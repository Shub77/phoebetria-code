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

#include "fancontrollerdata.h"
#include "fanchanneldata.h"
#include "phoebetriaapp.h"
#include <cmath>

#include <QDebug>

static const int FC_RTEMP_NOTSET = 0xffff;

FanControllerData::FanControllerData(QObject *parent)
    : QObject(parent),
      m_isCelcius(-1),
      m_isAuto(-1),
      m_isAudibleAlarm(-1),
      m_rampsReady(false),
      m_isSoftwareAuto(false),
      m_lastProfileId(-1)
{
    clearRampTemps();


}

void FanControllerData::connectSignals(void)
{
    connect(&ph_dispatcher(), SIGNAL(refresh_critical()),
            this, SLOT(onReset()));
}

void FanControllerData::syncWithProfile(const FanControllerProfile& fcp)
{
    m_isCelcius = fcp.isCelcius();
    m_isAuto = fcp.isAuto();
    m_isAudibleAlarm = fcp.isAudibleAlarm();
    m_isSoftwareAuto = fcp.isSoftwareAuto();

    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        const BasicChannelData& fcs = fcp.getChannelSettings(i);
        setAlarmTemp(i, fcs.alarmTemp);
        setManualRPM(i, fcs.speed);
        setRamp(i, fcp.ramp(i));
    }
}


// ------------------------------------------------------------------------
//  Access functions to channel settings
// ------------------------------------------------------------------------
int FanControllerData::maxRPM(int channel) const
{
    return m_channelSettings[channel].maxRPM();
}

int FanControllerData::alarmTemp(int channel) const
{
    return m_channelSettings[channel].alarmTemp();
}

int FanControllerData::manualRPM(int channel) const
{
    return m_channelSettings[channel].manualRPM();
}

int FanControllerData::lastTemp(int channel) const
{
    return m_channelSettings[channel].lastTemp();
}

int FanControllerData::maxTemp(int channel) const
{
    return m_channelSettings[channel].maxTemp();
}

int FanControllerData::minTemp(int channel) const
{
    return m_channelSettings[channel].minTemp();
}

int FanControllerData::lastRPM(int channel) const
{
    return m_channelSettings[channel].lastRPM();
}

int FanControllerData::minLoggedRPM(int channel) const
{
    return m_channelSettings[channel].minLoggedRPM();
}

int FanControllerData::maxLoggedRPM(int channel) const
{
    return m_channelSettings[channel].maxLoggedRPM();
}

// ------------------------------------------------------------------------
// Update channel settings
// ------------------------------------------------------------------------

void FanControllerData::updateMaxRPM(int channel, int to, bool emitSignal)
{
    FanChannelData& cd = m_channelSettings[channel];
    if (cd.maxRPM() != to || !cd.isSet_maxRpm())
    {
        cd.setMaxRPM(to);
        if (emitSignal) emit maxRPM_changed(channel, to);
    }
}

void FanControllerData::updateAlarmTemp(int channel, int to, bool emitSignal)
{
    FanChannelData& cd = m_channelSettings[channel];
    if (cd.alarmTemp() != to || !cd.isSet_alarmTemp())
    {
        cd.setAlarmTemp(to);
        if (emitSignal) emit currentAlarmTemp_changed(channel, to);
    }
}

void FanControllerData::updateManualRPM(int channel, int to, bool emitSignal)
{
    FanChannelData& cd = m_channelSettings[channel];

    if (to == 0xffff) return; // Ignore (0xffff is "not set")

    if ( cd.manualRPM() != to || !cd.isSet_manualRPM())
    {
        cd.setManualRPM(to);
        if (emitSignal) emit manualRPM_changed(channel, to);
    }
}

void FanControllerData::updateTempF(int channel, int to, bool emitSignal)
{
    /* !!!!!!!!! TODO: HOW? The range is 0x00 to 0xFF */

    /* Sometimes -'ve temperatures are sent from the device (that are
     * incorrect). The specs page for the recon show 0-100C as the probes'
     * range, so ignore these -'ve values.
     */
    if (to < 0) return;

    FanChannelData& cd = m_channelSettings[channel];
    if (cd.lastTemp() != to || !cd.isSet_lastTemp())
    {
        cd.setLastTemp(to);
        if (emitSignal) emit temperature_changed(channel, to);

        updateMinMax_temp(channel, to);

        if (!cd.isSet_lastTemp())
            qDebug() << "Last temp not set";
    }

    doSoftwareAuto(channel, to);
}

