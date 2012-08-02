#ifndef FANDATA_H
#define FANDATA_H

class FanData
{
public:
    FanData();

    int RPM(void) const;
    int calibratedRPM(void) const;
    int maxRPM(void) const;
    int voltage(void) const;
    double RPMcalibrationFactor(void) const;

private:
    int m_currentRPM;
    int m_maxRPM;
    int m_voltage;
    double m_RPMcalibrationFactor;
};

#endif // FANDATA_H
