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

/**************************************************************************
 *************************************************************************/
Preferences::Entry::Entry()
{
}


/**************************************************************************
 *************************************************************************/

const QString Preferences::PrefKey::MinimiseToTray = "MinimiseToTray";
const QString Preferences::PrefKey::ShowTooltipOnMinimise = "ShowToolTipOnMinimise";
const QString Preferences::PrefKey::DevicePollTime = "DevicePollTime";

/**************************************************************************
 *************************************************************************/
Preferences::Preferences(QObject *parent) :
    QObject(parent)
{
}

void Preferences::set(const QString& key, int value)
{
    m_prefs.insert(key, value);
}


void Preferences::set(const QString& key, bool value)
{
    m_prefs.insert(key, value);
}


void Preferences::setDefaults(void)
{
    set(PrefKey::MinimiseToTray, true);
    set(PrefKey::ShowTooltipOnMinimise, false);
    set(PrefKey::DevicePollTime, 200);
}

QString Preferences::filepath(void)
{
    QSettings settings(QSettings::IniFormat,
                       QSettings::UserScope,
                       "Phoebetria",
                       "Phoebetria");
    return QFileInfo(settings.fileName()).path();
}
