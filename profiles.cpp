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
                                    + QDir::separator();
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
        if (!m_isAuto) {
            m_channelSettings[i].speed = data.manualRPM(i);
        }
    }
}
