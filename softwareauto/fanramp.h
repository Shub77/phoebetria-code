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

#ifndef PHOEBETRIA_FANSPEEDRAMP_H
#define PHOEBETRIA_FANSPEEDRAMP_H

#include <QList>
#include <QPoint>

#include <math.h>

// Fwd decls
class FanControllerData;

class FanSpeedRampData
{
public:

    friend class FanSpeedRamp;

    FanSpeedRampData();

    bool allowFanToTurnOff;
    int temperatureF_fanOn;
    int temperatureF_rampStart;
    int temperatureF_rampMid;
    int temperatureF_rampEnd;
    int temperatureF_fanToMax;
    int speed_fanOn;
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

class FanSpeedRamp
{
public:

    FanSpeedRamp();

    bool init(const FanControllerData& fcd, int channel);

    inline FanSpeedRampData* setup(void);

    inline const QList<QPoint>& ramp(void);

    inline static int snapToStepSize(int rpm, int stepSize);

    inline bool generateCurve(int maxRpm);

protected:

    bool initWithDefaultData(const FanControllerData& fcd, int channel);

    bool generateCurve(const FanSpeedRampData &fanCurveData,
                       int maxRpm,
                       int tempRangeMin,
                       int tempRangeMax,
                       QList<QPoint> *dest);



private:

    bool m_rampIsInitialised;

    FanSpeedRampData m_setup;
    QList<QPoint> m_ramp;
};


FanSpeedRampData* FanSpeedRamp::setup(void)
{
    return &m_setup;
}

const QList<QPoint> &FanSpeedRamp::ramp(void)
{
    return m_ramp;
}

int FanSpeedRamp::snapToStepSize(int rpm, int stepSize)
{
    return floor((double)rpm / stepSize) * stepSize;
}

bool FanSpeedRamp::generateCurve(int maxRpm)
{
    return generateCurve(m_setup, maxRpm, 0, 255, &m_ramp);
}

#endif // PHOEBETRIA_FANSPEEDRAMP_H
