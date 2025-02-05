/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup   PIOS_USART USART Functions
 * @brief PIOS interface for USART port
 * @{
 *
 * @file       pios_usart.c
 * @author     The LibrePilot Project, http://www.librepilot.org, Copyright (c) 2016-2017.
 *             The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @brief      USART commands. Inits USARTs, controls USARTs & Interupt handlers. (STM32 dependent)
 * @see        The GNU Public License (GPL) Version 3
 *
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/*
 * @todo This is virtually identical to the F1xx driver and should be merged.
 */

#include "pios.h"

#ifdef PIOS_INCLUDE_USART

#include <pios_usart_priv.h>

#include <pios_dma.h>

/* Provide a COM driver */
static void PIOS_USART_ChangeBaud(uint32_t usart_id, uint32_t baud);
static void PIOS_USART_ChangeConfig(uint32_t usart_id, enum PIOS_COM_Word_Length word_len, enum PIOS_COM_Parity parity, enum PIOS_COM_StopBits stop_bits, uint32_t baud_rate);
static void PIOS_USART_SetCtrlLine(uint32_t usart_id, uint32_t mask, uint32_t state);
static void PIOS_USART_RegisterRxCallback(uint32_t usart_id, pios_com_callback rx_in_cb, uint32_t context);
static void PIOS_USART_RegisterTxCallback(uint32_t usart_id, pios_com_callback tx_out_cb, uint32_t context);
static void PIOS_USART_TxStart(uint32_t usart_id, uint16_t tx_bytes_avail);
static void PIOS_USART_RxStart(uint32_t usart_id, uint16_t rx_bytes_avail);
static int32_t PIOS_USART_Ioctl(uint32_t usart_id, uint32_t ctl, void *param);
/* DMA RX double Buffer */
#define DMA_RX_BUFFER_LEN 36u // avoid overflow
uint8_t rx_buf[2][DMA_RX_BUFFER_LEN];

const struct pios_com_driver pios_usart_com_driver = {
    .set_baud      = PIOS_USART_ChangeBaud,
    .set_config    = PIOS_USART_ChangeConfig,
    .set_ctrl_line = PIOS_USART_SetCtrlLine,
    .tx_start      = PIOS_USART_TxStart,
    .rx_start      = PIOS_USART_RxStart,
    .bind_tx_cb    = PIOS_USART_RegisterTxCallback,
    .bind_rx_cb    = PIOS_USART_RegisterRxCallback,
    .ioctl         = PIOS_USART_Ioctl,
};

enum pios_usart_dev_magic {
    PIOS_USART_DEV_MAGIC = 0x4152834A,
};

struct pios_usart_dev {
    enum pios_usart_dev_magic   magic;
    const struct pios_usart_cfg *cfg;
    USART_InitTypeDef init;
    pios_com_callback rx_in_cb;
    uint32_t rx_in_context;
    pios_com_callback tx_out_cb;
    uint32_t tx_out_context;
    bool     config_locked;
    uint8_t  irq_channel;
};

static bool PIOS_USART_validate(struct pios_usart_dev *usart_dev)
{
    return usart_dev->magic == PIOS_USART_DEV_MAGIC;
}

const struct pios_usart_cfg *PIOS_USART_GetConfig(uint32_t usart_id)
{
    struct pios_usart_dev *usart_dev = (struct pios_usart_dev *)usart_id;

    bool valid = PIOS_USART_validate(usart_dev);

    PIOS_Assert(valid);

    return usart_dev->cfg;
}

static int32_t PIOS_USART_SetIrqPrio(struct pios_usart_dev *usart_dev, uint8_t irq_prio)
{
    NVIC_InitTypeDef init = {
        .NVIC_IRQChannel    = usart_dev->irq_channel,
        .NVIC_IRQChannelPreemptionPriority = irq_prio,
        .NVIC_IRQChannelCmd = ENABLE,
    };

    NVIC_Init(&init);

    return 0;
}

#if defined(PIOS_INCLUDE_FREERTOS)
static struct pios_usart_dev *PIOS_USART_alloc(void)
{
    struct pios_usart_dev *usart_dev;

    usart_dev = (struct pios_usart_dev *)pios_malloc(sizeof(struct pios_usart_dev));
    if (!usart_dev) {
        return NULL;
    }

    memset(usart_dev, 0, sizeof(struct pios_usart_dev));
    usart_dev->magic = PIOS_USART_DEV_MAGIC;
    return usart_dev;
}
#else
static struct pios_usart_dev pios_usart_devs[PIOS_USART_MAX_DEVS];
static uint8_t pios_usart_num_devs;
static struct pios_usart_dev *PIOS_USART_alloc(void)
{
    struct pios_usart_dev *usart_dev;

    if (pios_usart_num_devs >= PIOS_USART_MAX_DEVS) {
        return NULL;
    }

    usart_dev = &pios_usart_devs[pios_usart_num_devs++];

    memset(usart_dev, 0, sizeof(struct pios_usart_dev));
    usart_dev->magic = PIOS_USART_DEV_MAGIC;

    return usart_dev;
}
#endif /* if defined(PIOS_INCLUDE_FREERTOS) */

/* Bind Interrupt Handlers
 *
 * Map all valid USART IRQs to the common interrupt handler
 * and provide storage for a 32-bit device id IRQ to map
 * each physical IRQ to a specific registered device instance.
 */
static void PIOS_USART_generic_irq_handler(uint32_t usart_id);
void DBUS_IRQHandler();

static uint32_t PIOS_USART_1_id;
void USART1_IRQHandler(void) __attribute__((alias("PIOS_USART_1_irq_handler")));
static void PIOS_USART_1_irq_handler(void)
{
    DBUS_IRQHandler();
    // PIOS_USART_generic_irq_handler(PIOS_USART_1_id);
}

static uint32_t PIOS_USART_2_id;
void USART2_IRQHandler(void) __attribute__((alias("PIOS_USART_2_irq_handler")));
static void PIOS_USART_2_irq_handler(void)
{
    PIOS_USART_generic_irq_handler(PIOS_USART_2_id);
}

static uint32_t PIOS_USART_3_id;
void USART3_IRQHandler(void) __attribute__((alias("PIOS_USART_3_irq_handler")));
static void PIOS_USART_3_irq_handler(void)
{
    PIOS_USART_generic_irq_handler(PIOS_USART_3_id);
}

static uint32_t PIOS_USART_4_id;
void USART4_IRQHandler(void) __attribute__((alias("PIOS_USART_4_irq_handler")));
static void PIOS_USART_4_irq_handler(void)
{
    PIOS_USART_generic_irq_handler(PIOS_USART_4_id);
}

static uint32_t PIOS_USART_5_id;
void USART5_IRQHandler(void) __attribute__((alias("PIOS_USART_5_irq_handler")));
static void PIOS_USART_5_irq_handler(void)
{
    PIOS_USART_generic_irq_handler(PIOS_USART_5_id);
}

static uint32_t PIOS_USART_6_id;
void USART6_IRQHandler(void) __attribute__((alias("PIOS_USART_6_irq_handler")));
static void PIOS_USART_6_irq_handler(void)
{
    PIOS_USART_generic_irq_handler(PIOS_USART_6_id);
}

/**
 * Initialise a single USART device
 */
int32_t PIOS_USART_Init(uint32_t *usart_id, struct pios_usart_cfg *cfg)
{
    PIOS_DEBUG_Assert(usart_id);
    PIOS_DEBUG_Assert(cfg);

    uint32_t *local_id;
    uint8_t irq_channel;

    switch ((uint32_t)cfg->regs) {
    case (uint32_t)USART1:
        local_id    = &PIOS_USART_1_id;
        irq_channel = USART1_IRQn;
        break;
    case (uint32_t)USART2:
        local_id    = &PIOS_USART_2_id;
        irq_channel = USART2_IRQn;
        break;
#if !defined(STM32F411xE)
    case (uint32_t)USART3:
        local_id    = &PIOS_USART_3_id;
        irq_channel = USART3_IRQn;
        break;
    case (uint32_t)UART4:
        local_id    = &PIOS_USART_4_id;
        irq_channel = UART4_IRQn;
        break;
    case (uint32_t)UART5:
        local_id    = &PIOS_USART_5_id;
        irq_channel = UART5_IRQn;
        break;
#endif /* STM32F411xE */
    case (uint32_t)USART6:
        local_id    = &PIOS_USART_6_id;
        irq_channel = USART6_IRQn;
        break;
    default:
        return -1;
    }

    if (*local_id) {
        /* this port is already open */
        *usart_id = *local_id;
        return 0;
    }

    struct pios_usart_dev *usart_dev =
        (struct pios_usart_dev *)PIOS_USART_alloc();
    if (!usart_dev) { // malloc failed
        return -1;
    }
    /* Bind the configuration to the device instance */
    usart_dev->irq_channel = irq_channel; // never used here, conf in board_hw_defs.c
    if (cfg->use_dma) {
        USART_TypeDef *USARTx = cfg->regs;
        DMA_Stream_TypeDef *r_chan = cfg->dma.rx.channel;

        if (cfg->remap) {
            GPIO_PinAFConfig(cfg->rx.gpio,
                             __builtin_ctz(cfg->rx.init.GPIO_Pin),
                             cfg->remap);
        }
        GPIO_Init(cfg->rx.gpio, (GPIO_InitTypeDef *)&(cfg->rx.init));

        // Enable Module Clock Source in PIOS_SYS_Init()
        // { // fix parity stuff
        // USART_InitTypeDef init = usart_dev->init; // nothing meaningful here
        // if ((init.USART_Parity != USART_Parity_No) &&
        // (init.USART_WordLength == USART_WordLength_8b)) {
        // init.USART_WordLength = USART_WordLength_9b;
        // }
        // USART_Init(USARTx, &init);
        // USART_DMACmd(USARTx, USART_DMAReq_Rx, ENABLE);
        // USART_ClearFlag(USARTx, USART_FLAG_RXNE);
        // USART_ClearFlag(USARTx, USART_FLAG_IDLE);
        // USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
        // USART_ITConfig(USARTx, USART_IT_IDLE, ENABLE);
        // USART_Cmd(USARTx, ENABLE);
        // }

        // Configure NVIC
        NVIC_Init(&cfg->dma.irq.init);

        // Configure DMA double buffer mode
        {
            // cfg->rx_buf = (char**)rx_buf;
            // cfg->buf_len = DMA_RX_BUFFER_LEN;

            DMA_InitTypeDef dma_init = cfg->dma.rx.init;
            DMA_DeInit(r_chan);
            PIOS_DMA_SetRxBuffer(&cfg->dma, rx_buf[0], DMA_RX_BUFFER_LEN);
            DMA_Init(r_chan, &dma_init);
            DMA_DoubleBufferModeConfig(r_chan, (uint32_t)rx_buf[1], DMA_Memory_0);
            DMA_DoubleBufferModeCmd(r_chan, ENABLE);
            DMA_Cmd(r_chan, DISABLE); // Add a disable
            DMA_Cmd(r_chan, ENABLE);
        }
        /*
           RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_DMA2, ENABLE);
           RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

           RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);
           RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);

           //GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_USART1); //PB7  usart1 rx
           //
                GPIO_PinAFConfig(GPIOA,
                                                 __builtin_ctz(GPIO_Pin_10),
                                                 GPIO_AF_USART1);
           {
           GPIO_InitTypeDef GPIO_InitStructure;
           USART_InitTypeDef USART_InitStructure;
           GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
           GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
           GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
           GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
           GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
           GPIO_Init(GPIOA, &GPIO_InitStructure);

           USART_DeInit(USART1);

           USART_InitStructure.USART_BaudRate = 100000;
           USART_InitStructure.USART_WordLength = USART_WordLength_8b;
           USART_InitStructure.USART_StopBits = USART_StopBits_1;
           USART_InitStructure.USART_Parity = USART_Parity_Even;
           USART_InitStructure.USART_Mode = USART_Mode_Rx;
           USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
           USART_Init(USART1, &USART_InitStructure);

           USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);

           USART_ClearFlag(USART1, USART_FLAG_IDLE);
           USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);

           USART_Cmd(USART1, ENABLE);
           }

           {
           NVIC_InitTypeDef NVIC_InitStructure;
           NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
           NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID;
           NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
           NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
           NVIC_Init(&NVIC_InitStructure);
           }

           //DMA2 stream5 ch4  or (DMA2 stream2 ch4)    !!!!!!! P206 of the datasheet
           {
           DMA_InitTypeDef DMA_InitStructure;
           DMA_DeInit(DMA2_Stream2);

           DMA_InitStructure.DMA_Channel = DMA_Channel_4;
           DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (USART1->DR);
           DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)(rx_buf[0]);
           DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
           DMA_InitStructure.DMA_BufferSize = DMA_RX_BUFFER_LEN;
           DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
           DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
           DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
           DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
           DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
           DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
           DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
           DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
           DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
           DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
           DMA_Init(DMA2_Stream2, &DMA_InitStructure);
           DMA_DoubleBufferModeConfig(DMA2_Stream2, (uint32_t)(rx_buf[1]), DMA_Memory_0);
           DMA_DoubleBufferModeCmd(DMA2_Stream2, ENABLE);
           DMA_Cmd(DMA2_Stream2, DISABLE); //Add a disable
           DMA_Cmd(DMA2_Stream2, ENABLE);
           }
         */
    } else { // no use dma
             /* Initialize the comm parameter structure */
        USART_StructInit(&usart_dev->init); // 9600 8n1

        /* We will set modes later, depending on installed callbacks */
        usart_dev->init.USART_Mode = 0;


        /* If a DTR line is specified, initialize it */
        if (cfg->dtr.gpio) {
            GPIO_Init(cfg->dtr.gpio, (GPIO_InitTypeDef *)&cfg->dtr.init);
            PIOS_USART_SetCtrlLine((uint32_t)usart_dev, COM_CTRL_LINE_DTR_MASK, 0);
        }
#ifdef PIOS_USART_INVERTER_PORT
        /* Initialize inverter gpio and set it to off */
        if (cfg->regs == PIOS_USART_INVERTER_PORT) {
            GPIO_InitTypeDef inverterGPIOInit = {
                .GPIO_Pin   = PIOS_USART_INVERTER_PIN,
                .GPIO_Speed = GPIO_Speed_2MHz,
                .GPIO_Mode  = GPIO_Mode_OUT,
                .GPIO_OType = GPIO_OType_PP,
                .GPIO_PuPd  = GPIO_PuPd_UP
            };
            GPIO_Init(PIOS_USART_INVERTER_GPIO, &inverterGPIOInit);

            GPIO_WriteBit(PIOS_USART_INVERTER_GPIO,
                          PIOS_USART_INVERTER_PIN,
                          PIOS_USART_INVERTER_DISABLE);
        }
#endif
        PIOS_USART_SetIrqPrio(usart_dev, PIOS_IRQ_PRIO_MID);
    }

    usart_dev->cfg = cfg;
    *usart_id = (uint32_t)usart_dev;
    *local_id = (uint32_t)usart_dev;
    return 0;
}

void PIOS_USART_DMA_Reinit(uint32_t usart_id)
{
    PIOS_DEBUG_Assert(usart_id);

    struct pios_usart_dev *usart_dev = (struct pios_usart_dev *)usart_id;
    USART_TypeDef *USARTx = usart_dev->cfg->regs;
    DMA_Stream_TypeDef *r_chan = usart_dev->cfg->dma.rx.channel;
    USART_Cmd(USARTx, DISABLE);
    DMA_Cmd(r_chan, DISABLE);
    DMA_SetCurrDataCounter(r_chan, DMA_RX_BUFFER_LEN);
    USART_ClearFlag(usart_dev->cfg->regs, USART_FLAG_IDLE);

    DMA_ClearFlag(r_chan, DMA_FLAG_TCIF2);
    DMA_ClearITPendingBit(r_chan, DMA_IT_TCIF2);
    DMA_Cmd(r_chan, ENABLE);
    USART_Cmd(USARTx, ENABLE);
}

static void PIOS_USART_Setup(struct pios_usart_dev *usart_dev)
{
    /* Configure RX GPIO */
    if ((usart_dev->init.USART_Mode & USART_Mode_Rx) && (usart_dev->cfg->rx.gpio)) {
        if (usart_dev->cfg->remap) {
            GPIO_PinAFConfig(usart_dev->cfg->rx.gpio,
                             __builtin_ctz(usart_dev->cfg->rx.init.GPIO_Pin),
                             usart_dev->cfg->remap);
        }

        GPIO_Init(usart_dev->cfg->rx.gpio, (GPIO_InitTypeDef *)&usart_dev->cfg->rx.init);

        /* just enable RX right away, cause rcvr modules do not call rx_start method */
        USART_ITConfig(usart_dev->cfg->regs, USART_IT_RXNE, ENABLE);
        USART_ITConfig(usart_dev->cfg->regs, USART_IT_IDLE, ENABLE);
    }

    /* Configure TX GPIO */
    if ((usart_dev->init.USART_Mode & USART_Mode_Tx) && usart_dev->cfg->tx.gpio) {
        if (usart_dev->cfg->remap) {
            GPIO_PinAFConfig(usart_dev->cfg->tx.gpio,
                             __builtin_ctz(usart_dev->cfg->tx.init.GPIO_Pin),
                             usart_dev->cfg->remap);
        }

        GPIO_Init(usart_dev->cfg->tx.gpio, (GPIO_InitTypeDef *)&usart_dev->cfg->tx.init);
    }

    /* Write new configuration */
    { // fix parity stuff, why
        USART_InitTypeDef init = usart_dev->init;

        if ((init.USART_Parity != USART_Parity_No) && (init.USART_WordLength == USART_WordLength_8b)) {
            init.USART_WordLength = USART_WordLength_9b;
        }

        USART_Init(usart_dev->cfg->regs, &init);
    }

    /*
     * Re enable USART.
     */
    USART_Cmd(usart_dev->cfg->regs, ENABLE);
}

static void PIOS_USART_RxStart(uint32_t usart_id, __attribute__((unused)) uint16_t rx_bytes_avail)
{
    struct pios_usart_dev *usart_dev = (struct pios_usart_dev *)usart_id;

    bool valid = PIOS_USART_validate(usart_dev);

    PIOS_Assert(valid);

    USART_ITConfig(usart_dev->cfg->regs, USART_IT_RXNE, ENABLE);
}
static void PIOS_USART_TxStart(uint32_t usart_id, __attribute__((unused)) uint16_t tx_bytes_avail)
{
    struct pios_usart_dev *usart_dev = (struct pios_usart_dev *)usart_id;

    bool valid = PIOS_USART_validate(usart_dev);

    PIOS_Assert(valid);

    USART_ITConfig(usart_dev->cfg->regs, USART_IT_TXE, ENABLE);
}

/**
 * Changes the baud rate of the USART peripheral without re-initialising.
 * \param[in] usart_id USART name (GPS, TELEM, AUX)
 * \param[in] baud Requested baud rate
 */
static void PIOS_USART_ChangeBaud(uint32_t usart_id, uint32_t baud)
{
    struct pios_usart_dev *usart_dev = (struct pios_usart_dev *)usart_id;

    bool valid = PIOS_USART_validate(usart_dev);

    PIOS_Assert(valid);

    if (usart_dev->config_locked) {
        return;
    }

    /* Use our working copy of the usart init structure */
    usart_dev->init.USART_BaudRate = baud;

    PIOS_USART_Setup(usart_dev);
}

/**
 * Changes configuration of the USART peripheral without re-initialising.
 * \param[in] usart_id USART name (GPS, TELEM, AUX)
 * \param[in] word_len Requested word length
 * \param[in] stop_bits Requested stop bits
 * \param[in] parity Requested parity
 * \param[in] baud_rate Requested baud rate
 * \param[in] mode Requested mode
 *
 */
static void PIOS_USART_ChangeConfig(uint32_t usart_id,
                                    enum PIOS_COM_Word_Length word_len,
                                    enum PIOS_COM_Parity parity,
                                    enum PIOS_COM_StopBits stop_bits,
                                    uint32_t baud_rate)
{
    struct pios_usart_dev *usart_dev = (struct pios_usart_dev *)usart_id;

    bool valid = PIOS_USART_validate(usart_dev);

    PIOS_Assert(valid);

    if (usart_dev->config_locked) {
        return;
    }

    switch (word_len) {
    case PIOS_COM_Word_length_8b:
        usart_dev->init.USART_WordLength = USART_WordLength_8b;
        break;
    case PIOS_COM_Word_length_9b:
        usart_dev->init.USART_WordLength = USART_WordLength_9b;
        break;
    default:
        break;
    }

    switch (stop_bits) {
    case PIOS_COM_StopBits_0_5:
        usart_dev->init.USART_StopBits = USART_StopBits_0_5;
        break;
    case PIOS_COM_StopBits_1:
        usart_dev->init.USART_StopBits = USART_StopBits_1;
        break;
    case PIOS_COM_StopBits_1_5:
        usart_dev->init.USART_StopBits = USART_StopBits_1_5;
        break;
    case PIOS_COM_StopBits_2:
        usart_dev->init.USART_StopBits = USART_StopBits_2;
        break;
    default:
        break;
    }

    switch (parity) {
    case PIOS_COM_Parity_No:
        usart_dev->init.USART_Parity = USART_Parity_No;
        break;
    case PIOS_COM_Parity_Even:
        usart_dev->init.USART_Parity = USART_Parity_Even;
        break;
    case PIOS_COM_Parity_Odd:
        usart_dev->init.USART_Parity = USART_Parity_Odd;
        break;
    default:
        break;
    }

    if (baud_rate) {
        usart_dev->init.USART_BaudRate = baud_rate;
    }

    usart_dev->init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    PIOS_USART_Setup(usart_dev);
}

static void PIOS_USART_SetCtrlLine(uint32_t usart_id, uint32_t mask, uint32_t state)
{
    struct pios_usart_dev *usart_dev = (struct pios_usart_dev *)usart_id;

    bool valid = PIOS_USART_validate(usart_dev);

    PIOS_Assert(valid);

    /* Only attempt to drive DTR if this USART has a GPIO line defined */
    if (usart_dev->cfg->dtr.gpio && (mask & COM_CTRL_LINE_DTR_MASK)) {
        GPIO_WriteBit(usart_dev->cfg->dtr.gpio,
                      usart_dev->cfg->dtr.init.GPIO_Pin,
                      state & COM_CTRL_LINE_DTR_MASK ? Bit_RESET : Bit_SET);
    }
}

static void PIOS_USART_RegisterRxCallback(uint32_t usart_id, pios_com_callback rx_in_cb, uint32_t context)
{
    struct pios_usart_dev *usart_dev = (struct pios_usart_dev *)usart_id;

    bool valid = PIOS_USART_validate(usart_dev);

    PIOS_Assert(valid);

    /*
     * Order is important in these assignments since ISR uses _cb
     * field to determine if it's ok to dereference _cb and _context
     */
    usart_dev->rx_in_context    = context;
    usart_dev->rx_in_cb = rx_in_cb;

    usart_dev->init.USART_Mode |= USART_Mode_Rx;

    PIOS_USART_Setup(usart_dev);
}

static void PIOS_USART_RegisterTxCallback(uint32_t usart_id, pios_com_callback tx_out_cb, uint32_t context)
{
    struct pios_usart_dev *usart_dev = (struct pios_usart_dev *)usart_id;

    bool valid = PIOS_USART_validate(usart_dev);

    PIOS_Assert(valid);

    /*
     * Order is important in these assignments since ISR uses _cb
     * field to determine if it's ok to dereference _cb and _context
     */
    usart_dev->tx_out_context   = context;
    usart_dev->tx_out_cb = tx_out_cb;

    usart_dev->init.USART_Mode |= USART_Mode_Tx;

    PIOS_USART_Setup(usart_dev);
}

void DBUS_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        USART_ReceiveData(USART1);
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
    if (USART_GetITStatus(USART1, USART_IT_IDLE) != RESET) {
        static uint16_t this_time_rx_len = 0;
        USART_ReceiveData(USART1);

        if (DMA_GetCurrentMemoryTarget(DMA2_Stream2) == 0) {
            DMA_Cmd(DMA2_Stream2, DISABLE);
            this_time_rx_len  = DMA_RX_BUFFER_LEN - DMA_GetCurrDataCounter(DMA2_Stream2);
            DMA_SetCurrDataCounter(DMA2_Stream2, DMA_RX_BUFFER_LEN);
            DMA2_Stream2->CR |= DMA_SxCR_CT;
            DMA_ClearFlag(DMA2_Stream2, DMA_FLAG_TCIF2 | DMA_FLAG_HTIF2);
            DMA_Cmd(DMA2_Stream2, ENABLE);
            if (this_time_rx_len == 18) {
                volatile char *rx_buf_0 = rx_buf[0];
            }
        } else {
            // ÖØÐÂÉèÖÃDMA
            DMA_Cmd(DMA2_Stream2, DISABLE);
            this_time_rx_len  = DMA_RX_BUFFER_LEN - DMA_GetCurrDataCounter(DMA2_Stream2);
            DMA_SetCurrDataCounter(DMA2_Stream2, DMA_RX_BUFFER_LEN);
            DMA2_Stream2->CR &= ~(DMA_SxCR_CT);
            // ÇåDMAÖÐ¶Ï±êÖ¾
            DMA_ClearFlag(DMA2_Stream2, DMA_FLAG_TCIF2 | DMA_FLAG_HTIF2);
            DMA_Cmd(DMA2_Stream2, ENABLE);
            if (this_time_rx_len == 18) {
                // ´¦ÀíÒ£¿ØÆ÷Êý¾Ý
                // ¼ÇÂ¼Êý¾Ý½ÓÊÕÊ±¼ä
                volatile char *rx_buf_0 = rx_buf[1];
            }
        }
    }
}


