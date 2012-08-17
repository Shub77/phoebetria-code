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

#include "profiles.h"

FanControllerProfile::FanControllerProfile()
{
}


// ------------------------------------------------------------------------
//  Access functions to channel settings
// ------------------------------------------------------------------------
int FanControllerProfile::maxRPM(int channel) const
{
    return m_channelSettings[channel].maxRPM();
}

int FanControllerProfile::alarmTemp(int channel) const
{
    return m_channelSettings[channel].alarmTemp();
}

int FanControllerProfile::manualRPM(int channel) const
{
    return m_channelSettings[channel].manualRPM();
}

int FanControllerProfile::lastTemp(int channel) const
{
    return m_channelSettings[channel].lastTemp();
}

int FanControllerProfile::maxTemp(int channel) const
{
    return m_channelSettings[channel].maxTemp();
}

int FanControllerProfile::minTemp(int channel) const
{
    return m_channelSettings[channel].minTemp();
}

int FanControllerProfile::lastRPM(int channel) const
{
    return m_channelSettings[channel].lastRPM();
}

int FanControllerProfile::minLoggedRPM(int channel) const
{
    return m_channelSettings[channel].minLoggedRPM();
}

int FanControllerProfile::maxLoggedRPM(int channel) const
{
    return m_channelSettings[channel].maxLoggedRPM();
}

// ------------------------------------------------------------------------
// Set channel settings
// ------------------------------------------------------------------------

void FanControllerProfile::setMaxRPM(int channel, int to)
{
    m_channelSettings[channel].setMaxRPM(to);
}

void FanControllerProfile::setAlarmTemp(int channel, int to)
{
    m_channelSettings[channel].setAlarmTemp(to);
}

void FanControllerProfile::setManualRPM(int channel, int to)
{
    m_channelSettings[channel].setManualRPM(to);
}

void FanControllerProfile::setLastTemp(int channel, int to)
{
    m_channelSettings[channel].setLastTemp(to);
}

void FanControllerProfile::setMinTemp(int channel, int to)
{
    m_channelSettings[channel].setMinTemp(to);
}

void FanControllerProfile::setMaxTemp(int channel, int to)
{
    m_channelSettings[channel].setMaxTemp(to);
}

void FanControllerProfile::setLastRPM(int channel, int to)
{
    m_channelSettings[channel].setLastRPM(to);
}

void FanControllerProfile::setMinLoggedRPM(int channel, int to)
{
    m_channelSettings[channel].setMinLoggedRPM(to);
}

void FanControllerProfile::setMaxLoggedRPM(int channel, int to)
{
    m_channelSettings[channel].setMaxLoggedRPM(to);
}

QString FanControllerProfile::temperatureString(int temperature,
                                                bool asCelcius,
                                                bool addScaleSymbol)
{
    QString r;
    int t = asCelcius ? ceil((temperature-32)*5.0/9) : temperature;
    r = QString::number(t);
    if (addScaleSymbol) r += (asCelcius ? " C" : " F");
    return r;
}
