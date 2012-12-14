/*  Copyright 2012 Craig Robbins and Christopher Ferris

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "preferences.h"

#include <QSettings>
#include <QFileInfo>

static const char* key_startMinimised       = "UserPrefs/startMinimised";
static const char* key_minimiseToTray       = "UserPrefs/minimiseToTray";
static const char* key_showTrayIconTT       = "UserPrefs/showTrayIconTooltips";
static const char* key_startupProfile       = "UserPrefs/startupProfile";
static const char* key_shutdownProfile      = "UserPrefs/shutdownProfile";
static const char* key_quitOnCloseButton    = "UserPrefs/quitOnCloseButton";

static const char* keyBase_channelName      = "UserPrefs/channelName";
static const char* keyBase_probeName        = "UserPrefs/probeName";

Preferences::Preferences(QObject *parent) :
    QObject(parent),
    m_settings(QSettings::IniFormat, QSettings::UserScope,
               "Phoebetria", "Phoebetria")

{
}

QString Preferences::filepath(void)
{
    QSettings settings(QSettings::IniFormat,
                       QSettings::UserScope,
                       "Phoebetria",
                       "Phoebetria");
    return QFileInfo(settings.fileName()).path();
}

bool Preferences::startMinimised(bool defaultVal) const
{
    return m_settings.value(key_startMinimised, defaultVal).toBool();
}

bool Preferences::minimiseToTray(bool defaultVal) const
{
    return m_settings.value(key_minimiseToTray, defaultVal).toBool();
}

bool Preferences::showTrayIconTooltips(bool defaultVal) const
{
    return m_settings.value(key_showTrayIconTT, defaultVal).toBool();
}

QString Preferences::startupProfile(QString defaultVal) const
{;
    return m_settings.value(key_startupProfile, defaultVal).toString();
}

QString Preferences::shutdownProfile(QString defaultVal) const
{
    return m_settings.value(key_shutdownProfile, defaultVal).toString();
}

bool Preferences::quitOnCloseButton(bool defaultVal) const
{
    return m_settings.value(key_quitOnCloseButton, defaultVal).toBool();
}

QString Preferences::channelName(unsigned channel, QString defaultVal) const
{
    QString keyName = keyBase_channelName + QString("_") + QString::number(channel);

    return m_settings.value(keyName, defaultVal).toString();
}

QString Preferences::probeName(unsigned channel, QString defaultVal) const
{
    QString keyName = keyBase_probeName + QString("_") + QString::number(channel);

    return m_settings.value(keyName, defaultVal).toString();
}