static void PIOS_USART_generic_irq_handler(uint32_t usart_id)
{
    struct pios_usart_dev *usart_dev = (struct pios_usart_dev *)usart_id;

    bool valid = PIOS_USART_validate(usart_dev);

    PIOS_Assert(valid);

    /* Force read of dr after sr to make sure to clear error flags */
    volatile uint16_t sr = usart_dev->cfg->regs->SR;
    volatile uint8_t dr  = usart_dev->cfg->regs->DR;

    /* Check if RXNE flag is set */
    bool rx_need_yield   = false;
    if (sr & USART_SR_RXNE) {
        uint8_t byte = dr;
        if (usart_dev->rx_in_cb) {
            (void)(usart_dev->rx_in_cb)(usart_dev->rx_in_context, &byte, 1, NULL, &rx_need_yield);
        }
    }

    /* Check if TXE flag is set */
    bool tx_need_yield = false;
    if (sr & USART_SR_TXE) {
        if (usart_dev->tx_out_cb) {
            uint8_t b;
            uint16_t bytes_to_send;

            bytes_to_send = (usart_dev->tx_out_cb)(usart_dev->tx_out_context, &b, 1, NULL, &tx_need_yield);

            if (bytes_to_send > 0) {
                /* Send the byte we've been given */
                usart_dev->cfg->regs->DR = b;
            } else {
                /* No bytes to send, disable TXE interrupt */
                USART_ITConfig(usart_dev->cfg->regs, USART_IT_TXE, DISABLE);
            }
        } else {
            /* No bytes to send, disable TXE interrupt */
            USART_ITConfig(usart_dev->cfg->regs, USART_IT_TXE, DISABLE);
        }
    }

    if (sr & USART_IT_IDLE) {
        const struct pios_usart_cfg *cfg = usart_dev->cfg;
        USART_TypeDef *USARTx = cfg->regs;
        DMA_Stream_TypeDef *r_chan = cfg->dma.rx.channel;
        static uint16_t this_time_rx_len = 0;
        USART_ReceiveData(USARTx); // use dr
        if (DMA_GetCurrentMemoryTarget(r_chan) == 0) {
            DMA_Cmd(r_chan, DISABLE);
            this_time_rx_len = DMA_RX_BUFFER_LEN
                               - DMA_GetCurrDataCounter(r_chan); // ?
            DMA_SetCurrDataCounter(r_chan, DMA_RX_BUFFER_LEN);
            r_chan->CR |= DMA_SxCR_CT;
            DMA_ClearFlag(r_chan, DMA_FLAG_TCIF2 | DMA_FLAG_HTIF2);
            DMA_Cmd(r_chan, ENABLE);
            if (usart_dev->rx_in_cb) {
                (void)(usart_dev->rx_in_cb)(usart_dev->rx_in_context,
                                            rx_buf[0], this_time_rx_len, NULL, &rx_need_yield);
            }
        } else {
            DMA_Cmd(r_chan, DISABLE);
            this_time_rx_len = DMA_RX_BUFFER_LEN
                               - DMA_GetCurrDataCounter(r_chan); // ?
            DMA_SetCurrDataCounter(r_chan, DMA_RX_BUFFER_LEN);
            r_chan->CR |= DMA_SxCR_CT;
            DMA_ClearFlag(r_chan, DMA_FLAG_TCIF2 | DMA_FLAG_HTIF2);
            DMA_Cmd(r_chan, ENABLE);
            if (usart_dev->rx_in_cb) {
                (void)(usart_dev->rx_in_cb)(usart_dev->rx_in_context,
                                            rx_buf[1], this_time_rx_len, NULL, &rx_need_yield);
            }
        }
    }

#if defined(PIOS_INCLUDE_FREERTOS)
    if (rx_need_yield || tx_need_yield) {
        vPortYield();
    }
#endif /* PIOS_INCLUDE_FREERTOS */
}