void FanControllerData::doSoftwareAuto(int channel, int tempF)
{
    if (!m_isSoftwareAuto)
        return;

    for (int i = 0; i < FC_MAX_CHANNELS; ++i)
    {
        if (isRampInitialised(i) && m_ramp[i].probeAffinity() == channel)
        {
            doSoftwareAutoChannel(i, tempF);
        }
    }
}

void FanControllerData::doSoftwareAutoChannel(int channel, int tempF)
{
    FanChannelData& cd = m_channelSettings[channel];

    //tempF = rand() % 256; // for testing

    int rDelta = abs(m_rTemps[channel] - tempF);
    // if temperature has changed by 2 or more degrees F
    // FIXME: TODO: Make user adjustable
    if (rDelta >= 2 || m_rTemps[channel] == FC_RTEMP_NOTSET
            || !cd.isSet_manualRPM())
    {

        int currRpm = m_ramp[channel].temperatureToRpm(m_rTemps[channel]);
        int newRpm = m_ramp[channel].temperatureToRpm(tempF);

        if (newRpm == -1) return;   // Do nothing if ramp not initialised

        if (newRpm != currRpm || m_rTemps[channel] == FC_RTEMP_NOTSET
                || !cd.isSet_manualRPM())
        {
            updateMinMax_rpm(channel, newRpm);
            m_rTemps[channel] = tempF; // Save tF for next time

            emit manualRPM_changed(channel, newRpm);

            ph_fanControllerIO().setChannelSettings(channel,
                                                    alarmTemp(channel),
                                                    newRpm);
#ifdef QT_DEBUG
            qDebug() << "S/W Auto -- Channel/Temp/RPM ="
                     << channel << tempF << newRpm;
#endif
        }
    }
}


void FanControllerData::updateRPM(int channel, int to, bool emitSignal)
{
    FanChannelData& cd = m_channelSettings[channel];
    if (cd.lastRPM() != to || !cd.isSet_lastRPM())
    {
        updateMinMax_rpm(channel, to);
        cd.setLastRPM(to);
        if (emitSignal) emit RPM_changed(channel, to);
    }
}


void FanControllerData::updateIsCelcius(bool isCelcius, bool emitSignal)
{
    if (m_isCelcius != (short)isCelcius || m_isCelcius == -1)
    {
        m_isCelcius = isCelcius;
        if (emitSignal) emit temperatureScale_changed(isCelcius);
    }
}

void FanControllerData::updateIsAuto(bool isAuto, bool emitSignal)
{
    if (m_isAuto != (short)isAuto || m_isAuto == -1)
    {
        m_isAuto = (short)isAuto;
        if (emitSignal) emit controlMode_changed(isAuto);
    }
}

void FanControllerData::updateIsAudibleAlarm(bool isAudible, bool emitSignal)
{
    if (m_isAudibleAlarm != (short)isAudible || m_isAudibleAlarm == -1)
    {
        m_isAudibleAlarm = isAudible;
        if (emitSignal) emit alarmIsAudible_changed(isAudible);
    }
}

void FanControllerData::clearMinMax(void)
{
    for (int i = 0; i < FC_MAX_CHANNELS; ++i)
    {
        FanChannelData& cd = m_channelSettings[i];
        cd.setMinTemp(FanChannelData::minLoggedTempNotSetValue);
        cd.setMaxTemp(FanChannelData::maxLoggedTempNotSetValue);
        cd.setMinLoggedRPM(FanChannelData::rpmNotSetValue);
        cd.setMaxLoggedRPM(FanChannelData::rpmNotSetValue);
    }
}

void FanControllerData::clearRampTemps(void)
{
    for (int i = 0; i < FC_MAX_CHANNELS; ++i)
        m_rTemps[i] = FC_RTEMP_NOTSET;
}

void FanControllerData::clearRampTemp(int channel)
{
    m_rTemps[channel] = FC_RTEMP_NOTSET;
}

void FanControllerData::updateMinMax_temp(int channel, int t)
{
    FanChannelData& cd = m_channelSettings[channel];

    if (cd.minTemp() > t || !cd.isSet_MinTemp())
    {
        cd.setMinTemp(t);
        emit minLoggedTemp_changed(channel, t);
    }
    if (cd.maxTemp() < t || !cd.isSet_MaxTemp())
    {
        cd.setMaxTemp(t);
        emit maxLoggedTemp_changed(channel, t);
    }
}

