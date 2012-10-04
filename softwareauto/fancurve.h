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

#ifndef PHOEBETRIA_FANCURVE_H
#define PHOEBETRIA_FANCURVE_H

#include <QPoint>

class FanCurveData
{
public:

    FanCurveData();

    int temperatureToRpm(int temperatureF, int maxRpm) const;

    bool allowFanToTurnOff;
    int temperatureF_fanOn;
    int temperatureF_rampStart;
    int temperatureF_rampMid;
    int temperatureF_rampEnd;
    int temperatureF_fanToMax;
    int speed_rampStart;
    int speed_rampMid;
    int speed_rampEnd;

    int minUsableRpm;

    int speedStepSize;

protected:

    int speedFromTemperatureLinear(int temperatureF,
                                   const QPoint& a,
                                   const QPoint& b) const;
};

class FanCurve
{
public:

    FanCurve();

};


#endif // PHOEBETRIA_FANCURVE_H