static int32_t PIOS_USART_Ioctl(uint32_t usart_id, uint32_t ctl, void *param)
{
    struct pios_usart_dev *usart_dev = (struct pios_usart_dev *)usart_id;

    bool valid = PIOS_USART_validate(usart_dev);

    PIOS_Assert(valid);

    /* First try board specific IOCTL to allow overriding default functions */
    if (usart_dev->cfg->ioctl) {
        int32_t ret = usart_dev->cfg->ioctl(usart_id, ctl, param);
        if (ret != COM_IOCTL_ENOSYS) {
            return ret;
        }
    }

    switch (ctl) {
    case PIOS_IOCTL_USART_SET_IRQ_PRIO:
        return PIOS_USART_SetIrqPrio(usart_dev, *(uint8_t *)param);

#ifdef PIOS_USART_INVERTER_PORT
    case PIOS_IOCTL_USART_SET_INVERTED:
        if (usart_dev->cfg->regs != PIOS_USART_INVERTER_PORT) {
            return COM_IOCTL_ENOSYS; /* don't know how */
        }
        GPIO_WriteBit(PIOS_USART_INVERTER_GPIO,
                      PIOS_USART_INVERTER_PIN,
                      (*(enum PIOS_USART_Inverted *)param & PIOS_USART_Inverted_Rx) ? PIOS_USART_INVERTER_ENABLE : PIOS_USART_INVERTER_DISABLE);

        break;
#endif /* PIOS_USART_INVERTER_PORT */
    case PIOS_IOCTL_USART_GET_DSMBIND:
#ifdef PIOS_USART_INVERTER_PORT
        if (usart_dev->cfg->regs == PIOS_USART_INVERTER_PORT) {
            return -2; /* do not allow dsm bind on port with inverter */
        }
#endif /* otherwise, return RXGPIO */
    case PIOS_IOCTL_USART_GET_RXGPIO:
        *(struct stm32_gpio *)param = usart_dev->cfg->rx;
        break;
    case PIOS_IOCTL_USART_GET_TXGPIO:
        *(struct stm32_gpio *)param = usart_dev->cfg->tx;
        break;
    case PIOS_IOCTL_USART_SET_HALFDUPLEX:
        USART_HalfDuplexCmd(usart_dev->cfg->regs, *(bool *)param ? ENABLE : DISABLE);
        break;
    case PIOS_IOCTL_USART_LOCK_CONFIG:
        usart_dev->config_locked = *(bool *)param;
        break;
    default:
        return COM_IOCTL_ENOSYS; /* unknown ioctl */
    }

    return 0;
}

#endif /* PIOS_INCLUDE_USART */

/**
 * @}
 * @}
 */
