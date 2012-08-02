#ifndef FANDATA_H
#define FANDATA_H

#include "temperaturemonitor.h"

class FanData
{
public:
    FanData();

    int RPM(void) const;
    int calibratedRPM(void) const;
    int maxRPM(void) const;
    int voltage(void) const;
    double RPMcalibrationFactor(void) const;
    bool connectToTemperatureSource(QString probeName);

private:
    int m_currentRPM;
    int m_maxRPM;
    int m_voltage;
    double m_RPMcalibrationFactor;
    TemperatureSource* m_tempSrc; // probe/source used to control this fan
};

#endif // FANDATA_H
