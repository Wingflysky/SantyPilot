/** @file
 *    @brief MAVLink comm protocol testsuite generated from matrixpilot.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef MATRIXPILOT_TESTSUITE_H
#define MATRIXPILOT_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common(uint8_t, uint8_t, mavlink_message_t * last_msg);
static void mavlink_test_matrixpilot(uint8_t, uint8_t, mavlink_message_t * last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_common(system_id, component_id, last_msg);
    mavlink_test_matrixpilot(system_id, component_id, last_msg);
}
#endif

#include "../common/testsuite.h"


static void mavlink_test_flexifunction_set(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FLEXIFUNCTION_SET >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_flexifunction_set_t packet_in = {
        5, 72
    };
    mavlink_flexifunction_set_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.target_system    = packet_in.target_system;
    packet1.target_component = packet_in.target_component;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_FLEXIFUNCTION_SET_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_FLEXIFUNCTION_SET_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_set_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_flexifunction_set_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_set_pack(system_id, component_id, &msg, packet1.target_system, packet1.target_component);
    mavlink_msg_flexifunction_set_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_set_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.target_system, packet1.target_component);
    mavlink_msg_flexifunction_set_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_flexifunction_set_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_set_send(MAVLINK_COMM_1, packet1.target_system, packet1.target_component);
    mavlink_msg_flexifunction_set_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FLEXIFUNCTION_SET") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FLEXIFUNCTION_SET) != NULL);
#endif
}

static void mavlink_test_flexifunction_read_req(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FLEXIFUNCTION_READ_REQ >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_flexifunction_read_req_t packet_in = {
        17235, 17339, 17, 84
    };
    mavlink_flexifunction_read_req_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.read_req_type    = packet_in.read_req_type;
    packet1.data_index       = packet_in.data_index;
    packet1.target_system    = packet_in.target_system;
    packet1.target_component = packet_in.target_component;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_FLEXIFUNCTION_READ_REQ_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_FLEXIFUNCTION_READ_REQ_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_read_req_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_flexifunction_read_req_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_read_req_pack(system_id, component_id, &msg, packet1.target_system, packet1.target_component, packet1.read_req_type, packet1.data_index);
    mavlink_msg_flexifunction_read_req_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_read_req_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.target_system, packet1.target_component, packet1.read_req_type, packet1.data_index);
    mavlink_msg_flexifunction_read_req_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_flexifunction_read_req_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_read_req_send(MAVLINK_COMM_1, packet1.target_system, packet1.target_component, packet1.read_req_type, packet1.data_index);
    mavlink_msg_flexifunction_read_req_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FLEXIFUNCTION_READ_REQ") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FLEXIFUNCTION_READ_REQ) != NULL);
#endif
}

static void mavlink_test_flexifunction_buffer_function(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FLEXIFUNCTION_BUFFER_FUNCTION >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_flexifunction_buffer_function_t packet_in = {
        17235, 17339, 17443, 17547, 29, 96, { 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210 }
    };
    mavlink_flexifunction_buffer_function_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.func_index       = packet_in.func_index;
    packet1.func_count       = packet_in.func_count;
    packet1.data_address     = packet_in.data_address;
    packet1.data_size        = packet_in.data_size;
    packet1.target_system    = packet_in.target_system;
    packet1.target_component = packet_in.target_component;

    mav_array_memcpy(packet1.data, packet_in.data, sizeof(int8_t) * 48);

#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_FLEXIFUNCTION_BUFFER_FUNCTION_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_FLEXIFUNCTION_BUFFER_FUNCTION_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_buffer_function_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_flexifunction_buffer_function_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_buffer_function_pack(system_id, component_id, &msg, packet1.target_system, packet1.target_component, packet1.func_index, packet1.func_count, packet1.data_address, packet1.data_size, packet1.data);
    mavlink_msg_flexifunction_buffer_function_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_buffer_function_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.target_system, packet1.target_component, packet1.func_index, packet1.func_count, packet1.data_address, packet1.data_size, packet1.data);
    mavlink_msg_flexifunction_buffer_function_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_flexifunction_buffer_function_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_buffer_function_send(MAVLINK_COMM_1, packet1.target_system, packet1.target_component, packet1.func_index, packet1.func_count, packet1.data_address, packet1.data_size, packet1.data);
    mavlink_msg_flexifunction_buffer_function_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FLEXIFUNCTION_BUFFER_FUNCTION") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FLEXIFUNCTION_BUFFER_FUNCTION) != NULL);
#endif
}

static void mavlink_test_flexifunction_buffer_function_ack(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FLEXIFUNCTION_BUFFER_FUNCTION_ACK >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_flexifunction_buffer_function_ack_t packet_in = {
        17235, 17339, 17, 84
    };
    mavlink_flexifunction_buffer_function_ack_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.func_index       = packet_in.func_index;
    packet1.result           = packet_in.result;
    packet1.target_system    = packet_in.target_system;
    packet1.target_component = packet_in.target_component;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_FLEXIFUNCTION_BUFFER_FUNCTION_ACK_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_FLEXIFUNCTION_BUFFER_FUNCTION_ACK_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_buffer_function_ack_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_flexifunction_buffer_function_ack_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_buffer_function_ack_pack(system_id, component_id, &msg, packet1.target_system, packet1.target_component, packet1.func_index, packet1.result);
    mavlink_msg_flexifunction_buffer_function_ack_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_buffer_function_ack_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.target_system, packet1.target_component, packet1.func_index, packet1.result);
    mavlink_msg_flexifunction_buffer_function_ack_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_flexifunction_buffer_function_ack_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_buffer_function_ack_send(MAVLINK_COMM_1, packet1.target_system, packet1.target_component, packet1.func_index, packet1.result);
    mavlink_msg_flexifunction_buffer_function_ack_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FLEXIFUNCTION_BUFFER_FUNCTION_ACK") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FLEXIFUNCTION_BUFFER_FUNCTION_ACK) != NULL);
#endif
}

static void mavlink_test_flexifunction_directory(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FLEXIFUNCTION_DIRECTORY >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_flexifunction_directory_t packet_in = {
        5, 72, 139, 206, 17, { 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131 }
    };
    mavlink_flexifunction_directory_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.target_system    = packet_in.target_system;
    packet1.target_component = packet_in.target_component;
    packet1.directory_type   = packet_in.directory_type;
    packet1.start_index = packet_in.start_index;
    packet1.count = packet_in.count;

    mav_array_memcpy(packet1.directory_data, packet_in.directory_data, sizeof(int8_t) * 48);

#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_FLEXIFUNCTION_DIRECTORY_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_FLEXIFUNCTION_DIRECTORY_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_directory_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_flexifunction_directory_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_directory_pack(system_id, component_id, &msg, packet1.target_system, packet1.target_component, packet1.directory_type, packet1.start_index, packet1.count, packet1.directory_data);
    mavlink_msg_flexifunction_directory_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_directory_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.target_system, packet1.target_component, packet1.directory_type, packet1.start_index, packet1.count, packet1.directory_data);
    mavlink_msg_flexifunction_directory_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_flexifunction_directory_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_directory_send(MAVLINK_COMM_1, packet1.target_system, packet1.target_component, packet1.directory_type, packet1.start_index, packet1.count, packet1.directory_data);
    mavlink_msg_flexifunction_directory_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FLEXIFUNCTION_DIRECTORY") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FLEXIFUNCTION_DIRECTORY) != NULL);
#endif
}

static void mavlink_test_flexifunction_directory_ack(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FLEXIFUNCTION_DIRECTORY_ACK >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_flexifunction_directory_ack_t packet_in = {
        17235, 139, 206, 17, 84, 151
    };
    mavlink_flexifunction_directory_ack_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.result = packet_in.result;
    packet1.target_system    = packet_in.target_system;
    packet1.target_component = packet_in.target_component;
    packet1.directory_type   = packet_in.directory_type;
    packet1.start_index = packet_in.start_index;
    packet1.count = packet_in.count;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_FLEXIFUNCTION_DIRECTORY_ACK_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_FLEXIFUNCTION_DIRECTORY_ACK_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_directory_ack_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_flexifunction_directory_ack_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_directory_ack_pack(system_id, component_id, &msg, packet1.target_system, packet1.target_component, packet1.directory_type, packet1.start_index, packet1.count, packet1.result);
    mavlink_msg_flexifunction_directory_ack_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_directory_ack_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.target_system, packet1.target_component, packet1.directory_type, packet1.start_index, packet1.count, packet1.result);
    mavlink_msg_flexifunction_directory_ack_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_flexifunction_directory_ack_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_directory_ack_send(MAVLINK_COMM_1, packet1.target_system, packet1.target_component, packet1.directory_type, packet1.start_index, packet1.count, packet1.result);
    mavlink_msg_flexifunction_directory_ack_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FLEXIFUNCTION_DIRECTORY_ACK") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FLEXIFUNCTION_DIRECTORY_ACK) != NULL);
#endif
}

static void mavlink_test_flexifunction_command(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FLEXIFUNCTION_COMMAND >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_flexifunction_command_t packet_in = {
        5, 72, 139
    };
    mavlink_flexifunction_command_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.target_system    = packet_in.target_system;
    packet1.target_component = packet_in.target_component;
    packet1.command_type     = packet_in.command_type;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_FLEXIFUNCTION_COMMAND_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_FLEXIFUNCTION_COMMAND_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_command_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_flexifunction_command_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_command_pack(system_id, component_id, &msg, packet1.target_system, packet1.target_component, packet1.command_type);
    mavlink_msg_flexifunction_command_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_command_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.target_system, packet1.target_component, packet1.command_type);
    mavlink_msg_flexifunction_command_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_flexifunction_command_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_command_send(MAVLINK_COMM_1, packet1.target_system, packet1.target_component, packet1.command_type);
    mavlink_msg_flexifunction_command_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FLEXIFUNCTION_COMMAND") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FLEXIFUNCTION_COMMAND) != NULL);
#endif
}

static void mavlink_test_flexifunction_command_ack(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FLEXIFUNCTION_COMMAND_ACK >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_flexifunction_command_ack_t packet_in = {
        17235, 17339
    };
    mavlink_flexifunction_command_ack_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.command_type = packet_in.command_type;
    packet1.result = packet_in.result;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_FLEXIFUNCTION_COMMAND_ACK_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_FLEXIFUNCTION_COMMAND_ACK_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_command_ack_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_flexifunction_command_ack_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_command_ack_pack(system_id, component_id, &msg, packet1.command_type, packet1.result);
    mavlink_msg_flexifunction_command_ack_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_command_ack_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.command_type, packet1.result);
    mavlink_msg_flexifunction_command_ack_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_flexifunction_command_ack_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_flexifunction_command_ack_send(MAVLINK_COMM_1, packet1.command_type, packet1.result);
    mavlink_msg_flexifunction_command_ack_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FLEXIFUNCTION_COMMAND_ACK") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FLEXIFUNCTION_COMMAND_ACK) != NULL);
#endif
}

static void mavlink_test_serial_udb_extra_f2_a(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F2_A >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_serial_udb_extra_f2_a_t packet_in = {
        963497464, 963497672, 963497880, 963498088, 18067, 18171, 18275, 18379, 18483, 18587, 18691, 18795, 18899, 19003, 19107, 19211, 19315, 19419, 19523, 19627, 19731, 19835, 19939, 20043, 20147, 20251, 185
    };
    mavlink_serial_udb_extra_f2_a_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.sue_time      = packet_in.sue_time;
    packet1.sue_latitude  = packet_in.sue_latitude;
    packet1.sue_longitude = packet_in.sue_longitude;
    packet1.sue_altitude  = packet_in.sue_altitude;
    packet1.sue_waypoint_index = packet_in.sue_waypoint_index;
    packet1.sue_rmat0     = packet_in.sue_rmat0;
    packet1.sue_rmat1     = packet_in.sue_rmat1;
    packet1.sue_rmat2     = packet_in.sue_rmat2;
    packet1.sue_rmat3     = packet_in.sue_rmat3;
    packet1.sue_rmat4     = packet_in.sue_rmat4;
    packet1.sue_rmat5     = packet_in.sue_rmat5;
    packet1.sue_rmat6     = packet_in.sue_rmat6;
    packet1.sue_rmat7     = packet_in.sue_rmat7;
    packet1.sue_rmat8     = packet_in.sue_rmat8;
    packet1.sue_cog = packet_in.sue_cog;
    packet1.sue_sog = packet_in.sue_sog;
    packet1.sue_cpu_load  = packet_in.sue_cpu_load;
    packet1.sue_air_speed_3DIMU  = packet_in.sue_air_speed_3DIMU;
    packet1.sue_estimated_wind_0 = packet_in.sue_estimated_wind_0;
    packet1.sue_estimated_wind_1 = packet_in.sue_estimated_wind_1;
    packet1.sue_estimated_wind_2 = packet_in.sue_estimated_wind_2;
    packet1.sue_magFieldEarth0   = packet_in.sue_magFieldEarth0;
    packet1.sue_magFieldEarth1   = packet_in.sue_magFieldEarth1;
    packet1.sue_magFieldEarth2   = packet_in.sue_magFieldEarth2;
    packet1.sue_svs    = packet_in.sue_svs;
    packet1.sue_hdop   = packet_in.sue_hdop;
    packet1.sue_status = packet_in.sue_status;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F2_A_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F2_A_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f2_a_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_serial_udb_extra_f2_a_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f2_a_pack(system_id, component_id, &msg, packet1.sue_time, packet1.sue_status, packet1.sue_latitude, packet1.sue_longitude, packet1.sue_altitude, packet1.sue_waypoint_index, packet1.sue_rmat0, packet1.sue_rmat1, packet1.sue_rmat2, packet1.sue_rmat3, packet1.sue_rmat4, packet1.sue_rmat5, packet1.sue_rmat6, packet1.sue_rmat7, packet1.sue_rmat8, packet1.sue_cog, packet1.sue_sog, packet1.sue_cpu_load, packet1.sue_air_speed_3DIMU, packet1.sue_estimated_wind_0, packet1.sue_estimated_wind_1, packet1.sue_estimated_wind_2, packet1.sue_magFieldEarth0, packet1.sue_magFieldEarth1, packet1.sue_magFieldEarth2, packet1.sue_svs, packet1.sue_hdop);
    mavlink_msg_serial_udb_extra_f2_a_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f2_a_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.sue_time, packet1.sue_status, packet1.sue_latitude, packet1.sue_longitude, packet1.sue_altitude, packet1.sue_waypoint_index, packet1.sue_rmat0, packet1.sue_rmat1, packet1.sue_rmat2, packet1.sue_rmat3, packet1.sue_rmat4, packet1.sue_rmat5, packet1.sue_rmat6, packet1.sue_rmat7, packet1.sue_rmat8, packet1.sue_cog, packet1.sue_sog, packet1.sue_cpu_load, packet1.sue_air_speed_3DIMU, packet1.sue_estimated_wind_0, packet1.sue_estimated_wind_1, packet1.sue_estimated_wind_2, packet1.sue_magFieldEarth0, packet1.sue_magFieldEarth1, packet1.sue_magFieldEarth2, packet1.sue_svs, packet1.sue_hdop);
    mavlink_msg_serial_udb_extra_f2_a_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_serial_udb_extra_f2_a_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f2_a_send(MAVLINK_COMM_1, packet1.sue_time, packet1.sue_status, packet1.sue_latitude, packet1.sue_longitude, packet1.sue_altitude, packet1.sue_waypoint_index, packet1.sue_rmat0, packet1.sue_rmat1, packet1.sue_rmat2, packet1.sue_rmat3, packet1.sue_rmat4, packet1.sue_rmat5, packet1.sue_rmat6, packet1.sue_rmat7, packet1.sue_rmat8, packet1.sue_cog, packet1.sue_sog, packet1.sue_cpu_load, packet1.sue_air_speed_3DIMU, packet1.sue_estimated_wind_0, packet1.sue_estimated_wind_1, packet1.sue_estimated_wind_2, packet1.sue_magFieldEarth0, packet1.sue_magFieldEarth1, packet1.sue_magFieldEarth2, packet1.sue_svs, packet1.sue_hdop);
    mavlink_msg_serial_udb_extra_f2_a_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SERIAL_UDB_EXTRA_F2_A") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F2_A) != NULL);
#endif
}

static void mavlink_test_serial_udb_extra_f2_b(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F2_B >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_serial_udb_extra_f2_b_t packet_in = {
        963497464, 963497672, 963497880, 963498088, 18067, 18171, 18275, 18379, 18483, 18587, 18691, 18795, 18899, 19003, 19107, 19211, 19315, 19419, 19523, 19627, 19731, 19835, 19939, 20043, 20147, 20251, 20355, 20459, 20563, 20667, 20771, 20875, 20979, 21083, 21187, 21291, 21395, 21499, 21603, 21707, 21811, 21915, 22019, 22123, 22227, 22331, 22435, 22539, 22643, 22747
    };
    mavlink_serial_udb_extra_f2_b_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.sue_time           = packet_in.sue_time;
    packet1.sue_flags          = packet_in.sue_flags;
    packet1.sue_barom_press    = packet_in.sue_barom_press;
    packet1.sue_barom_alt      = packet_in.sue_barom_alt;
    packet1.sue_pwm_input_1    = packet_in.sue_pwm_input_1;
    packet1.sue_pwm_input_2    = packet_in.sue_pwm_input_2;
    packet1.sue_pwm_input_3    = packet_in.sue_pwm_input_3;
    packet1.sue_pwm_input_4    = packet_in.sue_pwm_input_4;
    packet1.sue_pwm_input_5    = packet_in.sue_pwm_input_5;
    packet1.sue_pwm_input_6    = packet_in.sue_pwm_input_6;
    packet1.sue_pwm_input_7    = packet_in.sue_pwm_input_7;
    packet1.sue_pwm_input_8    = packet_in.sue_pwm_input_8;
    packet1.sue_pwm_input_9    = packet_in.sue_pwm_input_9;
    packet1.sue_pwm_input_10   = packet_in.sue_pwm_input_10;
    packet1.sue_pwm_input_11   = packet_in.sue_pwm_input_11;
    packet1.sue_pwm_input_12   = packet_in.sue_pwm_input_12;
    packet1.sue_pwm_output_1   = packet_in.sue_pwm_output_1;
    packet1.sue_pwm_output_2   = packet_in.sue_pwm_output_2;
    packet1.sue_pwm_output_3   = packet_in.sue_pwm_output_3;
    packet1.sue_pwm_output_4   = packet_in.sue_pwm_output_4;
    packet1.sue_pwm_output_5   = packet_in.sue_pwm_output_5;
    packet1.sue_pwm_output_6   = packet_in.sue_pwm_output_6;
    packet1.sue_pwm_output_7   = packet_in.sue_pwm_output_7;
    packet1.sue_pwm_output_8   = packet_in.sue_pwm_output_8;
    packet1.sue_pwm_output_9   = packet_in.sue_pwm_output_9;
    packet1.sue_pwm_output_10  = packet_in.sue_pwm_output_10;
    packet1.sue_pwm_output_11  = packet_in.sue_pwm_output_11;
    packet1.sue_pwm_output_12  = packet_in.sue_pwm_output_12;
    packet1.sue_imu_location_x = packet_in.sue_imu_location_x;
    packet1.sue_imu_location_y = packet_in.sue_imu_location_y;
    packet1.sue_imu_location_z = packet_in.sue_imu_location_z;
    packet1.sue_location_error_earth_x = packet_in.sue_location_error_earth_x;
    packet1.sue_location_error_earth_y = packet_in.sue_location_error_earth_y;
    packet1.sue_location_error_earth_z = packet_in.sue_location_error_earth_z;
    packet1.sue_osc_fails = packet_in.sue_osc_fails;
    packet1.sue_imu_velocity_x  = packet_in.sue_imu_velocity_x;
    packet1.sue_imu_velocity_y  = packet_in.sue_imu_velocity_y;
    packet1.sue_imu_velocity_z  = packet_in.sue_imu_velocity_z;
    packet1.sue_waypoint_goal_x = packet_in.sue_waypoint_goal_x;
    packet1.sue_waypoint_goal_y = packet_in.sue_waypoint_goal_y;
    packet1.sue_waypoint_goal_z = packet_in.sue_waypoint_goal_z;
    packet1.sue_aero_x            = packet_in.sue_aero_x;
    packet1.sue_aero_y            = packet_in.sue_aero_y;
    packet1.sue_aero_z            = packet_in.sue_aero_z;
    packet1.sue_barom_temp        = packet_in.sue_barom_temp;
    packet1.sue_bat_volt          = packet_in.sue_bat_volt;
    packet1.sue_bat_amp           = packet_in.sue_bat_amp;
    packet1.sue_bat_amp_hours     = packet_in.sue_bat_amp_hours;
    packet1.sue_desired_height    = packet_in.sue_desired_height;
    packet1.sue_memory_stack_free = packet_in.sue_memory_stack_free;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F2_B_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F2_B_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f2_b_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_serial_udb_extra_f2_b_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f2_b_pack(system_id, component_id, &msg, packet1.sue_time, packet1.sue_pwm_input_1, packet1.sue_pwm_input_2, packet1.sue_pwm_input_3, packet1.sue_pwm_input_4, packet1.sue_pwm_input_5, packet1.sue_pwm_input_6, packet1.sue_pwm_input_7, packet1.sue_pwm_input_8, packet1.sue_pwm_input_9, packet1.sue_pwm_input_10, packet1.sue_pwm_input_11, packet1.sue_pwm_input_12, packet1.sue_pwm_output_1, packet1.sue_pwm_output_2, packet1.sue_pwm_output_3, packet1.sue_pwm_output_4, packet1.sue_pwm_output_5, packet1.sue_pwm_output_6, packet1.sue_pwm_output_7, packet1.sue_pwm_output_8, packet1.sue_pwm_output_9, packet1.sue_pwm_output_10, packet1.sue_pwm_output_11, packet1.sue_pwm_output_12, packet1.sue_imu_location_x, packet1.sue_imu_location_y, packet1.sue_imu_location_z, packet1.sue_location_error_earth_x, packet1.sue_location_error_earth_y, packet1.sue_location_error_earth_z, packet1.sue_flags, packet1.sue_osc_fails, packet1.sue_imu_velocity_x, packet1.sue_imu_velocity_y, packet1.sue_imu_velocity_z, packet1.sue_waypoint_goal_x, packet1.sue_waypoint_goal_y, packet1.sue_waypoint_goal_z, packet1.sue_aero_x, packet1.sue_aero_y, packet1.sue_aero_z, packet1.sue_barom_temp, packet1.sue_barom_press, packet1.sue_barom_alt, packet1.sue_bat_volt, packet1.sue_bat_amp, packet1.sue_bat_amp_hours, packet1.sue_desired_height, packet1.sue_memory_stack_free);
    mavlink_msg_serial_udb_extra_f2_b_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f2_b_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.sue_time, packet1.sue_pwm_input_1, packet1.sue_pwm_input_2, packet1.sue_pwm_input_3, packet1.sue_pwm_input_4, packet1.sue_pwm_input_5, packet1.sue_pwm_input_6, packet1.sue_pwm_input_7, packet1.sue_pwm_input_8, packet1.sue_pwm_input_9, packet1.sue_pwm_input_10, packet1.sue_pwm_input_11, packet1.sue_pwm_input_12, packet1.sue_pwm_output_1, packet1.sue_pwm_output_2, packet1.sue_pwm_output_3, packet1.sue_pwm_output_4, packet1.sue_pwm_output_5, packet1.sue_pwm_output_6, packet1.sue_pwm_output_7, packet1.sue_pwm_output_8, packet1.sue_pwm_output_9, packet1.sue_pwm_output_10, packet1.sue_pwm_output_11, packet1.sue_pwm_output_12, packet1.sue_imu_location_x, packet1.sue_imu_location_y, packet1.sue_imu_location_z, packet1.sue_location_error_earth_x, packet1.sue_location_error_earth_y, packet1.sue_location_error_earth_z, packet1.sue_flags, packet1.sue_osc_fails, packet1.sue_imu_velocity_x, packet1.sue_imu_velocity_y, packet1.sue_imu_velocity_z, packet1.sue_waypoint_goal_x, packet1.sue_waypoint_goal_y, packet1.sue_waypoint_goal_z, packet1.sue_aero_x, packet1.sue_aero_y, packet1.sue_aero_z, packet1.sue_barom_temp, packet1.sue_barom_press, packet1.sue_barom_alt, packet1.sue_bat_volt, packet1.sue_bat_amp, packet1.sue_bat_amp_hours, packet1.sue_desired_height, packet1.sue_memory_stack_free);
    mavlink_msg_serial_udb_extra_f2_b_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_serial_udb_extra_f2_b_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f2_b_send(MAVLINK_COMM_1, packet1.sue_time, packet1.sue_pwm_input_1, packet1.sue_pwm_input_2, packet1.sue_pwm_input_3, packet1.sue_pwm_input_4, packet1.sue_pwm_input_5, packet1.sue_pwm_input_6, packet1.sue_pwm_input_7, packet1.sue_pwm_input_8, packet1.sue_pwm_input_9, packet1.sue_pwm_input_10, packet1.sue_pwm_input_11, packet1.sue_pwm_input_12, packet1.sue_pwm_output_1, packet1.sue_pwm_output_2, packet1.sue_pwm_output_3, packet1.sue_pwm_output_4, packet1.sue_pwm_output_5, packet1.sue_pwm_output_6, packet1.sue_pwm_output_7, packet1.sue_pwm_output_8, packet1.sue_pwm_output_9, packet1.sue_pwm_output_10, packet1.sue_pwm_output_11, packet1.sue_pwm_output_12, packet1.sue_imu_location_x, packet1.sue_imu_location_y, packet1.sue_imu_location_z, packet1.sue_location_error_earth_x, packet1.sue_location_error_earth_y, packet1.sue_location_error_earth_z, packet1.sue_flags, packet1.sue_osc_fails, packet1.sue_imu_velocity_x, packet1.sue_imu_velocity_y, packet1.sue_imu_velocity_z, packet1.sue_waypoint_goal_x, packet1.sue_waypoint_goal_y, packet1.sue_waypoint_goal_z, packet1.sue_aero_x, packet1.sue_aero_y, packet1.sue_aero_z, packet1.sue_barom_temp, packet1.sue_barom_press, packet1.sue_barom_alt, packet1.sue_bat_volt, packet1.sue_bat_amp, packet1.sue_bat_amp_hours, packet1.sue_desired_height, packet1.sue_memory_stack_free);
    mavlink_msg_serial_udb_extra_f2_b_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SERIAL_UDB_EXTRA_F2_B") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F2_B) != NULL);
#endif
}

static void mavlink_test_serial_udb_extra_f4(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F4 >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_serial_udb_extra_f4_t packet_in = {
        5, 72, 139, 206, 17, 84, 151, 218, 29, 96
    };
    mavlink_serial_udb_extra_f4_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.sue_ROLL_STABILIZATION_AILERONS = packet_in.sue_ROLL_STABILIZATION_AILERONS;
    packet1.sue_ROLL_STABILIZATION_RUDDER   = packet_in.sue_ROLL_STABILIZATION_RUDDER;
    packet1.sue_PITCH_STABILIZATION = packet_in.sue_PITCH_STABILIZATION;
    packet1.sue_YAW_STABILIZATION_RUDDER    = packet_in.sue_YAW_STABILIZATION_RUDDER;
    packet1.sue_YAW_STABILIZATION_AILERON   = packet_in.sue_YAW_STABILIZATION_AILERON;
    packet1.sue_AILERON_NAVIGATION = packet_in.sue_AILERON_NAVIGATION;
    packet1.sue_RUDDER_NAVIGATION = packet_in.sue_RUDDER_NAVIGATION;
    packet1.sue_ALTITUDEHOLD_STABILIZED     = packet_in.sue_ALTITUDEHOLD_STABILIZED;
    packet1.sue_ALTITUDEHOLD_WAYPOINT = packet_in.sue_ALTITUDEHOLD_WAYPOINT;
    packet1.sue_RACING_MODE = packet_in.sue_RACING_MODE;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F4_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F4_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f4_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_serial_udb_extra_f4_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f4_pack(system_id, component_id, &msg, packet1.sue_ROLL_STABILIZATION_AILERONS, packet1.sue_ROLL_STABILIZATION_RUDDER, packet1.sue_PITCH_STABILIZATION, packet1.sue_YAW_STABILIZATION_RUDDER, packet1.sue_YAW_STABILIZATION_AILERON, packet1.sue_AILERON_NAVIGATION, packet1.sue_RUDDER_NAVIGATION, packet1.sue_ALTITUDEHOLD_STABILIZED, packet1.sue_ALTITUDEHOLD_WAYPOINT, packet1.sue_RACING_MODE);
    mavlink_msg_serial_udb_extra_f4_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f4_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.sue_ROLL_STABILIZATION_AILERONS, packet1.sue_ROLL_STABILIZATION_RUDDER, packet1.sue_PITCH_STABILIZATION, packet1.sue_YAW_STABILIZATION_RUDDER, packet1.sue_YAW_STABILIZATION_AILERON, packet1.sue_AILERON_NAVIGATION, packet1.sue_RUDDER_NAVIGATION, packet1.sue_ALTITUDEHOLD_STABILIZED, packet1.sue_ALTITUDEHOLD_WAYPOINT, packet1.sue_RACING_MODE);
    mavlink_msg_serial_udb_extra_f4_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_serial_udb_extra_f4_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f4_send(MAVLINK_COMM_1, packet1.sue_ROLL_STABILIZATION_AILERONS, packet1.sue_ROLL_STABILIZATION_RUDDER, packet1.sue_PITCH_STABILIZATION, packet1.sue_YAW_STABILIZATION_RUDDER, packet1.sue_YAW_STABILIZATION_AILERON, packet1.sue_AILERON_NAVIGATION, packet1.sue_RUDDER_NAVIGATION, packet1.sue_ALTITUDEHOLD_STABILIZED, packet1.sue_ALTITUDEHOLD_WAYPOINT, packet1.sue_RACING_MODE);
    mavlink_msg_serial_udb_extra_f4_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SERIAL_UDB_EXTRA_F4") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F4) != NULL);
#endif
}

static void mavlink_test_serial_udb_extra_f5(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F5 >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_serial_udb_extra_f5_t packet_in = {
        17.0, 45.0, 73.0, 101.0
    };
    mavlink_serial_udb_extra_f5_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.sue_YAWKP_AILERON = packet_in.sue_YAWKP_AILERON;
    packet1.sue_YAWKD_AILERON = packet_in.sue_YAWKD_AILERON;
    packet1.sue_ROLLKP = packet_in.sue_ROLLKP;
    packet1.sue_ROLLKD = packet_in.sue_ROLLKD;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F5_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F5_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f5_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_serial_udb_extra_f5_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f5_pack(system_id, component_id, &msg, packet1.sue_YAWKP_AILERON, packet1.sue_YAWKD_AILERON, packet1.sue_ROLLKP, packet1.sue_ROLLKD);
    mavlink_msg_serial_udb_extra_f5_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f5_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.sue_YAWKP_AILERON, packet1.sue_YAWKD_AILERON, packet1.sue_ROLLKP, packet1.sue_ROLLKD);
    mavlink_msg_serial_udb_extra_f5_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_serial_udb_extra_f5_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f5_send(MAVLINK_COMM_1, packet1.sue_YAWKP_AILERON, packet1.sue_YAWKD_AILERON, packet1.sue_ROLLKP, packet1.sue_ROLLKD);
    mavlink_msg_serial_udb_extra_f5_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SERIAL_UDB_EXTRA_F5") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F5) != NULL);
#endif
}

static void mavlink_test_serial_udb_extra_f6(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F6 >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_serial_udb_extra_f6_t packet_in = {
        17.0, 45.0, 73.0, 101.0, 129.0
    };
    mavlink_serial_udb_extra_f6_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.sue_PITCHGAIN       = packet_in.sue_PITCHGAIN;
    packet1.sue_PITCHKD         = packet_in.sue_PITCHKD;
    packet1.sue_RUDDER_ELEV_MIX = packet_in.sue_RUDDER_ELEV_MIX;
    packet1.sue_ROLL_ELEV_MIX   = packet_in.sue_ROLL_ELEV_MIX;
    packet1.sue_ELEVATOR_BOOST  = packet_in.sue_ELEVATOR_BOOST;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F6_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F6_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f6_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_serial_udb_extra_f6_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f6_pack(system_id, component_id, &msg, packet1.sue_PITCHGAIN, packet1.sue_PITCHKD, packet1.sue_RUDDER_ELEV_MIX, packet1.sue_ROLL_ELEV_MIX, packet1.sue_ELEVATOR_BOOST);
    mavlink_msg_serial_udb_extra_f6_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f6_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.sue_PITCHGAIN, packet1.sue_PITCHKD, packet1.sue_RUDDER_ELEV_MIX, packet1.sue_ROLL_ELEV_MIX, packet1.sue_ELEVATOR_BOOST);
    mavlink_msg_serial_udb_extra_f6_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_serial_udb_extra_f6_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f6_send(MAVLINK_COMM_1, packet1.sue_PITCHGAIN, packet1.sue_PITCHKD, packet1.sue_RUDDER_ELEV_MIX, packet1.sue_ROLL_ELEV_MIX, packet1.sue_ELEVATOR_BOOST);
    mavlink_msg_serial_udb_extra_f6_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SERIAL_UDB_EXTRA_F6") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F6) != NULL);
#endif
}

static void mavlink_test_serial_udb_extra_f7(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F7 >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_serial_udb_extra_f7_t packet_in = {
        17.0, 45.0, 73.0, 101.0, 129.0, 157.0
    };
    mavlink_serial_udb_extra_f7_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.sue_YAWKP_RUDDER   = packet_in.sue_YAWKP_RUDDER;
    packet1.sue_YAWKD_RUDDER   = packet_in.sue_YAWKD_RUDDER;
    packet1.sue_ROLLKP_RUDDER  = packet_in.sue_ROLLKP_RUDDER;
    packet1.sue_ROLLKD_RUDDER  = packet_in.sue_ROLLKD_RUDDER;
    packet1.sue_RUDDER_BOOST   = packet_in.sue_RUDDER_BOOST;
    packet1.sue_RTL_PITCH_DOWN = packet_in.sue_RTL_PITCH_DOWN;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F7_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F7_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f7_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_serial_udb_extra_f7_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f7_pack(system_id, component_id, &msg, packet1.sue_YAWKP_RUDDER, packet1.sue_YAWKD_RUDDER, packet1.sue_ROLLKP_RUDDER, packet1.sue_ROLLKD_RUDDER, packet1.sue_RUDDER_BOOST, packet1.sue_RTL_PITCH_DOWN);
    mavlink_msg_serial_udb_extra_f7_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f7_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.sue_YAWKP_RUDDER, packet1.sue_YAWKD_RUDDER, packet1.sue_ROLLKP_RUDDER, packet1.sue_ROLLKD_RUDDER, packet1.sue_RUDDER_BOOST, packet1.sue_RTL_PITCH_DOWN);
    mavlink_msg_serial_udb_extra_f7_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_serial_udb_extra_f7_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f7_send(MAVLINK_COMM_1, packet1.sue_YAWKP_RUDDER, packet1.sue_YAWKD_RUDDER, packet1.sue_ROLLKP_RUDDER, packet1.sue_ROLLKD_RUDDER, packet1.sue_RUDDER_BOOST, packet1.sue_RTL_PITCH_DOWN);
    mavlink_msg_serial_udb_extra_f7_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SERIAL_UDB_EXTRA_F7") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F7) != NULL);
#endif
}

static void mavlink_test_serial_udb_extra_f8(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F8 >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_serial_udb_extra_f8_t packet_in = {
        17.0, 45.0, 73.0, 101.0, 129.0, 157.0, 185.0
    };
    mavlink_serial_udb_extra_f8_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.sue_HEIGHT_TARGET_MAX     = packet_in.sue_HEIGHT_TARGET_MAX;
    packet1.sue_HEIGHT_TARGET_MIN     = packet_in.sue_HEIGHT_TARGET_MIN;
    packet1.sue_ALT_HOLD_THROTTLE_MIN = packet_in.sue_ALT_HOLD_THROTTLE_MIN;
    packet1.sue_ALT_HOLD_THROTTLE_MAX = packet_in.sue_ALT_HOLD_THROTTLE_MAX;
    packet1.sue_ALT_HOLD_PITCH_MIN    = packet_in.sue_ALT_HOLD_PITCH_MIN;
    packet1.sue_ALT_HOLD_PITCH_MAX    = packet_in.sue_ALT_HOLD_PITCH_MAX;
    packet1.sue_ALT_HOLD_PITCH_HIGH   = packet_in.sue_ALT_HOLD_PITCH_HIGH;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F8_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F8_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f8_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_serial_udb_extra_f8_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f8_pack(system_id, component_id, &msg, packet1.sue_HEIGHT_TARGET_MAX, packet1.sue_HEIGHT_TARGET_MIN, packet1.sue_ALT_HOLD_THROTTLE_MIN, packet1.sue_ALT_HOLD_THROTTLE_MAX, packet1.sue_ALT_HOLD_PITCH_MIN, packet1.sue_ALT_HOLD_PITCH_MAX, packet1.sue_ALT_HOLD_PITCH_HIGH);
    mavlink_msg_serial_udb_extra_f8_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f8_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.sue_HEIGHT_TARGET_MAX, packet1.sue_HEIGHT_TARGET_MIN, packet1.sue_ALT_HOLD_THROTTLE_MIN, packet1.sue_ALT_HOLD_THROTTLE_MAX, packet1.sue_ALT_HOLD_PITCH_MIN, packet1.sue_ALT_HOLD_PITCH_MAX, packet1.sue_ALT_HOLD_PITCH_HIGH);
    mavlink_msg_serial_udb_extra_f8_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_serial_udb_extra_f8_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f8_send(MAVLINK_COMM_1, packet1.sue_HEIGHT_TARGET_MAX, packet1.sue_HEIGHT_TARGET_MIN, packet1.sue_ALT_HOLD_THROTTLE_MIN, packet1.sue_ALT_HOLD_THROTTLE_MAX, packet1.sue_ALT_HOLD_PITCH_MIN, packet1.sue_ALT_HOLD_PITCH_MAX, packet1.sue_ALT_HOLD_PITCH_HIGH);
    mavlink_msg_serial_udb_extra_f8_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SERIAL_UDB_EXTRA_F8") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F8) != NULL);
#endif
}

static void mavlink_test_serial_udb_extra_f13(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F13 >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_serial_udb_extra_f13_t packet_in = {
        963497464, 963497672, 963497880, 17859
    };
    mavlink_serial_udb_extra_f13_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.sue_lat_origin = packet_in.sue_lat_origin;
    packet1.sue_lon_origin = packet_in.sue_lon_origin;
    packet1.sue_alt_origin = packet_in.sue_alt_origin;
    packet1.sue_week_no    = packet_in.sue_week_no;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F13_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F13_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f13_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_serial_udb_extra_f13_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f13_pack(system_id, component_id, &msg, packet1.sue_week_no, packet1.sue_lat_origin, packet1.sue_lon_origin, packet1.sue_alt_origin);
    mavlink_msg_serial_udb_extra_f13_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f13_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.sue_week_no, packet1.sue_lat_origin, packet1.sue_lon_origin, packet1.sue_alt_origin);
    mavlink_msg_serial_udb_extra_f13_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_serial_udb_extra_f13_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f13_send(MAVLINK_COMM_1, packet1.sue_week_no, packet1.sue_lat_origin, packet1.sue_lon_origin, packet1.sue_alt_origin);
    mavlink_msg_serial_udb_extra_f13_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SERIAL_UDB_EXTRA_F13") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F13) != NULL);
#endif
}

static void mavlink_test_serial_udb_extra_f14(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F14 >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_serial_udb_extra_f14_t packet_in = {
        963497464, 17443, 17547, 17651, 163, 230, 41, 108, 175, 242, 53
    };
    mavlink_serial_udb_extra_f14_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.sue_TRAP_SOURCE      = packet_in.sue_TRAP_SOURCE;
    packet1.sue_RCON = packet_in.sue_RCON;
    packet1.sue_TRAP_FLAGS       = packet_in.sue_TRAP_FLAGS;
    packet1.sue_osc_fail_count   = packet_in.sue_osc_fail_count;
    packet1.sue_WIND_ESTIMATION  = packet_in.sue_WIND_ESTIMATION;
    packet1.sue_GPS_TYPE = packet_in.sue_GPS_TYPE;
    packet1.sue_DR = packet_in.sue_DR;
    packet1.sue_BOARD_TYPE       = packet_in.sue_BOARD_TYPE;
    packet1.sue_AIRFRAME = packet_in.sue_AIRFRAME;
    packet1.sue_CLOCK_CONFIG     = packet_in.sue_CLOCK_CONFIG;
    packet1.sue_FLIGHT_PLAN_TYPE = packet_in.sue_FLIGHT_PLAN_TYPE;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F14_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F14_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f14_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_serial_udb_extra_f14_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f14_pack(system_id, component_id, &msg, packet1.sue_WIND_ESTIMATION, packet1.sue_GPS_TYPE, packet1.sue_DR, packet1.sue_BOARD_TYPE, packet1.sue_AIRFRAME, packet1.sue_RCON, packet1.sue_TRAP_FLAGS, packet1.sue_TRAP_SOURCE, packet1.sue_osc_fail_count, packet1.sue_CLOCK_CONFIG, packet1.sue_FLIGHT_PLAN_TYPE);
    mavlink_msg_serial_udb_extra_f14_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f14_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.sue_WIND_ESTIMATION, packet1.sue_GPS_TYPE, packet1.sue_DR, packet1.sue_BOARD_TYPE, packet1.sue_AIRFRAME, packet1.sue_RCON, packet1.sue_TRAP_FLAGS, packet1.sue_TRAP_SOURCE, packet1.sue_osc_fail_count, packet1.sue_CLOCK_CONFIG, packet1.sue_FLIGHT_PLAN_TYPE);
    mavlink_msg_serial_udb_extra_f14_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_serial_udb_extra_f14_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f14_send(MAVLINK_COMM_1, packet1.sue_WIND_ESTIMATION, packet1.sue_GPS_TYPE, packet1.sue_DR, packet1.sue_BOARD_TYPE, packet1.sue_AIRFRAME, packet1.sue_RCON, packet1.sue_TRAP_FLAGS, packet1.sue_TRAP_SOURCE, packet1.sue_osc_fail_count, packet1.sue_CLOCK_CONFIG, packet1.sue_FLIGHT_PLAN_TYPE);
    mavlink_msg_serial_udb_extra_f14_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SERIAL_UDB_EXTRA_F14") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F14) != NULL);
#endif
}

static void mavlink_test_serial_udb_extra_f15(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F15 >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_serial_udb_extra_f15_t packet_in = {
        { 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44 }, { 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144 }
    };
    mavlink_serial_udb_extra_f15_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));

    mav_array_memcpy(packet1.sue_ID_VEHICLE_MODEL_NAME, packet_in.sue_ID_VEHICLE_MODEL_NAME, sizeof(uint8_t) * 40);
    mav_array_memcpy(packet1.sue_ID_VEHICLE_REGISTRATION, packet_in.sue_ID_VEHICLE_REGISTRATION, sizeof(uint8_t) * 20);

#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F15_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F15_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f15_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_serial_udb_extra_f15_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f15_pack(system_id, component_id, &msg, packet1.sue_ID_VEHICLE_MODEL_NAME, packet1.sue_ID_VEHICLE_REGISTRATION);
    mavlink_msg_serial_udb_extra_f15_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f15_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.sue_ID_VEHICLE_MODEL_NAME, packet1.sue_ID_VEHICLE_REGISTRATION);
    mavlink_msg_serial_udb_extra_f15_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_serial_udb_extra_f15_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f15_send(MAVLINK_COMM_1, packet1.sue_ID_VEHICLE_MODEL_NAME, packet1.sue_ID_VEHICLE_REGISTRATION);
    mavlink_msg_serial_udb_extra_f15_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SERIAL_UDB_EXTRA_F15") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F15) != NULL);
#endif
}

static void mavlink_test_serial_udb_extra_f16(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F16 >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_serial_udb_extra_f16_t packet_in = {
        { 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44 }, { 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194 }
    };
    mavlink_serial_udb_extra_f16_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));

    mav_array_memcpy(packet1.sue_ID_LEAD_PILOT, packet_in.sue_ID_LEAD_PILOT, sizeof(uint8_t) * 40);
    mav_array_memcpy(packet1.sue_ID_DIY_DRONES_URL, packet_in.sue_ID_DIY_DRONES_URL, sizeof(uint8_t) * 70);

#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F16_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F16_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f16_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_serial_udb_extra_f16_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f16_pack(system_id, component_id, &msg, packet1.sue_ID_LEAD_PILOT, packet1.sue_ID_DIY_DRONES_URL);
    mavlink_msg_serial_udb_extra_f16_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f16_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.sue_ID_LEAD_PILOT, packet1.sue_ID_DIY_DRONES_URL);
    mavlink_msg_serial_udb_extra_f16_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_serial_udb_extra_f16_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f16_send(MAVLINK_COMM_1, packet1.sue_ID_LEAD_PILOT, packet1.sue_ID_DIY_DRONES_URL);
    mavlink_msg_serial_udb_extra_f16_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SERIAL_UDB_EXTRA_F16") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F16) != NULL);
#endif
}

static void mavlink_test_altitudes(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ALTITUDES >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_altitudes_t packet_in = {
        963497464, 963497672, 963497880, 963498088, 963498296, 963498504, 963498712
    };
    mavlink_altitudes_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.time_boot_ms     = packet_in.time_boot_ms;
    packet1.alt_gps = packet_in.alt_gps;
    packet1.alt_imu = packet_in.alt_imu;
    packet1.alt_barometric   = packet_in.alt_barometric;
    packet1.alt_optical_flow = packet_in.alt_optical_flow;
    packet1.alt_range_finder = packet_in.alt_range_finder;
    packet1.alt_extra = packet_in.alt_extra;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_ALTITUDES_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_ALTITUDES_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_altitudes_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_altitudes_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_altitudes_pack(system_id, component_id, &msg, packet1.time_boot_ms, packet1.alt_gps, packet1.alt_imu, packet1.alt_barometric, packet1.alt_optical_flow, packet1.alt_range_finder, packet1.alt_extra);
    mavlink_msg_altitudes_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_altitudes_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.time_boot_ms, packet1.alt_gps, packet1.alt_imu, packet1.alt_barometric, packet1.alt_optical_flow, packet1.alt_range_finder, packet1.alt_extra);
    mavlink_msg_altitudes_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_altitudes_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_altitudes_send(MAVLINK_COMM_1, packet1.time_boot_ms, packet1.alt_gps, packet1.alt_imu, packet1.alt_barometric, packet1.alt_optical_flow, packet1.alt_range_finder, packet1.alt_extra);
    mavlink_msg_altitudes_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ALTITUDES") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ALTITUDES) != NULL);
#endif
}

static void mavlink_test_airspeeds(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_AIRSPEEDS >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_airspeeds_t packet_in = {
        963497464, 17443, 17547, 17651, 17755, 17859, 17963
    };
    mavlink_airspeeds_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.time_boot_ms        = packet_in.time_boot_ms;
    packet1.airspeed_imu        = packet_in.airspeed_imu;
    packet1.airspeed_pitot      = packet_in.airspeed_pitot;
    packet1.airspeed_hot_wire   = packet_in.airspeed_hot_wire;
    packet1.airspeed_ultrasonic = packet_in.airspeed_ultrasonic;
    packet1.aoa = packet_in.aoa;
    packet1.aoy = packet_in.aoy;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_AIRSPEEDS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_AIRSPEEDS_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_airspeeds_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_airspeeds_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_airspeeds_pack(system_id, component_id, &msg, packet1.time_boot_ms, packet1.airspeed_imu, packet1.airspeed_pitot, packet1.airspeed_hot_wire, packet1.airspeed_ultrasonic, packet1.aoa, packet1.aoy);
    mavlink_msg_airspeeds_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_airspeeds_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.time_boot_ms, packet1.airspeed_imu, packet1.airspeed_pitot, packet1.airspeed_hot_wire, packet1.airspeed_ultrasonic, packet1.aoa, packet1.aoy);
    mavlink_msg_airspeeds_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_airspeeds_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_airspeeds_send(MAVLINK_COMM_1, packet1.time_boot_ms, packet1.airspeed_imu, packet1.airspeed_pitot, packet1.airspeed_hot_wire, packet1.airspeed_ultrasonic, packet1.aoa, packet1.aoy);
    mavlink_msg_airspeeds_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("AIRSPEEDS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_AIRSPEEDS) != NULL);
#endif
}

static void mavlink_test_serial_udb_extra_f17(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F17 >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_serial_udb_extra_f17_t packet_in = {
        17.0, 45.0, 73.0
    };
    mavlink_serial_udb_extra_f17_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.sue_feed_forward  = packet_in.sue_feed_forward;
    packet1.sue_turn_rate_nav = packet_in.sue_turn_rate_nav;
    packet1.sue_turn_rate_fbw = packet_in.sue_turn_rate_fbw;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F17_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F17_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f17_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_serial_udb_extra_f17_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f17_pack(system_id, component_id, &msg, packet1.sue_feed_forward, packet1.sue_turn_rate_nav, packet1.sue_turn_rate_fbw);
    mavlink_msg_serial_udb_extra_f17_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f17_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.sue_feed_forward, packet1.sue_turn_rate_nav, packet1.sue_turn_rate_fbw);
    mavlink_msg_serial_udb_extra_f17_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_serial_udb_extra_f17_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f17_send(MAVLINK_COMM_1, packet1.sue_feed_forward, packet1.sue_turn_rate_nav, packet1.sue_turn_rate_fbw);
    mavlink_msg_serial_udb_extra_f17_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SERIAL_UDB_EXTRA_F17") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F17) != NULL);
#endif
}

static void mavlink_test_serial_udb_extra_f18(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F18 >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_serial_udb_extra_f18_t packet_in = {
        17.0, 45.0, 73.0, 101.0, 129.0
    };
    mavlink_serial_udb_extra_f18_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.angle_of_attack_normal   = packet_in.angle_of_attack_normal;
    packet1.angle_of_attack_inverted = packet_in.angle_of_attack_inverted;
    packet1.elevator_trim_normal     = packet_in.elevator_trim_normal;
    packet1.elevator_trim_inverted   = packet_in.elevator_trim_inverted;
    packet1.reference_speed = packet_in.reference_speed;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F18_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F18_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f18_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_serial_udb_extra_f18_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f18_pack(system_id, component_id, &msg, packet1.angle_of_attack_normal, packet1.angle_of_attack_inverted, packet1.elevator_trim_normal, packet1.elevator_trim_inverted, packet1.reference_speed);
    mavlink_msg_serial_udb_extra_f18_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f18_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.angle_of_attack_normal, packet1.angle_of_attack_inverted, packet1.elevator_trim_normal, packet1.elevator_trim_inverted, packet1.reference_speed);
    mavlink_msg_serial_udb_extra_f18_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_serial_udb_extra_f18_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f18_send(MAVLINK_COMM_1, packet1.angle_of_attack_normal, packet1.angle_of_attack_inverted, packet1.elevator_trim_normal, packet1.elevator_trim_inverted, packet1.reference_speed);
    mavlink_msg_serial_udb_extra_f18_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SERIAL_UDB_EXTRA_F18") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F18) != NULL);
#endif
}

static void mavlink_test_serial_udb_extra_f19(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F19 >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_serial_udb_extra_f19_t packet_in = {
        5, 72, 139, 206, 17, 84, 151, 218
    };
    mavlink_serial_udb_extra_f19_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.sue_aileron_output_channel  = packet_in.sue_aileron_output_channel;
    packet1.sue_aileron_reversed = packet_in.sue_aileron_reversed;
    packet1.sue_elevator_output_channel = packet_in.sue_elevator_output_channel;
    packet1.sue_elevator_reversed = packet_in.sue_elevator_reversed;
    packet1.sue_throttle_output_channel = packet_in.sue_throttle_output_channel;
    packet1.sue_throttle_reversed = packet_in.sue_throttle_reversed;
    packet1.sue_rudder_output_channel   = packet_in.sue_rudder_output_channel;
    packet1.sue_rudder_reversed = packet_in.sue_rudder_reversed;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F19_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F19_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f19_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_serial_udb_extra_f19_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f19_pack(system_id, component_id, &msg, packet1.sue_aileron_output_channel, packet1.sue_aileron_reversed, packet1.sue_elevator_output_channel, packet1.sue_elevator_reversed, packet1.sue_throttle_output_channel, packet1.sue_throttle_reversed, packet1.sue_rudder_output_channel, packet1.sue_rudder_reversed);
    mavlink_msg_serial_udb_extra_f19_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f19_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.sue_aileron_output_channel, packet1.sue_aileron_reversed, packet1.sue_elevator_output_channel, packet1.sue_elevator_reversed, packet1.sue_throttle_output_channel, packet1.sue_throttle_reversed, packet1.sue_rudder_output_channel, packet1.sue_rudder_reversed);
    mavlink_msg_serial_udb_extra_f19_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_serial_udb_extra_f19_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f19_send(MAVLINK_COMM_1, packet1.sue_aileron_output_channel, packet1.sue_aileron_reversed, packet1.sue_elevator_output_channel, packet1.sue_elevator_reversed, packet1.sue_throttle_output_channel, packet1.sue_throttle_reversed, packet1.sue_rudder_output_channel, packet1.sue_rudder_reversed);
    mavlink_msg_serial_udb_extra_f19_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SERIAL_UDB_EXTRA_F19") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F19) != NULL);
#endif
}

static void mavlink_test_serial_udb_extra_f20(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F20 >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_serial_udb_extra_f20_t packet_in = {
        17235, 17339, 17443, 17547, 17651, 17755, 17859, 17963, 18067, 18171, 18275, 18379, 77
    };
    mavlink_serial_udb_extra_f20_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.sue_trim_value_input_1  = packet_in.sue_trim_value_input_1;
    packet1.sue_trim_value_input_2  = packet_in.sue_trim_value_input_2;
    packet1.sue_trim_value_input_3  = packet_in.sue_trim_value_input_3;
    packet1.sue_trim_value_input_4  = packet_in.sue_trim_value_input_4;
    packet1.sue_trim_value_input_5  = packet_in.sue_trim_value_input_5;
    packet1.sue_trim_value_input_6  = packet_in.sue_trim_value_input_6;
    packet1.sue_trim_value_input_7  = packet_in.sue_trim_value_input_7;
    packet1.sue_trim_value_input_8  = packet_in.sue_trim_value_input_8;
    packet1.sue_trim_value_input_9  = packet_in.sue_trim_value_input_9;
    packet1.sue_trim_value_input_10 = packet_in.sue_trim_value_input_10;
    packet1.sue_trim_value_input_11 = packet_in.sue_trim_value_input_11;
    packet1.sue_trim_value_input_12 = packet_in.sue_trim_value_input_12;
    packet1.sue_number_of_inputs    = packet_in.sue_number_of_inputs;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F20_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F20_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f20_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_serial_udb_extra_f20_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f20_pack(system_id, component_id, &msg, packet1.sue_number_of_inputs, packet1.sue_trim_value_input_1, packet1.sue_trim_value_input_2, packet1.sue_trim_value_input_3, packet1.sue_trim_value_input_4, packet1.sue_trim_value_input_5, packet1.sue_trim_value_input_6, packet1.sue_trim_value_input_7, packet1.sue_trim_value_input_8, packet1.sue_trim_value_input_9, packet1.sue_trim_value_input_10, packet1.sue_trim_value_input_11, packet1.sue_trim_value_input_12);
    mavlink_msg_serial_udb_extra_f20_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f20_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.sue_number_of_inputs, packet1.sue_trim_value_input_1, packet1.sue_trim_value_input_2, packet1.sue_trim_value_input_3, packet1.sue_trim_value_input_4, packet1.sue_trim_value_input_5, packet1.sue_trim_value_input_6, packet1.sue_trim_value_input_7, packet1.sue_trim_value_input_8, packet1.sue_trim_value_input_9, packet1.sue_trim_value_input_10, packet1.sue_trim_value_input_11, packet1.sue_trim_value_input_12);
    mavlink_msg_serial_udb_extra_f20_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_serial_udb_extra_f20_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f20_send(MAVLINK_COMM_1, packet1.sue_number_of_inputs, packet1.sue_trim_value_input_1, packet1.sue_trim_value_input_2, packet1.sue_trim_value_input_3, packet1.sue_trim_value_input_4, packet1.sue_trim_value_input_5, packet1.sue_trim_value_input_6, packet1.sue_trim_value_input_7, packet1.sue_trim_value_input_8, packet1.sue_trim_value_input_9, packet1.sue_trim_value_input_10, packet1.sue_trim_value_input_11, packet1.sue_trim_value_input_12);
    mavlink_msg_serial_udb_extra_f20_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SERIAL_UDB_EXTRA_F20") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F20) != NULL);
#endif
}

static void mavlink_test_serial_udb_extra_f21(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F21 >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_serial_udb_extra_f21_t packet_in = {
        17235, 17339, 17443, 17547, 17651, 17755
    };
    mavlink_serial_udb_extra_f21_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.sue_accel_x_offset = packet_in.sue_accel_x_offset;
    packet1.sue_accel_y_offset = packet_in.sue_accel_y_offset;
    packet1.sue_accel_z_offset = packet_in.sue_accel_z_offset;
    packet1.sue_gyro_x_offset  = packet_in.sue_gyro_x_offset;
    packet1.sue_gyro_y_offset  = packet_in.sue_gyro_y_offset;
    packet1.sue_gyro_z_offset  = packet_in.sue_gyro_z_offset;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F21_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F21_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f21_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_serial_udb_extra_f21_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f21_pack(system_id, component_id, &msg, packet1.sue_accel_x_offset, packet1.sue_accel_y_offset, packet1.sue_accel_z_offset, packet1.sue_gyro_x_offset, packet1.sue_gyro_y_offset, packet1.sue_gyro_z_offset);
    mavlink_msg_serial_udb_extra_f21_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f21_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.sue_accel_x_offset, packet1.sue_accel_y_offset, packet1.sue_accel_z_offset, packet1.sue_gyro_x_offset, packet1.sue_gyro_y_offset, packet1.sue_gyro_z_offset);
    mavlink_msg_serial_udb_extra_f21_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_serial_udb_extra_f21_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f21_send(MAVLINK_COMM_1, packet1.sue_accel_x_offset, packet1.sue_accel_y_offset, packet1.sue_accel_z_offset, packet1.sue_gyro_x_offset, packet1.sue_gyro_y_offset, packet1.sue_gyro_z_offset);
    mavlink_msg_serial_udb_extra_f21_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SERIAL_UDB_EXTRA_F21") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F21) != NULL);
#endif
}

static void mavlink_test_serial_udb_extra_f22(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
    if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F22 >= 256) {
        return;
    }
#endif
    mavlink_message_t msg;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    uint16_t i;
    mavlink_serial_udb_extra_f22_t packet_in = {
        17235, 17339, 17443, 17547, 17651, 17755
    };
    mavlink_serial_udb_extra_f22_t packet1, packet2;
    memset(&packet1, 0, sizeof(packet1));
    packet1.sue_accel_x_at_calibration = packet_in.sue_accel_x_at_calibration;
    packet1.sue_accel_y_at_calibration = packet_in.sue_accel_y_at_calibration;
    packet1.sue_accel_z_at_calibration = packet_in.sue_accel_z_at_calibration;
    packet1.sue_gyro_x_at_calibration  = packet_in.sue_gyro_x_at_calibration;
    packet1.sue_gyro_y_at_calibration  = packet_in.sue_gyro_y_at_calibration;
    packet1.sue_gyro_z_at_calibration  = packet_in.sue_gyro_z_at_calibration;


#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
        // cope with extensions
        memset(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F22_MIN_LEN + (char *)&packet1, 0, sizeof(packet1) - MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F22_MIN_LEN);
    }
#endif
    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f22_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_serial_udb_extra_f22_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f22_pack(system_id, component_id, &msg, packet1.sue_accel_x_at_calibration, packet1.sue_accel_y_at_calibration, packet1.sue_accel_z_at_calibration, packet1.sue_gyro_x_at_calibration, packet1.sue_gyro_y_at_calibration, packet1.sue_gyro_z_at_calibration);
    mavlink_msg_serial_udb_extra_f22_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f22_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg, packet1.sue_accel_x_at_calibration, packet1.sue_accel_y_at_calibration, packet1.sue_accel_z_at_calibration, packet1.sue_gyro_x_at_calibration, packet1.sue_gyro_y_at_calibration, packet1.sue_gyro_z_at_calibration);
    mavlink_msg_serial_udb_extra_f22_decode(&msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_to_send_buffer(buffer, &msg);
    for (i = 0; i < mavlink_msg_get_send_buffer_length(&msg); i++) {
        comm_send_ch(MAVLINK_COMM_0, buffer[i]);
    }
    mavlink_msg_serial_udb_extra_f22_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

    memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_serial_udb_extra_f22_send(MAVLINK_COMM_1, packet1.sue_accel_x_at_calibration, packet1.sue_accel_y_at_calibration, packet1.sue_accel_z_at_calibration, packet1.sue_gyro_x_at_calibration, packet1.sue_gyro_y_at_calibration, packet1.sue_gyro_z_at_calibration);
    mavlink_msg_serial_udb_extra_f22_decode(last_msg, &packet2);
    MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SERIAL_UDB_EXTRA_F22") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SERIAL_UDB_EXTRA_F22) != NULL);
#endif
}

static void mavlink_test_matrixpilot(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_flexifunction_set(system_id, component_id, last_msg);
    mavlink_test_flexifunction_read_req(system_id, component_id, last_msg);
    mavlink_test_flexifunction_buffer_function(system_id, component_id, last_msg);
    mavlink_test_flexifunction_buffer_function_ack(system_id, component_id, last_msg);
    mavlink_test_flexifunction_directory(system_id, component_id, last_msg);
    mavlink_test_flexifunction_directory_ack(system_id, component_id, last_msg);
    mavlink_test_flexifunction_command(system_id, component_id, last_msg);
    mavlink_test_flexifunction_command_ack(system_id, component_id, last_msg);
    mavlink_test_serial_udb_extra_f2_a(system_id, component_id, last_msg);
    mavlink_test_serial_udb_extra_f2_b(system_id, component_id, last_msg);
    mavlink_test_serial_udb_extra_f4(system_id, component_id, last_msg);
    mavlink_test_serial_udb_extra_f5(system_id, component_id, last_msg);
    mavlink_test_serial_udb_extra_f6(system_id, component_id, last_msg);
    mavlink_test_serial_udb_extra_f7(system_id, component_id, last_msg);
    mavlink_test_serial_udb_extra_f8(system_id, component_id, last_msg);
    mavlink_test_serial_udb_extra_f13(system_id, component_id, last_msg);
    mavlink_test_serial_udb_extra_f14(system_id, component_id, last_msg);
    mavlink_test_serial_udb_extra_f15(system_id, component_id, last_msg);
    mavlink_test_serial_udb_extra_f16(system_id, component_id, last_msg);
    mavlink_test_altitudes(system_id, component_id, last_msg);
    mavlink_test_airspeeds(system_id, component_id, last_msg);
    mavlink_test_serial_udb_extra_f17(system_id, component_id, last_msg);
    mavlink_test_serial_udb_extra_f18(system_id, component_id, last_msg);
    mavlink_test_serial_udb_extra_f19(system_id, component_id, last_msg);
    mavlink_test_serial_udb_extra_f20(system_id, component_id, last_msg);
    mavlink_test_serial_udb_extra_f21(system_id, component_id, last_msg);
    mavlink_test_serial_udb_extra_f22(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MATRIXPILOT_TESTSUITE_H
