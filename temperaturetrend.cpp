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

#include "temperaturetrend.h"

#include <stdlib.h>
#include <cmath>

const int TemperatureTrend::m_sampleSize = 3;

TemperatureTrend::TemperatureTrend() :
    m_samples(NULL),
    m_pos(0),
    m_storedAverage(0),
    m_prevTemperatureF(0)
{
    m_samples = new int[m_sampleSize];
    for (int i = 0; i < m_sampleSize; ++i)
        m_samples[i] = 0;

    m_pos = 0;
}

TemperatureTrend::~TemperatureTrend()
{
    if (m_samples)
        delete [] m_samples;
}

void TemperatureTrend::addSampleTemperature(int tF)
{
    int direction;
    int delta = tF - m_prevTemperatureF;

    if (delta == 0)
        direction = 0;
    else if (delta < 0)
        direction = -1;
    else
        direction = 1;

    m_samples[m_pos++] = direction;
    m_pos %= m_sampleSize;

    m_prevTemperatureF = tF;

    updateStoredAverage();
}


int TemperatureTrend::updateStoredAverage(void)
{
    double total = 0;
    for (int i = 0; i < m_sampleSize; ++i)
        total += m_samples[i];

    return ceil(total / m_sampleSize);
}
