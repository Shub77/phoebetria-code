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
#include <cmath>


FanControllerData::FanControllerData(QObject *parent)
    : QObject(parent),
      m_isCelcius(-1),
      m_isAuto(-1),
      m_isAudibleAlarm(-1),
      m_rampsReady(false),
      m_isSoftwareAuto(false),
      m_lastProfileId(-1)
{
}

void FanControllerData::syncWithProfile(const FanControllerProfile& fcp)
{
    m_isCelcius = fcp.isCelcius();
    m_isAuto = fcp.isAuto();
    m_isAudibleAlarm = fcp.isAudibleAlarm();

    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        const BasicChannelData& fcs = fcp.getChannelSettings(i);
        setAlarmTemp(i, fcs.alarmTemp);
        setManualRPM(i, fcs.speed);
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
        if (cd.minTemp() > to || !cd.isSet_MinTemp())
        {
            cd.setMinTemp(to);
            emit minLoggedTemp_changed(channel, to);
        }
        if (cd.maxTemp() < to || !cd.isSet_MaxTemp())
        {
            cd.setMaxTemp(to);
            emit maxLoggedTemp_changed(channel, to);
        }
        cd.setLastTemp(to);
        if (emitSignal) emit temperature_changed(channel, to);
    }

    /* ####### DEBUG FOR S/WARE AUTO */

    if (rampsReady())
    {
        for (int i = 0; i < FC_MAX_CHANNELS; ++i)
        {
            if (m_ramp[i].probeAffinity() == channel)
            {
                qDebug() << "Software Auto (Channel"
                            << channel
                            << ")"
                            << "Temp:"
                            << (m_isCelcius ? toCelcius(to) : to)
                            << "RPM:"
                            << m_ramp[i].temperatureToRpm(to);
            }
        }
    }

    /* ####### END DEBUG FOR S/WARE AUTO */
}

void FanControllerData::updateRPM(int channel, int to, bool emitSignal)
{
    FanChannelData& cd = m_channelSettings[channel];
    if (cd.lastRPM() != to || !cd.isSet_lastRPM())
    {
        if (cd.minLoggedRPM() > to || !cd.isSet_minLoggedRPM())
        {
            cd.setMinLoggedRPM(to);
            emit minLoggedRPM_changed(channel, to);
        }
        if (cd.maxLoggedRPM() < to || !cd.isSet_maxLoggedRPM())
        {
            cd.setMaxLoggedRPM(to);
            emit maxLoggedRPM_changed(channel, to);
        }
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
    int t = m_isCelcius ? ceil((temperature-32)*5.0/9) : temperature;
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
    return ceil((tempInF-32)*5.0/9);
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
int FanControllerData::toFahrenheit(int tempInC)
{
    return ceil(tempInC * 9/5.0 + 32);
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
