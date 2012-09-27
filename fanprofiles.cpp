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
#include "dbmanager.h"

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
    return PhoebetriaDbMgr::readProfileNames();
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
#if 0
    PhoebetriaDbMgr::saveProfile(profileName, "isAuto", 0, m_isAuto);
    PhoebetriaDbMgr::saveProfile(profileName, "isCelcius", 0, m_isCelcius);
    PhoebetriaDbMgr::saveProfile(profileName, "isAudibleAlarm", 0, m_isAudibleAlarm);

    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        PhoebetriaDbMgr::saveProfile(profileName, "FanRPM", i, m_channelSettings[i].speed);
        PhoebetriaDbMgr::saveProfile(profileName, "AlarmTempF", i, m_channelSettings[i].alarmTemp);
    }

    return true;
#endif


    PhoebetriaDbMgr db;

    QSqlQuery qry(QSqlDatabase::database(db.connectionName()));

    bool ok;


    ok = qry.exec("select p_id from Profile where name = 'doe';");

    int p_id = ok ? qry.value(0).toInt() : -1;

    if (p_id == -1)
    ok = qry.prepare("insert or replace into Profile "
                     " (name, isAuto, isCelcius, isAudibleAlarm, isSoftwareAuto)"
                     " values (:name, :isCelcius, :isAuto, :isAudibleAlarm, :isSoftwareAuto)"
                    );
    if (!ok)
    {
        qDebug() << qry.lastError().databaseText();
        return false;
    }

    qry.bindValue(":name", profileName);
    qry.bindValue(":isAuto", m_isAuto);
    qry.bindValue(":isCelcius", m_isCelcius);
    qry.bindValue(":isAudibleAlarm", m_isAudibleAlarm);
    qry.bindValue(":isSoftwareAuto", 0);        // TODO: Implement

    // TODO: If error, log actual database error

    if (!qry.exec())
    {
        qDebug() << qry.lastError().databaseText();
        return false;
    }

    //qry.clear();
    qry.exec("select p_id from Profile where name = 'blah';");
    //qry.bindValue(":name", profileName);
    if (!qry.exec())
    {
        qDebug() << qry.lastError().databaseText();
        return false;
    }
    qry.first();

    qDebug() << qry.size();

    p_id = qry.value(0).toInt();

    qDebug() << p_id;



    for (int i = 0; i < FC_MAX_CHANNELS; ++i)
    {
        qry.clear();
        qry.prepare("insert or replace into ChannelSetting"
                    " (p_id, channel, manualRpm, alarmTempF)"
                    " values (:p_id, :channel, :rpm, :alarmTempF)"
                    );
        qry.bindValue(":p_id", p_id);
        qry.bindValue(":channel", i);
        qry.bindValue(":rpm", m_channelSettings[i].speed);
        qry.bindValue(":alarmTempF", m_channelSettings[i].alarmTemp);
        qry.exec();
    }


    return true;

}


bool FanControllerProfile::load(const QString& profileName)
{
    m_isAuto = PhoebetriaDbMgr::readProfile(profileName, "isAuto", 0);
    m_isCelcius = PhoebetriaDbMgr::readProfile(profileName, "isCelcius", 0);
    m_isAudibleAlarm = PhoebetriaDbMgr::readProfile(profileName, "isAudibleAlarm", 0);

    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        m_channelSettings[i].alarmTemp = PhoebetriaDbMgr::readProfile(profileName, "AlarmTempF", i);
        m_channelSettings[i].speed = PhoebetriaDbMgr::readProfile(profileName, "FanRPM", i);
    }

    return true;
}

bool FanControllerProfile::erase(const QString& profileName)
{
    QSqlError err;
    err = PhoebetriaDbMgr::eraseProfile(profileName);
    return err.type() == QSqlError::NoError;
}


bool FanControllerProfile::importFromIni(void)
{
    // Get all ini filenames

    // Read each profile

    // Check if in database; if not, add the profile

    return true;
}
