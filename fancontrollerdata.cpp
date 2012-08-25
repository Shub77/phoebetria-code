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

#include "fancontrollerdata.h"
#include <cmath>


FanControllerData::FanControllerData()
{
    init();
}

void FanControllerData::init(void)
{
    m_isCelcius = false;
    m_isAuto = true;
    m_isAudibleAlarm = true;
}

// ------------------------------------------------------------------------
//  Access functions to channel settings
// ------------------------------------------------------------------------
int FanControllerData::maxRPM(int channel) const
{
    return m_channelSettings[channel].maxRPM();
}

int FanControllerData::alarmTemp(int channel) const
{
    return m_channelSettings[channel].alarmTemp();
}

int FanControllerData::manualRPM(int channel) const
{
    return m_channelSettings[channel].manualRPM();
}

int FanControllerData::lastTemp(int channel) const
{
    return m_channelSettings[channel].lastTemp();
}

int FanControllerData::maxTemp(int channel) const
{
    return m_channelSettings[channel].maxTemp();
}

int FanControllerData::minTemp(int channel) const
{
    return m_channelSettings[channel].minTemp();
}

int FanControllerData::lastRPM(int channel) const
{
    return m_channelSettings[channel].lastRPM();
}

int FanControllerData::minLoggedRPM(int channel) const
{
    return m_channelSettings[channel].minLoggedRPM();
}

int FanControllerData::maxLoggedRPM(int channel) const
{
    return m_channelSettings[channel].maxLoggedRPM();
}

// ------------------------------------------------------------------------
// Update channel settings
// ------------------------------------------------------------------------

bool FanControllerData::updateMaxRPM(int channel, int to)
{
    bool r = false;
    FanChannelData& cd = m_channelSettings[channel];
    if (cd.maxRPM() != to || !cd.isSet_maxRpm()) {
        cd.setMaxRPM(to);
        r = true;
    }
    return r;
}

bool FanControllerData::updateAlarmTemp(int channel, int to)
{
    bool r = false;
    FanChannelData& cd = m_channelSettings[channel];
    if (cd.alarmTemp() != to || !cd.isSet_alarmTemp()) {
        cd.setAlarmTemp(to);
        r = true;
    }
    return r;
}

bool FanControllerData::updateManualRPM(int channel, int to)
{
    bool r = false;
    FanChannelData& cd = m_channelSettings[channel];
    if (cd.manualRPM() != to || !cd.isSet_manualRPM()) {
        cd.setManualRPM(to);
        r = true;
    }
    return r;
}

bool FanControllerData::updateTempF(int channel, int to)
{
    bool r = false;
    FanChannelData& cd = m_channelSettings[channel];
    if (cd.lastTemp() != to || !cd.isSet_lastTemp()) {
        if (cd.minTemp() > to || !cd.isSet_MinTemp()) {
            cd.setMinTemp(to);
        }
        if (cd.maxTemp() < to || !cd.isSet_MaxTemp()) {
            cd.setMaxTemp(to);
        }
        cd.setLastTemp(to);
        r = true;
    }
    return r;
}

bool FanControllerData::updateRPM(int channel, int to)
{
    bool r = false;
    FanChannelData& cd = m_channelSettings[channel];
    if (cd.lastRPM() != to || !cd.isSet_lastRPM()) {
        if (cd.minLoggedRPM() > to || !cd.isSet_minLoggedRPM()) {
            cd.setMinLoggedRPM(to);
        }
        if (cd.maxLoggedRPM() < to || !cd.isSet_maxLoggedRPM()) {
            cd.setMaxLoggedRPM(to);
        }
        cd.setLastRPM(to);
        r = true;
    }
    return r;
}


// ------------------------------------------------------------------------
// Set channel settings
// ------------------------------------------------------------------------

void FanControllerData::setMaxRPM(int channel, int to)
{
    m_channelSettings[channel].setMaxRPM(to);
}

void FanControllerData::setAlarmTemp(int channel, int to)
{
    m_channelSettings[channel].setAlarmTemp(to);
}

void FanControllerData::setManualRPM(int channel, int to)
{
    m_channelSettings[channel].setManualRPM(to);
}

void FanControllerData::setLastTemp(int channel, int to)
{
    m_channelSettings[channel].setLastTemp(to);
}

void FanControllerData::setMinTemp(int channel, int to)
{
    m_channelSettings[channel].setMinTemp(to);
}

void FanControllerData::setMaxTemp(int channel, int to)
{
    m_channelSettings[channel].setMaxTemp(to);
}

void FanControllerData::setLastRPM(int channel, int to)
{
    m_channelSettings[channel].setLastRPM(to);
}

void FanControllerData::setMinLoggedRPM(int channel, int to)
{
    m_channelSettings[channel].setMinLoggedRPM(to);
}

void FanControllerData::setMaxLoggedRPM(int channel, int to)
{
    m_channelSettings[channel].setMaxLoggedRPM(to);
}

QString FanControllerData::temperatureString(int temperature,
                                                bool asCelcius,
                                                bool addScaleSymbol)
{
    QString r;
    int t = asCelcius ? ceil((temperature-32)*5.0/9) : temperature;
    r = QString::number(t);
    if (addScaleSymbol) r += (asCelcius ? " C" : " F");
    return r;
}

/* Note:    Due to the conversion being somewhat specific for the fan controller
 *          device this should not be made a general (global) function; i.e.
 *          the rounding (or potential rounding) etc. make the function
 *          unsuitable for general purpose use.
 */
int FanControllerData::toCelcius(int tempInF)
{
    return ceil((tempInF-32)*5.0/9);
}

/* Note:    Due to the conversion being somewhat specific for the fan controller
 *          device this should not be made a general (global) function; i.e.
 *          the rounding (or potential rounding) etc. make the function
 *          unsuitable for general purpose use.
 */
int FanControllerData::toFahrenheit(int tempInC)
{
    return tempInC * 9/5.0 + 32;
}
