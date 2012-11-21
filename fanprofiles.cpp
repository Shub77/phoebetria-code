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

FanControllerProfile::FanControllerProfile(const QString& name,
                                           const QString& desc)
{
    initCommon();
    m_name = name;
    m_description = desc;
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
    m_isSoftwareAuto = false;
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
    m_isSoftwareAuto = data.isSoftwareAuto();

    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        m_channelSettings[i].alarmTemp = data.alarmTemp(i);

        int speedToSave;

        speedToSave = data.isManualRpmSet(i) ? data.manualRPM(i)
                                             : data.lastRPM(i);

        m_channelSettings[i].speed = speedToSave;

        m_ramp[i] = data.ramp(i);
    }
}


bool FanControllerProfile::save(const QString& profileName)
{
    MainDb mdb;

    return mdb.writeProfile(profileName, *this);
}

// Redundant load and read functions, load function is inaccuratly named for it's use, Chris will resolve...

bool FanControllerProfile::load(const QString& profileName)
{
    MainDb mdb;

    return mdb.readProfile(profileName, *this);
}

bool FanControllerProfile::read(const QString& profileName)
{
    MainDb mdb;

    return mdb.readProfile(profileName, *this);
}

bool FanControllerProfile::erase(const QString& profileName)
{
    MainDb mdb;

    return mdb.deleteProfile(profileName);
}

QString FanControllerProfile::profileDescription(const QString& profileName)
{
    MainDb mdb;

    return mdb.profileDescription(profileName);
}

// returns the number of files imported
// pre dir.exists() == true
int FanControllerProfile::importFromIni(QDir& dir)
{
    QFileInfoList files = dir.entryInfoList(QDir::Files);

    MainDb mdb;
    int count = files.count();
    int filesImported = 0;

    for (int i = 0; i < count; ++i)
    {
        FanControllerProfile tmp;
        if (loadFromIni(files.at(i).filePath(), tmp))
        {
            QString profileName(files.at(i).fileName());
            if (profileName.endsWith(".ini"))
                profileName.chop(4);

            if (profileName.isEmpty())  // Paranoia probabaly
                continue;

            if (mdb.writeProfile(profileName, tmp))
                filesImported++;
        }
    }

    return filesImported;
}


bool FanControllerProfile::loadFromIni(const QString& filenameAndPath,
                                       FanControllerProfile& dest)
{
    bool r = true;

    QFile file;
    file.setFileName(filenameAndPath);
    if (!file.exists())
    {
        return false;
    }

    QSettings settings (filenameAndPath, QSettings::IniFormat);

    dest.m_isAuto = settings.value("common/auto", true).toBool();
    dest.m_isCelcius = settings.value("common/celcius", true).toBool();
    dest.m_isAudibleAlarm = settings.value("common/alarm", true).toBool();

    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        QString group = "fan_" + QString::number(i);
        settings.beginGroup(group);

        int value;
        bool ok;

        value = settings.value("alarm_temperature_F",
                               dest.m_channelSettings[i].alarmTemp).toInt(&ok);
        if (ok)
            dest.m_channelSettings[i].alarmTemp = value;
        else
            r = false;

        value = settings.value("rpm",
                               dest.m_channelSettings[i].speed).toInt(&ok);
        if (ok)
            dest.m_channelSettings[i].speed = value;
        else
            r = false;

        settings.endGroup();
    }

    return r && (settings.status() == QSettings::NoError);
}
