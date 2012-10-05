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

#include <QList>
#include <QPoint>

#include <math.h>

// Fwd decls
class FanControllerData;

class FanCurveData
{
public:

    friend class FanCurve;

    FanCurveData();

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
    bool fixedRpm;
    int probeAffinity;

protected:


    int temperatureToRpm(int temperatureF, int maxRpm) const;

    int speedFromTemperatureLinear(int temperatureF,
                                   const QPoint& a,
                                   const QPoint& b) const;
};

class FanCurve
{
public:

    FanCurve();

    bool init(const FanControllerData& fcd, int channel);

    inline FanCurveData* setup(void);

    inline QList<QPoint> ramp(void);

    inline static int snapToStepSize(int rpm, int stepSize);

protected:

    bool initWithDefaultData(const FanControllerData& fcd, int channel);

    bool generateCurve(const FanCurveData &fanCurveData,
                       int maxRpm,
                       int tempRangeMin,
                       int tempRangeMax,
                       QList<QPoint> *dest);



private:
    FanCurveData m_setup;
    QList<QPoint> m_ramp;
};


FanCurveData* FanCurve::setup(void)
{
    return &m_setup;
}

QList<QPoint> FanCurve::ramp(void)
{
    return m_ramp;
}

int FanCurve::snapToStepSize(int rpm, int stepSize)
{
    return floor((double)rpm / stepSize) * stepSize;
}

#endif // PHOEBETRIA_FANCURVE_H
