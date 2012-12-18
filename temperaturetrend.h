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

#ifndef TEMPERATURETREND_H
#define TEMPERATURETREND_H

class TemperatureTrend
{
public:
    TemperatureTrend();
    ~TemperatureTrend();

    void addSampleTemperature(int tF);

    inline bool isStable(void) const;
    inline bool isIncreasing(void) const;
    inline bool isDecreasing(void) const;

protected:

    int updateStoredAverage(void);

private:

    static const int m_sampleSize;

    int* m_samples;
    int m_pos;
    int m_storedAverage;
    int m_prevTemperatureF;

};


bool TemperatureTrend::isStable(void) const
{
    return m_storedAverage == 0;
}

bool TemperatureTrend::isIncreasing(void) const
{
    return m_storedAverage == 1;
}

bool TemperatureTrend::isDecreasing(void) const
{
    return m_storedAverage == -1;
}


#endif // TEMPERATURETREND_H
