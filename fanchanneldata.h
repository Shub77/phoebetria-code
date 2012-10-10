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
    inline int maxRPM(void) const;
    inline int alarmTemp(void) const;
    inline int manualRPM(void) const;
    inline int lastTemp(void) const;
    inline int maxTemp(void) const;
    inline int minTemp(void) const;
    inline int lastRPM(void) const;
    inline int minLoggedRPM(void) const;
    inline int maxLoggedRPM(void) const;

    //
    inline void setMaxRPM(int to);
    inline void setAlarmTemp(int to);
    inline void setManualRPM(int to);
    inline void setLastTemp(int to);
    inline void setMinTemp(int to);
    inline void setMaxTemp(int to);
    inline void setLastRPM(int to);
    inline void setMinLoggedRPM(int to);
    inline void setMaxLoggedRPM(int to);

    //

    inline bool isSet_maxRpm(void) const;
    inline bool isSet_alarmTemp(void) const;
    inline bool isSet_manualRPM(void) const;
    inline bool isSet_lastTemp(void) const;
    inline bool isSet_MinTemp(void) const;
    inline bool isSet_MaxTemp(void) const;
    inline bool isSet_lastRPM(void) const;
    inline bool isSet_minLoggedRPM(void) const;
    inline bool isSet_maxLoggedRPM(void) const;
    inline static bool isUndefinedValue_manualRPM(int value);

    inline bool requiredParamsAreSet(void) const;

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

    static const int m_RpmNotSetValue;
    static const int m_TemperatureNotSetValue;
    static const int m_maxLoggedTempNotSetValue;
    static const int m_minLoggedTempNotSetValue;
    static const int m_manualRPMNotSetValue;
    static const int m_manualRPMNotSetValue_Preferred;
};


int FanChannelData::maxRPM(void) const
{
    return m_maxRPM;
}

int FanChannelData::alarmTemp(void) const
{
    return m_alarmTemp;
}

int FanChannelData::manualRPM(void) const
{
    return m_manualRPM;
}

int FanChannelData::lastTemp(void) const
{
    return m_lastTemp;
}

int FanChannelData::maxTemp(void) const
{
    return m_maxTemp;
}

int FanChannelData::minTemp(void) const
{
    return m_minTemp;
}

int FanChannelData::lastRPM(void) const
{
    return m_lastRPM;
}

int FanChannelData::minLoggedRPM(void) const
{
    return m_minLoggedRPM;
}

int FanChannelData::maxLoggedRPM(void) const
{
    return m_maxLoggedRPM;
}

//
void FanChannelData::setMaxRPM(int to)
{
    m_maxRPM = to;
}

void FanChannelData::setAlarmTemp(int to)
{
    m_alarmTemp = to;
}

void FanChannelData::setManualRPM(int to)
{
    m_manualRPM = to;
}

void FanChannelData::setLastTemp(int to)
{
    m_lastTemp = to;
}

void FanChannelData::setMinTemp(int to)
{
    m_minTemp = to;
}

void FanChannelData::setMaxTemp(int to)
{
    m_maxTemp = to;
}

void FanChannelData::setLastRPM(int to)
{
    m_lastRPM = to;
}

void FanChannelData::setMinLoggedRPM(int to)
{
    m_minLoggedRPM = to;
}

void FanChannelData::setMaxLoggedRPM(int to)
{
    m_maxLoggedRPM = to;
}

//

bool FanChannelData::isSet_maxRpm(void) const
{
    return m_maxRPM != m_RpmNotSetValue;
}

bool FanChannelData::isSet_alarmTemp(void) const
{
    return m_alarmTemp != m_TemperatureNotSetValue;
}

bool FanChannelData::isSet_manualRPM(void) const
{
    return m_manualRPM != m_manualRPMNotSetValue
           && m_manualRPM != m_manualRPMNotSetValue_Preferred;
}

bool FanChannelData::isSet_lastTemp(void) const
{
    return m_lastTemp != m_TemperatureNotSetValue;
}

bool FanChannelData::isSet_MinTemp(void) const
{
    return m_minTemp != m_minLoggedTempNotSetValue;
}

bool FanChannelData::isSet_MaxTemp(void) const
{
    return m_maxTemp != m_maxLoggedTempNotSetValue;
}

bool FanChannelData::isSet_lastRPM(void) const
{
    return m_lastRPM != m_RpmNotSetValue;
}

bool FanChannelData::isSet_minLoggedRPM(void) const
{
    return m_minLoggedRPM != m_RpmNotSetValue;
}

bool FanChannelData::isSet_maxLoggedRPM(void) const
{
    return m_maxLoggedRPM != m_RpmNotSetValue;
}

bool FanChannelData::isUndefinedValue_manualRPM(int value)
{
    return !( value == m_manualRPMNotSetValue
              || value == m_manualRPMNotSetValue_Preferred );
}

bool FanChannelData::requiredParamsAreSet(void) const
{
    return isSet_alarmTemp() && isSet_maxRpm();
}

#endif // FANCHANNELDATA_H
