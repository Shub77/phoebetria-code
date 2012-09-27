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


#include "fanprofiles.h"

#include <QDebug>
#include <QFileInfo>
#include <QDir>

#include "fancontrollerdata.h"
#include "maindb.h"

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

QStringList FanControllerProfile::getProfileNames(void)
{
    MainDb mdb;
    QStringList result = mdb.profileNames();
    if (mdb.lastSqlError().type() != QSqlError::NoError)
    {
        qDebug() << "Error reading profile names."
                 << __FILE__ << ":" << __LINE__;

        // TODO: Implement mechanism for passing error back to caller
    }
    return result;
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
    MainDb mdb;

    return mdb.writeProfile(profileName, *this);
}


bool FanControllerProfile::load(const QString& profileName)
{
#if 0
    m_isAuto = DatabaseManager::readProfile(profileName, "isAuto", 0);
    m_isCelcius = DatabaseManager::readProfile(profileName, "isCelcius", 0);
    m_isAudibleAlarm = DatabaseManager::readProfile(profileName, "isAudibleAlarm", 0);

    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        m_channelSettings[i].alarmTemp = DatabaseManager::readProfile(profileName, "AlarmTempF", i);
        m_channelSettings[i].speed = DatabaseManager::readProfile(profileName, "FanRPM", i);
    }
#endif
    return true;
}

bool FanControllerProfile::erase(const QString& profileName)
{
#if 0
    QSqlError err;
    err = DatabaseManager::eraseProfile(profileName);
    return err.type() == QSqlError::NoError;
#endif
    return true;
}


bool FanControllerProfile::importFromIni(void)
{
    // Get all ini filenames

    // Read each profile

    // Check if in database; if not, add the profile

    return true;
}
