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

#ifndef FANCONTROLLERDATA_H
#define FANCONTROLLERDATA_H

#include <QString>
#include "fanchanneldata.h"

#define FC_MAX_CHANNELS 5

class FanControllerData
{
public:
    FanControllerData();

    const QString& name(void) const;

    void init(void);

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

    //
    bool updateMaxRPM(int channel, int to);
    bool updateAlarmTemp(int channel, int to);
    bool updateManualRPM(int channel, int to);
    bool updateTempF(int channel, int to);
    bool updateRPM(int channel, int to);

    // Set channel settings
    // TODO: make these protected or even private
    void setMaxRPM(int channel, int to);
    void setAlarmTemp(int channel, int to);

    void setManualRPM(int channel, int to);

    void setLastTemp(int channel, int to);
    void setMinTemp(int channel, int to);
    void setMaxTemp(int channel, int to);

    void setLastRPM(int channel, int to);
    void setMinLoggedRPM(int channel, int to);
    void setMaxLoggedRPM(int channel, int to);
    // END TODO: make these protected or even private


    static QString temperatureString(int temperature,
                                     bool asCelcius,
                                     bool addScaleSymbol);

    static int toCelcius(int tempInF);
    static int toFahrenheit(int tempInC);

private:

    // Common data
    bool m_isCelcius;
    bool m_isAuto;
    bool m_isAudibleAlarm;

    FanChannelData m_channelSettings[FC_MAX_CHANNELS];

};



#endif // FANCONTROLLERDATA_H
