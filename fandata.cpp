#include "fandata.h"

FanData::FanData()
{
    m_RPMcalibrationFactor = 1.0;   // Default is to simply report what the controller says
}

int FanData::temperature(void) const
{
    return m_temperature;
}

int FanData::RPM(void) const
{
    return m_currentRPM;
}

int FanData::calibratedRPM(void) const
{
    return (int)(m_currentRPM * m_RPMcalibrationFactor);
}

int FanData::maxRPM(void) const
{
    return m_maxRPM;
}

int FanData::voltage(void) const
{
    return m_voltage;
}

double FanData::RPMcalibrationFactor(void) const
{
    return m_RPMcalibrationFactor;
}
