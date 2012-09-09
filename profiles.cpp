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

#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include "profiles.h"
#include "fancontrollerdata.h"
#include "database.h"

FanControllerProfile::FanControllerProfile()
{
    initCommon();
}


void FanControllerProfile::initCommon(void)
{
    QSettings settings(QSettings::IniFormat,
                       QSettings::UserScope,
                       "Phoebetria",
                       "Phoebetria");

    m_defaultProfileLocation = QFileInfo(settings.fileName()).path()
                               + "/Presets/";

    m_isCelcius = false;
    m_isAuto = true;
    m_isAudibleAlarm = true;
}


QString FanControllerProfile::defualtProfileLocation(void) const
{
    return m_defaultProfileLocation;
}

QStringList FanControllerProfile::getProfileNames()
{
    Database m_database;
    QStringList m_Presets = m_database.readProfileNames();

    return m_Presets;
}

/* Set from the current controller settings
 */
void FanControllerProfile::setFromCurrentData(const FanControllerData& data)
{
    m_isCelcius = data.isCelcius();
    m_isAuto = data.isAuto();
    m_isAudibleAlarm = data.isAudibleAlarm();

    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        m_channelSettings[i].alarmTemp = data.alarmTemp(i);

        int speedToSave;

        speedToSave = data.isManualRpmSet(i) ? data.manualRPM(i)
                                             : data.lastRPM(i);

        m_channelSettings[i].speed = speedToSave;
    }
}


bool FanControllerProfile::save(const QString& profileName)
{
    Database m_database;

    m_database.saveProfile(profileName, "isAuto", 0, m_isAuto);
    m_database.saveProfile(profileName, "isCelcius", 0, m_isCelcius);
    m_database.saveProfile(profileName, "isAudibleAlarm", 0, m_isAudibleAlarm);

    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        m_database.saveProfile(profileName, "FanRPM", i, m_channelSettings[i].speed);
        m_database.saveProfile(profileName, "AlarmTempF", i, m_channelSettings[i].alarmTemp);
    }

    return 0;
}


bool FanControllerProfile::load(const QString& profileName)
{
    Database m_database;

    m_isAuto = m_database.readProfile(profileName, "isAuto", 0);
    m_isCelcius = m_database.readProfile(profileName, "isCelcius", 0);
    m_isAudibleAlarm = m_database.readProfile(profileName, "isAudibleAlarm", 0);

    for (int i = 0; i < FC_MAX_CHANNELS; i++) {

        m_channelSettings[i].alarmTemp = m_database.readProfile(profileName, "AlarmTempF", i);
        m_channelSettings[i].speed = m_database.readProfile(profileName, "FanRPM", i);

    }

    return true;
}

