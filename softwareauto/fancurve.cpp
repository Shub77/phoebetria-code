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

#include "fancontrollerdata.h"
#include "math.h"

FanCurveData::FanCurveData()
{}

int FanCurveData::temperatureToRpm(int temperatureF, int maxRpm) const
{
    if (temperatureF < temperatureF_fanOn)
    {
        if (allowFanToTurnOff)
            return 0;
        else if (temperatureF <= temperatureF_rampStart)
            return minUsableRpm;
    }

    if (temperatureF < temperatureF_rampStart)
    {
        return minUsableRpm;
    }

    if (temperatureF <= temperatureF_rampMid)
    {
        if (temperatureF == temperatureF_rampStart)
            return speed_rampStart;
        if (temperatureF == temperatureF_rampMid)
            return speed_rampMid;

        QPoint a(temperatureF_rampStart, speed_rampStart);
        QPoint b(temperatureF_rampMid, speed_rampMid);

        return speedFromTemperatureLinear(temperatureF, a, b);
    }

    if (temperatureF < temperatureF_fanToMax)
    {
        QPoint a(temperatureF_rampMid, speed_rampMid);
        QPoint b(temperatureF_rampEnd, speed_rampEnd);

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
    double speed;

    int deltax = b.x() - a.x();
    int deltay = b.y() - a.y();
    double m = (double)deltay/deltax;
    double yi = a.y() - m*a.x();

    speed = m * temperatureF + yi;

    if (temperatureF > deltay / 2)
        speed  = ceil( (double)speed / speedStepSize );
    else
        speed  = floor( (double)speed / speedStepSize );

    speed *= speedStepSize;

    return speed;
}

FanCurve::FanCurve()
{
}

bool FanCurve::init(const FanControllerData& fcd, int channel)
{
    // TODO: load from database if exists

    return initWithDefaultData(fcd, channel);
}


bool FanCurve::initWithDefaultData(const FanControllerData& fcd, int channel)
{

    // Setup to be roughly equivalent to the Recon's built-in Auto
    m_setup.allowFanToTurnOff       = false;
    m_setup.temperatureF_fanOn      = floor(fcd.maxRPM(channel) * 0.50 / 100) * 100;
    m_setup.minUsableRpm            = floor(fcd.maxRPM(channel) * 0.50 / 100) * 100;
    m_setup.temperatureF_rampStart  = 0;
    m_setup.temperatureF_rampMid    = fcd.alarmTemp(channel)/2;
    m_setup.temperatureF_rampEnd    = fcd.alarmTemp(channel);
    m_setup.temperatureF_fanToMax   = fcd.alarmTemp(channel);
    m_setup.speed_rampStart         = floor(fcd.maxRPM(channel) * 0.50 / 100) * 100;
    m_setup.speed_rampEnd           = fcd.maxRPM(channel);
    m_setup.speed_rampMid           = (m_setup.minUsableRpm + m_setup.speed_rampEnd) / 2;
    m_setup.speed_rampMid = round(m_setup.speed_rampMid / 100.0) *100;



    m_setup.speedStepSize           = 100;
    m_setup.fixedRpm                = false;
    m_setup.probeAffinity           = channel;

    generateCurve(m_setup, fcd.maxRPM(channel), 0, 255, &m_ramp);

    return true;
}


bool FanCurve::generateCurve(const FanCurveData& fanCurveData,
                             int maxRpm,
                             int tempRangeMin,
                             int tempRangeMax,
                             QList<QPoint>* dest)
{
    int lastRpm = -1;

    for (int i = tempRangeMin; i < tempRangeMax; ++i)
    {
        int rpm = fanCurveData.temperatureToRpm(i, maxRpm);
        if (rpm < fanCurveData.minUsableRpm)
        {
            if (fanCurveData.allowFanToTurnOff)
                rpm = 0;
            else
                rpm = fanCurveData.minUsableRpm;
        }

        if (fanCurveData.allowFanToTurnOff
                && i == fanCurveData.temperatureF_fanOn - 1)
        {
            dest->append(QPoint(i, 0));
        }
        else if (i == fanCurveData.temperatureF_rampStart)
        {
            if (i != 0)
                dest->append(QPoint(i-1, lastRpm));
            dest->append(QPoint(i, rpm));
        }
        else if (rpm != lastRpm
                || i == tempRangeMax-1)
        {
            dest->append(QPoint(i, rpm));
        }

        lastRpm = rpm;
    }

    if (lastRpm != maxRpm)
        dest->append(QPoint(tempRangeMax, maxRpm));

    return true;
}
