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

#include "fancurve.h"

#include <QDebug>

#include "math.h"


int FanCurveData::temperatureToRpm(int temperatureF, int maxRpm) const
{
    if (temperatureF < temperatureF_fanOn)
    {
        if (allowFanToTurnOff)
            return 0;
        else if (temperatureF <= temperatureF_rampStart)
            return minUsableRpm;
    }

    if (temperatureF <= temperatureF_rampMid)
    {
        QPoint a(temperatureF_rampStart, temperatureF_rampMid);
        QPoint b(speed_rampStart, speed_rampMid);
        return speedFromTemperatureLinear(temperatureF, a, b);
    }

    if (temperatureF <= temperatureF_rampEnd
            && temperatureF < temperatureF_fanToMax)
    {

        QPoint a(temperatureF_rampMid, temperatureF_rampEnd);
        QPoint b(speed_rampMid, speed_rampEnd);

        if (temperatureF > temperatureF_rampEnd)
        {
            return speedFromTemperatureLinear(temperatureF_rampEnd, a, b);
        }
        return speedFromTemperatureLinear(temperatureF, a, b);
    }

    return maxRpm;
}

int FanCurveData::speedFromTemperatureLinear(int temperatureF,
                                         const QPoint& a,
                                         const QPoint& b) const
{
    int temperatureTemp;

    int deltax = b.x() - a.x();
    int deltay = b.y() - a.y();

    temperatureTemp =  floor( (double)deltax/deltay * temperatureF );

    int speed;

    speed +=  a.y();
    speed +=  floor( (double)temperatureTemp / speedStepSize );
    speed *= speedStepSize;

    return speed;
}

FanCurve::FanCurve()
{
}

