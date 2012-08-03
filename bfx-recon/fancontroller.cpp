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

#include <QDebug>
#include "fancontroller.h"

static const int bitfenixrecon_vendorId = 3141;
static const int bitfenixrecon_productId = 28928;

static const unsigned bitfenix_flag_auto    = 1 << 0;
static const unsigned bitfenix_flag_celcius = 1 << 1;
static const unsigned bitfenix_flag_alarm   = 1 << 2;

static const fcResponseCodeDef bfxReconResponseCodes[] = {
    { fcResp_TempAndSpeed, 0, 0x40, 7, QString("Channel 1 Temp & Speed") },
    { fcResp_TempAndSpeed, 1, 0x41, 7, QString("Channel 2 Temp & Speed") },
    { fcResp_TempAndSpeed, 2, 0x42, 7, QString("Channel 3 Temp & Speed") },
    { fcResp_TempAndSpeed, 3, 0x43, 7, QString("Channel 4 Temp & Speed") },
    { fcResp_TempAndSpeed, 4, 0x44, 7, QString("Channel 5 Temp & Speed") },

    { fcResp_DeviceFlags, -1, 0x60, 2, QString("Device Flags (Common)") },

    { fcResp_AlarmAndSpeed, 0, 0x80, -1, QString ("Channel 1 Alarm Temp & Current Speed") },
    { fcResp_AlarmAndSpeed, 1, 0x81, -1, QString ("Channel 2 Alarm Temp & Current Speed") },
    { fcResp_AlarmAndSpeed, 2, 0x82, -1, QString ("Channel 3 Alarm Temp & Current Speed") },
    { fcResp_AlarmAndSpeed, 3, 0x83, -1, QString ("Channel 4 Alarm Temp & Current Speed") },
    { fcResp_AlarmAndSpeed, 4, 0x84, -1, QString ("Channel 5 Alarm Temp & Current Speed") },

    { fcResp_DeviceStatus, -1, 0xA0, 2, QString("Device Status") },

    { fcResp_Handshake, -1, 0xF0, -1, QString ("ACK") },
    { fcResp_Handshake, -1, 0xFA, -1, QString ("NAK") }

};

#define RESPONSECODE_COUNT (sizeof(bfxReconResponseCodes) / sizeof(bfxReconResponseCodes[0]))

QMap<char, const fcResponseCodeDef*> FanController::m_responseCodes;

FanController::FanController(QObject *parent) :
    QObject(parent)
{
    m_deviceIsReady = false;
    initResponseCodeMap();
    connectSignals();
}

void FanController::initResponseCodeMap(void)
{
    for (unsigned i = 0; i < RESPONSECODE_COUNT; i++) {
        m_responseCodes.insert(bfxReconResponseCodes[i].code,
                               &bfxReconResponseCodes[i]);
    }
}

int FanController::HID_vendorId(void)
{
    return bitfenixrecon_vendorId;
}

int FanController::HID_productId(void)
{
    return bitfenixrecon_productId;
}

bool FanController::connect(void)
{
    bool r = false;

    r = m_io_device.connect(bitfenixrecon_vendorId, bitfenixrecon_productId);

    // assume device is ready until it tell us otherwise
    m_deviceIsReady = true;

    if (r) emit deviceConnected();

    return r;
}

void FanController::disconnect(void)
{
    m_io_device.disconnect();

    emit deviceDisconnected();
}

bool FanController::isConnected(void) const
{
    return m_io_device.isConnected();
}

void FanController::connectSignals(void)
{
    QObject::connect(&m_io_device, SIGNAL(dataRX(QByteArray)),
                     this, SLOT(onRawData(QByteArray)));
}

void FanController::onPollTimerTriggered(void)
{
    qDebug("Poll");
    m_io_device.pollForData();
}

void FanController::onRawData(QByteArray rawdata)
{
#ifdef QT_DEBUG
    qDebug("Got raw data");
    qDebug(rawdata.toHex());
#endif
    parseRawData(rawdata);
}

void FanController::parseRawData(QByteArray rawdata)
{
    const fcResponseCodeDef* responseDef;

    if (rawdata.length() < 2) {
        qDebug ("FanController::parseRawData() given empty array");
        return;
    }
    responseDef = m_responseCodes.value(rawdata[1]);
    if (responseDef == NULL) {
        qDebug("============== Unknown response code from device");
        return;
    }
#ifdef QT_DEBUG
    QString debugOut;
    debugOut = "Got " + responseDef->desc;
    qDebug() << debugOut;
#endif

    switch (responseDef->category)
    {
    case fcResp_TempAndSpeed:
        parseTempAndSpeed(responseDef->channel, rawdata);
        break;
    case fcResp_DeviceFlags:
        parseDeviceFlags(rawdata);
        break;
    case fcResp_AlarmAndSpeed:
        break;
    case fcResp_DeviceStatus:
        parseDeviceStatus(rawdata);
        break;
    case fcResp_Handshake:
        break;
    default:
        qDebug() << "Unhandled response category";
        break;
    }
}

void FanController::parseTempAndSpeed(int channel, const QByteArray &rawdata)
{
    // Byte 0:  data/packet length
    // Byte 1:  response code
    // Byte 2:  temp
    // Byte 3:  rpm (lo byte)
    // Byte 4:  rpm (hi byte)
    // Byte 5:  checksum

#ifdef QT_DEBUG
    qDebug() << "Temp for channel " << channel + 1 << ":" << rawToTemp(rawdata[2]) << "F";
    qDebug() << "Fan #" << channel + 1 << "@" << rawToRPM(rawdata[4], rawdata[3]) << "RPM";
#endif

}

void FanController::parseDeviceFlags(const QByteArray& rawdata)
{
    bool isAuto, isCelcius, isAlarm;

    isAuto =    rawdata[2] & bitfenix_flag_auto ? false : true;
    isCelcius = rawdata[2] & bitfenix_flag_celcius ? false : true;
    isAlarm =   rawdata[2] & bitfenix_flag_alarm ? true : false;

    qDebug() << "Auto: " << isAuto << "Celcius: " << isCelcius
             << "Alarm:" << isAlarm;
}

void FanController::parseAlarmAndSpeed(int channel, const QByteArray &rawdata)
{

}

void FanController::parseDeviceStatus(const QByteArray& rawdata)
{
    m_deviceIsReady = rawdata[2] == 1 ? true : false;
    qDebug() << "Device is: " << (m_deviceIsReady ? "Ready" : "Not Ready");
}

void FanController::parseHandshake(const QByteArray& rawdata)
{

}


int FanController::rawToTemp(char byte) const
{
    return byte;
}

unsigned FanController::rawToRPM(char highByte, char lowByte) const
{
    return highByte*256 + lowByte;
}

char FanController::calcChecksum(QByteArray rawdata) const
{

}
