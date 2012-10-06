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

#ifndef FANCHANNELDATA_H
#define FANCHANNELDATA_H

#include <QString>

#include "fanramp.h"

class FanChannelData
{
public:
    FanChannelData();

    //
    int maxRPM(void) const
    {
        return m_maxRPM;
    }
    int alarmTemp(void) const
    {
        return m_alarmTemp;
    }

    int manualRPM(void) const
    {
        return m_manualRPM;
    }

    int lastTemp(void) const
    {
        return m_lastTemp;
    }
    int maxTemp(void) const
    {
        return m_maxTemp;
    }
    int minTemp(void) const
    {
        return m_minTemp;
    }

    int lastRPM(void) const
    {
        return m_lastRPM;
    }
    int minLoggedRPM(void) const
    {
        return m_minLoggedRPM;
    }
    int maxLoggedRPM(void) const
    {
        return m_maxLoggedRPM;
    }

    //
    void setMaxRPM(int to)
    {
        m_maxRPM = to;
    }
    void setAlarmTemp(int to)
    {
        m_alarmTemp = to;
    }

    void setManualRPM(int to)
    {
        m_manualRPM = to;
    }

    void setLastTemp(int to)
    {
        m_lastTemp = to;
    }
    void setMinTemp(int to)
    {
        m_minTemp = to;
    }
    void setMaxTemp(int to)
    {
        m_maxTemp = to;
    }

    void setLastRPM(int to)
    {
        m_lastRPM = to;
    }
    void setMinLoggedRPM(int to)
    {
        m_minLoggedRPM = to;
    }
    void setMaxLoggedRPM(int to)
    {
        m_maxLoggedRPM = to;
    }

    //

    bool isSet_maxRpm(void) const
    {
        return m_maxRPM != m_RpmNotSetValue;
    }
    bool isSet_alarmTemp(void) const
    {
        return m_alarmTemp != m_TemperatureNotSetValue;
    }

    bool isSet_manualRPM(void) const
    {
        return m_manualRPM != m_manualRPMNotSetValue
               && m_manualRPM != m_manualRPMNotSetValue_Preferred;
    }

    bool isSet_lastTemp(void) const
    {
        return m_lastTemp != m_TemperatureNotSetValue;
    }
    bool isSet_MinTemp(void) const
    {
        return m_minTemp != m_minLoggedTempNotSetValue;
    }
    bool isSet_MaxTemp(void) const
    {
        return m_maxTemp != m_maxLoggedTempNotSetValue;
    }

    bool isSet_lastRPM(void) const
    {
        return m_lastRPM != m_RpmNotSetValue;
    }
    bool isSet_minLoggedRPM(void) const
    {
        return m_minLoggedRPM != m_RpmNotSetValue;
    }
    bool isSet_maxLoggedRPM(void) const
    {
        return m_maxLoggedRPM != m_RpmNotSetValue;
    }

    bool isRampInitialised(void) const
        { return m_ramp.isInitalised(); }

    bool initRamp(const FanControllerData& fcd, int channel)
        { return m_ramp.init(fcd, channel); }

    static bool isUndefinedValue_manualRPM(int value)
    {
        return !( value == m_manualRPMNotSetValue
                  || value == m_manualRPMNotSetValue_Preferred );
    }

private:
    int m_maxRPM;
    int m_alarmTemp;

    int m_lastTemp;
    int m_maxTemp;
    int m_minTemp;

    int m_lastRPM;
    int m_minLoggedRPM;
    int m_maxLoggedRPM;

    int m_manualRPM;

    FanSpeedRamp m_ramp;

    static const int m_RpmNotSetValue;
    static const int m_TemperatureNotSetValue;
    static const int m_maxLoggedTempNotSetValue;
    static const int m_minLoggedTempNotSetValue;
    static const int m_manualRPMNotSetValue;
    static const int m_manualRPMNotSetValue_Preferred;
};

#endif // FANCHANNELDATA_H
