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

#ifndef PROFILES_H
#define PROFILES_H

#include <QString>
#include "fanchanneldata.h"

#define FC_MAX_CHANNELS 5

class FanControllerProfile
{
public:
    FanControllerProfile();

    const QString& name(void) const;

    bool init(void);

    bool load();
    bool save(const char* filename);

    // Access functions for common settings
    bool isCelcius(void) const { return m_isCelcius; }
    bool isAuto(void) const {return m_isAuto; }
    bool isAudibleAlarm(void) const { return m_isAudibleAlarm; }

    // Set common settings
    void setIsCelcius(bool isC)
        { m_isCelcius = isC; }
    void setIsAuto(bool isAuto)
        { m_isAuto = isAuto; }
    void setIsAudibleAlarm(bool isAudible)
        { m_isAudibleAlarm = isAudible; }

    // Access functions to channel settings
    int maxRPM(int channel) const;
    int alarmTemp(int channel) const;

    int manualRPM(int channel) const;

    int lastTemp(int channel) const;
    int maxTemp(int channel) const;
    int minTemp(int channel) const;

    int lastRPM(int channel) const;
    int minLoggedRPM(int channel) const;
    int maxLoggedRPM(int channel) const;

    // Set channel settings
    void setMaxRPM(int channel, int to);
    void setAlarmTemp(int channel, int to);

    void setManualRPM(int channel, int to);

    void setLastTemp(int channel, int to);
    void setMinTemp(int channel, int to);
    void setMaxTemp(int channel, int to);

    void setLastRPM(int channel, int to);
    void setMinLoggedRPM(int channel, int to);
    void setMaxLoggedRPM(int channel, int to);

    static QString temperatureString(int temperature,
                                     bool asCelcius,
                                     bool addScaleSymbol);
private:

    // Common data
    bool m_isCelcius;
    bool m_isAuto;
    bool m_isAudibleAlarm;

    FanChannelData m_channelSettings[FC_MAX_CHANNELS];

};

#endif // PROFILES_H
