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


/* Set from the current controller settings
 */
void FanControllerProfile::setFromCurrentData(const FanControllerData& data)
{
    m_isCelcius = data.isCelcius();
    m_isAuto = data.isAuto();
    m_isAudibleAlarm = data.isAudibleAlarm();

    for (int i = 0; i < FC_MAX_CHANNELS; i++) {
        m_channelSettings[i].alarmTemp = data.alarmTemp(i);
        m_channelSettings[i].speed =  m_isAuto ? -1 :
                 (data.manualRPM(i) ==  -1 ? data.lastRPM(i) : data.manualRPM(i));
    }
}


bool FanControllerProfile::save(const QString& filenameAndPath)
{
    QSettings settings (filenameAndPath, QSettings::IniFormat);

    settings.setValue("common/auto", m_isAuto ? 1 : 0);
    settings.setValue("common/celcius", m_isCelcius ? 1 : 0);
    settings.setValue("common/alarm", m_isAudibleAlarm ? 1 : 0);
    for (int i = 0; i < FC_MAX_CHANNELS; i++) {
        QString group = "fan_" + QString::number(i);
        settings.beginGroup(group);
        settings.setValue("alarm_temperature_F",
                          QString::number(m_channelSettings[i].alarmTemp));
        settings.setValue("rpm", m_channelSettings[i].speed);
        settings.endGroup();
    }
    settings.sync();
    qDebug() << settings.status();
    return settings.status() == QSettings::NoError;
}


bool FanControllerProfile::load(const QString& filenameAndPath)
{
    bool r = true;

    // TODO: Check if the profile even exists before trying to use
    //       QSettings

    QSettings settings (filenameAndPath, QSettings::IniFormat);

    m_isAuto = settings.value("common/auto", m_isAuto).toBool();
    m_isCelcius = settings.value("common/celcius", m_isCelcius).toBool();
    m_isAudibleAlarm = settings.value("common/alarm", m_isAudibleAlarm).toBool();

    for (int i = 0; i < FC_MAX_CHANNELS; i++) {
        QString group = "fan_" + QString::number(i);
        settings.beginGroup(group);

        int value;
        bool ok;

        value = settings.value("alarm_temperature_F",
                               m_channelSettings[i].alarmTemp).toInt(&ok);
        if (ok) {
            m_channelSettings[i].alarmTemp = value;
        }
        else r = false;

        value = settings.value("speed",
                               m_channelSettings[i].speed).toInt(&ok);
        if (ok) {
            m_channelSettings[i].speed = value;
        }
        else r = false;

        settings.endGroup();
    }

    return r && (settings.status() == QSettings::NoError);
}
