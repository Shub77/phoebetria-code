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
    QObject(parent)
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

}

bool Preferences::minimiseToTray(bool defaultVal) const
{

}

bool Preferences::showTrayIconTooltips(bool defaultVal) const
{

}

QString Preferences::startupProfile(QString defaultVal) const
{

}

QString Preferences::shutdownProfile(QString defaultVal) const
{

}


bool Preferences::quitOnCloseButton(bool defaultVal) const
{

}