void FanControllerData::clearAllChannelRpmAndTemp(void)
{
    for (int i = 0; i < FC_MAX_CHANNELS; ++i)
        m_channelSettings[i].clearRpmAndTemp();
}

void FanControllerData::updateMinMax_rpm(int channel, int rpm)
{
    FanChannelData& cd = m_channelSettings[channel];
    if (cd.minLoggedRPM() > rpm || !cd.isSet_minLoggedRPM())
    {
        cd.setMinLoggedRPM(rpm);
        emit minLoggedRPM_changed(channel, rpm);
    }
    if ((cd.maxLoggedRPM() < rpm || !cd.isSet_maxLoggedRPM()) && rpm != 65500)
    {
        cd.setMaxLoggedRPM(rpm);
        emit maxLoggedRPM_changed(channel, rpm);
    }
}

// ------------------------------------------------------------------------
// Set channel settings
// ------------------------------------------------------------------------

void FanControllerData::setMaxRPM(int channel, int to)
{
    m_channelSettings[channel].setMaxRPM(to);
}

void FanControllerData::setAlarmTemp(int channel, int to)
{
    m_channelSettings[channel].setAlarmTemp(to);
}

void FanControllerData::setManualRPM(int channel, int to)
{
    m_channelSettings[channel].setManualRPM(to);
}

void FanControllerData::setLastTemp(int channel, int to)
{
    m_channelSettings[channel].setLastTemp(to);
}

void FanControllerData::setMinTemp(int channel, int to)
{
    m_channelSettings[channel].setMinTemp(to);
}

void FanControllerData::setMaxTemp(int channel, int to)
{
    m_channelSettings[channel].setMaxTemp(to);
}

void FanControllerData::setLastRPM(int channel, int to)
{
    m_channelSettings[channel].setLastRPM(to);
}

void FanControllerData::setMinLoggedRPM(int channel, int to)
{
    m_channelSettings[channel].setMinLoggedRPM(to);
}

void FanControllerData::setMaxLoggedRPM(int channel, int to)
{
    m_channelSettings[channel].setMaxLoggedRPM(to);
}

QString FanControllerData::temperatureString(int temperature,
        bool addScaleSymbol)
{
    QString r;
    int t = m_isCelcius ? toCelcius(temperature) : temperature;
    r = QString::number(t);
    if (addScaleSymbol) r += (m_isCelcius ? " C" : " F");
    return r;
}

/* Note:    Due to the conversion being somewhat specific for the fan controller
 *          device this should not be made a general (global) function; i.e.
 *          the rounding (or potential rounding) etc. make the function
 *          unsuitable for general purpose use.
 */
int FanControllerData::toCelcius(int tempInF)
{
    return round((tempInF-32)*5.0/9);
}

double FanControllerData::toCelciusReal(int tempInF)
{
    return (tempInF-32)*5.0/9;
}

/* Note:    Due to the conversion being somewhat specific for the fan controller
 *          device this should not be made a general (global) function; i.e.
 *          the rounding (or potential rounding) etc. make the function
 *          unsuitable for general purpose use.
 */
int FanControllerData::toFahrenheit(int tempInC, double errCorr)
{
    return round( (tempInC + errCorr) * 9/5.0 + 32);
}

bool FanControllerData::ramp_reqParamsForInitAreSet(void) const
{
    int cc = channelCount();
    bool r = true;

    for (int i = 0; i < cc; ++i)
    {
        if (!m_channelSettings[i].reqRampParamsAreSet())
        {
            r = false;
            break;
        }
    }
    return r;
}

void FanControllerData::initAllRamps(void)
{
    int cc = channelCount();

    for (int i = 0; i < cc; ++i)
    {
        if (!isRampInitialised(i))
            initRamp(i);
    }

    m_rampsReady = true;
}

void FanControllerData::onReset(void)
{
    clearMinMax();
    clearAllChannelRpmAndTemp();
    clearRampTemps();

    //qDebug() << "FanControllerData::onReset() called";
}

void FanControllerData::softReset(void)
{
    clearAllChannelRpmAndTemp();
    clearRampTemps();
}


