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

#include <cmath>
#include "fanchanneldata.h"

FanChannelData::FanChannelData()
{
    m_maxTemp = 0;
    m_maxLoggedRPM = 0;
    m_lastRPM = -1;
    m_minLoggedRPM = -1;
    m_lastTemp = -1;
    m_minTemp = 9999;

    m_alarmTemp = -1;
    m_maxRPM = 1400;

    m_manualRPM = -1;
}

