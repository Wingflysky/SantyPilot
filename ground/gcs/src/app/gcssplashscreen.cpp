/**
 ******************************************************************************
 *
 * @file       gcssplashscreen.cpp
 * @author     The LibrePilot Project, http://www.librepilot.org Copyright (C) 2015.
 *             The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @addtogroup [Group]
 * @{
 * @addtogroup GCSSplashScreen
 * @{
 * @brief [Brief]
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

#include "gcssplashscreen.h"
#include "version_info/version_info.h"
#include <QDebug>
#include <QApplication>

const QChar CopyrightSymbol(0x00a9);

GCSSplashScreen::GCSSplashScreen() :
    QSplashScreen(), m_pixmap(0), m_painter(0)
{
    setWindowFlags(windowFlags());
    m_pixmap  = new QPixmap(":/app/splash.png");

    m_painter = new QPainter(m_pixmap);
    m_painter->setPen(Qt::darkGray);
    QFont font("Tahoma", 8);
    m_painter->setFont(font);

    m_painter->drawText(375, 226, QString(CopyrightSymbol) +
                        QString(" 2024-2034") +
                        QString(tr(" The %1 Project - All Rights Reserved").arg(ORG_BIG_NAME)));

    m_painter->drawText(375, 242, QString(CopyrightSymbol) +
                        QString(" 2015-2024") +
                        QString(tr(" The LibrePilot Project - All Rights Reserved")));

    m_painter->drawText(375, 258, QString(CopyrightSymbol) +
                        QString(tr(" 2010-2015 The OpenPilot Project - All Rights Reserved")));

    m_painter->drawText(375, 268, 310, 100, Qt::TextWordWrap | Qt::AlignTop | Qt::AlignLeft,
                        QString(tr("GCS Revision - ")) + VersionInfo::revision());
    setPixmap(*m_pixmap);
}

GCSSplashScreen::~GCSSplashScreen()
{}

void GCSSplashScreen::drawMessageText(const QString &message)
{
    QPixmap pix(*m_pixmap);
    QPainter progressPainter(&pix);

    progressPainter.setPen(Qt::yellow);
    QFont font("Tahoma", 13);
    progressPainter.setFont(font);
    progressPainter.drawText(300, 385, message);
    setPixmap(pix);
}

void GCSSplashScreen::showPluginLoadingProgress(ExtensionSystem::PluginSpec *pluginSpec)
{
    QString message(tr("Loading ") + pluginSpec->name() + " plugin...");

    drawMessageText(message);
    qApp->processEvents();
}
