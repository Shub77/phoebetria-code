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


/*
 * NOTE: The order (and number) of these strings must correspond with
 *       Preferences::KeyId
 */
const char* preferenceKeyStrings[] =
{
    "MinimiseToTray",
    "ShowToolTipOnMinimise",
    "Interval_GlobalTimer",
    "Interval_FcCommonSettings",
    "Interval_FcAlarmTempAndMaxSpeed",
    "Interval_FcCurrentTempAndSpeed",

    "PrimaryDb_DeleteOnAnyCreateError"
};


/**************************************************************************
 *************************************************************************/

const char* Preferences::m_userPrefsGroup = "UserPrefs/";

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

void Preferences::set(KeyId id, const QVariant& value)
{
    QSettings settings;
    settings.setProperty(propertyName(id).toAscii().constData(), value);
}

QString Preferences::propertyName(KeyId id) const
{
    // TODO Bounds checking may be wise
    QString pname(m_userPrefsGroup);
    pname += preferenceKeyStrings[id];
    return pname;
}
