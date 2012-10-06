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

class FanSpeedRampParameters
{
public:

    friend class FanSpeedRamp;

    FanSpeedRampParameters();

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
    int maxUsableRpm;
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

    inline bool isInitialised(void) const;

    inline bool isModified(void) const;

    bool init(const FanControllerData& fcd, int channel, int profileId);

    inline const QList<QPoint>& ramp(void);

    inline int snapToStepSize(int rpm) const;

    inline static int snapToStepSize(int rpm, int stepSize);

    inline bool generateCurve(int maxRpm);

    inline const FanSpeedRampParameters& rampParameters(void) const;

    // ----------- Set functions for setup data

    inline void    setAllowFanToTurnOff(bool allow);
    inline void    setTemperatureFanOn(int t);
    inline void    setTemperatureRampStart(int t);
    inline void    setTemperatureRampMid(int t);
    inline void    setTemperatureRampEnd(int t);
    inline void    setTemperatureFanToMax(int t);
    inline void    setSpeedFanOn(int rpm);
    inline void    setSpeedRampStart(int rpm);
    inline void    setSpeedRampMid(int rpm);
    inline void    setSpeedRampEnd(int rpm);

    inline void    setMinUsableRpm(int rpm);
    inline void    setMaxUsableRpm(int rpm);

    inline void    setSpeedStepSize(int step);

    inline void    setIsFixedRpm (bool isFixed);

    inline void    setProbeAffinity(int probeNumber);

    // ----------- END Set functions for setup data

protected:

    bool initWithDefaultData(const FanControllerData& fcd, int channel);

    bool generateCurve(const FanSpeedRampParameters &fanCurveData,
                       int maxRpm,
                       int tempRangeMin,
                       int tempRangeMax,
                       QList<QPoint> *dest);

private:

    bool m_rampIsInitialised;
    bool m_isModified;
    int m_profileId;        // profile that was used to init
    int m_channel;
    FanSpeedRampParameters m_rampParameters;
    QList<QPoint> m_ramp;
};

bool FanSpeedRamp::isInitialised(void) const
{
    return m_rampIsInitialised;
}

bool FanSpeedRamp::isModified(void) const
{
    return m_isModified;
}

const QList<QPoint> &FanSpeedRamp::ramp(void)
{
    return m_ramp;
}

int FanSpeedRamp::snapToStepSize(int rpm) const
{
    return snapToStepSize(rpm, m_rampParameters.speedStepSize);
}

int FanSpeedRamp::snapToStepSize(int rpm, int stepSize)
{
    return floor((double)rpm / stepSize) * stepSize;
}

bool FanSpeedRamp::generateCurve(int maxRpm)
{
    return generateCurve(m_rampParameters, maxRpm, 0, 255, &m_ramp);
}

const FanSpeedRampParameters& FanSpeedRamp::rampParameters(void) const
{
    return m_rampParameters;
}

/*------------------------------------------------------------------------
  Set functions for setup data
  -----------------------------------------------------------------------*/
void FanSpeedRamp::setAllowFanToTurnOff(bool allow)
{
    m_isModified = true;
    m_rampParameters.allowFanToTurnOff = allow;
}

void FanSpeedRamp::setTemperatureFanOn(int t)
{
    m_isModified = true;
    m_rampParameters.temperatureF_fanOn = t;
}

void FanSpeedRamp::setTemperatureRampStart(int t)
{
    m_isModified = true;
    m_rampParameters.temperatureF_rampStart = t;
}

void FanSpeedRamp::setTemperatureRampMid(int t)
{
    m_isModified = true;
    m_rampParameters.temperatureF_rampMid = t;
}

void FanSpeedRamp::setTemperatureRampEnd(int t)
{
    m_isModified = true;
    m_rampParameters.temperatureF_rampEnd = t;
}

void FanSpeedRamp::setTemperatureFanToMax(int t)
{
    m_isModified = true;
    m_rampParameters.temperatureF_fanToMax = t;
}

void    FanSpeedRamp::setSpeedFanOn(int rpm)
{
    m_isModified = true;
    m_rampParameters.speed_fanOn = rpm;
}

void FanSpeedRamp::setSpeedRampStart(int rpm)
{
    m_isModified = true;
    m_rampParameters.speed_rampStart = rpm;
}

void FanSpeedRamp::setSpeedRampMid(int rpm)
{
    m_isModified = true;
    m_rampParameters.speed_rampMid = rpm;
}

void FanSpeedRamp::setSpeedRampEnd(int rpm)
{
    m_isModified = true;
    m_rampParameters.speed_rampEnd = rpm;
}

void FanSpeedRamp::setMinUsableRpm(int rpm)
{
    m_isModified = true;
    m_rampParameters.minUsableRpm = rpm;
}

void FanSpeedRamp::setMaxUsableRpm(int rpm)
{
    m_isModified = true;
    m_rampParameters.maxUsableRpm = rpm;
}

void FanSpeedRamp::setSpeedStepSize(int step)
{
    m_isModified = true;
    m_rampParameters.speedStepSize = step;
}

void FanSpeedRamp::setIsFixedRpm (bool isFixed)
{
    m_isModified = true;
    m_rampParameters.fixedRpm = isFixed;
}

void FanSpeedRamp::setProbeAffinity(int probeNumber)
{
    m_isModified = true;
    m_rampParameters.probeAffinity = probeNumber;
}

/*------------------------------------------------------------------------
  END Set functions for setup data
  -----------------------------------------------------------------------*/

#endif // PHOEBETRIA_FANSPEEDRAMP_H
