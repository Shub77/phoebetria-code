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

class FanChannelData
{
public:
    FanChannelData();

    //
    int maxRPM(void) const { return m_maxRPM; }
    int alarmTemp(void) const { return m_alarmTemp; }

    int manualRPM(void) const { return m_manualRPM; }

    int lastTemp(void) const { return m_lastTemp; }
    int maxTemp(void) const { return m_maxTemp; }
    int minTemp(void) const { return m_minTemp; }

    int lastRPM(void) const { return m_lastRPM; }
    int minLoggedRPM(void) const { return m_minLoggedRPM; }
    int maxLoggedRPM(void) const { return m_maxLoggedRPM; }

    //
    void setMaxRPM(int to) { m_maxRPM = to; }
    void setAlarmTemp(int to) { m_alarmTemp = to; }

    void setManualRPM(int to) { m_manualRPM = to; }

    void setLastTemp(int to) { m_lastTemp = to; }
    void setMinTemp(int to) { m_minTemp = to; }
    void setMaxTemp(int to) { m_maxTemp = to; }

    void setLastRPM(int to) { m_lastRPM = to; }
    void setMinLoggedRPM(int to) { m_minLoggedRPM = to; }
    void setMaxLoggedRPM(int to) { m_maxLoggedRPM = to; }

    //
    static QString temperatureString(int temperature,
                                     bool asCelcius,
                                     bool addScaleSymbol);

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
};

#endif // FANCHANNELDATA_H
