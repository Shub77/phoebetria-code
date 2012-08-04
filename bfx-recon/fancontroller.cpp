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

static const fcCommandDef bfxReconCommandDefs[] = {
    { fcResp_TempAndSpeed, 0, 0x40,  QString("Channel 1 Temp & Speed") },
    { fcResp_TempAndSpeed, 1, 0x41,  QString("Channel 2 Temp & Speed") },
    { fcResp_TempAndSpeed, 2, 0x42,  QString("Channel 3 Temp & Speed") },
    { fcResp_TempAndSpeed, 3, 0x43,  QString("Channel 4 Temp & Speed") },
    { fcResp_TempAndSpeed, 4, 0x44,  QString("Channel 5 Temp & Speed") },

    { fcResp_DeviceFlags, -1, 0x60,  QString("Device Flags (Common)") },

    { fcResp_AlarmAndSpeed, 0, 0x80, QString ("Channel 1 Alarm Temp & Current Speed") },
    { fcResp_AlarmAndSpeed, 1, 0x81, QString ("Channel 2 Alarm Temp & Current Speed") },
    { fcResp_AlarmAndSpeed, 2, 0x82, QString ("Channel 3 Alarm Temp & Current Speed") },
    { fcResp_AlarmAndSpeed, 3, 0x83, QString ("Channel 4 Alarm Temp & Current Speed") },
    { fcResp_AlarmAndSpeed, 4, 0x84, QString ("Channel 5 Alarm Temp & Current Speed") },

    { fcResp_DeviceStatus, -1, 0xA0, QString("Device Status") },

    { fcResp_Handshake, -1, 0xF0,    QString ("ACK") },
    { fcResp_Handshake, -1, 0xFA,    QString ("NAK") },

    { fcReq_GetChannelSettings, 0,  0x30, "Request Channel 1 Temp & Speed" },
    { fcReq_GetChannelSettings, 1,  0x31, "Request Channel 2 Temp & Speed" },
    { fcReq_GetChannelSettings, 2,  0x32, "Request Channel 3 Temp & Speed" },
    { fcReq_GetChannelSettings, 3,  0x33, "Request Channel 4 Temp & Speed" },
    { fcReq_GetChannelSettings, 4,  0x34, "Request Channel 5 Temp & Speed" },
    { fcReq_GetDeviceStatus,    -1, 0x90, "Request device status" },
    { fcReq_GetCurrentChannel,  -1, 0x10, "Request current channel" },
    { fcReq_GetDeviceFlags,     -1, 0x50, "Request device flags" }
};
#define COMMAND_DEF_COUNT (sizeof(bfxReconCommandDefs) / sizeof(bfxReconCommandDefs[0]))


/****************************************************************************
 class fcData
 ***************************************************************************/

FcData::FcData()
{

}

FcData::FcData(const QByteArray &rawData)
{
    setFromRawData(rawData);
}

#if 0
char FcData::calcChecksum(QByteArray rawdata, int length) const
{
    unsigned checksum = length + 1;

    for (int i = 1; i < length; ++i) {
        checksum += rawdata[i];
    }
    checksum ^= 0xff;
    checksum = (checksum + 2) & 0xff;

    return checksum;
}
#endif


bool FcData::setFromRawData(const QByteArray& rawdata)
{
    const fcCommandDef* responseDef;

    if (rawdata.length() < 2) {
        qDebug ("FanController::parseRawData() not enough data");
        return false;
    }
    responseDef = FanController::commandDef(rawdata[1]);
    if (responseDef == NULL) {
        qDebug("============== Unknown response code from device");
        return false;
    }
#ifdef QT_DEBUG
    QString debugOut;
    debugOut = "Got " + responseDef->desc;
    qDebug() << debugOut;
#endif

    // TODO: Add bounds checking

    command = responseDef;
    channel = responseDef->channel;
    int len = rawdata.at(0);
    data.clear();
    for (int i = 1; i < len; i++) {   // copy data apart from checksum
        data.append(rawdata.at(i));
    }
    checksum = rawdata.at(len);

    return true;
}

/****************************************************************************
 class FanController
 ***************************************************************************/

QMap<char, const fcCommandDef*> FanController::m_commandDefs;

FanController::FanController(QObject *parent) :
    QObject(parent)
{
    m_deviceIsReady = false;
    m_pollNumber = 0;

    initCommandDefs();
    connectSignals();
}

void FanController::initCommandDefs(void)
{
    for (unsigned i = 0; i < COMMAND_DEF_COUNT; i++) {
        m_commandDefs.insert(bfxReconCommandDefs[i].commandByte,
                               &bfxReconCommandDefs[i]);
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
    m_pollNumber++;
    m_pollNumber &= 0x07;       // 0 <= m_pollNumber <= 7

    // Check for pending data (from device) every time timer is triggered
    m_io_device.pollForData();

    // Check device status every 8th poll
    if (m_pollNumber & 0x01) requestDeviceStatus();

}

void FanController::onRawData(QByteArray rawdata)
{
#ifdef QT_DEBUG
    qDebug("Got raw data");
    qDebug(rawdata.toHex());
#endif
    FcData parsedData;
    parseRawData(rawdata, &parsedData);
}

bool FanController::parseRawData(QByteArray rawdata, FcData *parsedData)
{
    parsedData->setFromRawData(rawdata);

#if 0
    switch (responseDef->category)
    {
    case fcResp_TempAndSpeed:
        parseTempAndSpeed(responseDef->channel, rawdata);
        break;
    case fcResp_DeviceFlags:
        parseDeviceFlags(rawdata);
        break;
    case fcResp_AlarmAndSpeed:
        parseAlarmAndSpeed(responseDef->channel, rawdata);
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

    return true;
#endif
}

void FanController::parseTempAndSpeed(int channel, const QByteArray &rawdata)
{
    // Byte 0:  data/packet length
    // Byte 1:  response code
    // Byte 2:  temp
    // Byte 3:  rpm (lo byte)
    // Byte 4:  rpm (hi byte)
    // Byte 5:  maxRPM (lo)
    // Byte 6:  maxRPM (hi)
    // Byte 7:  checksum

#ifdef QT_DEBUG
    qDebug() << "Temp for channel " << channel + 1 << ":" << rawToTemp(rawdata[2]) << "F";
    qDebug() << "Fan #" << channel + 1 << "@" << rawToRPM(rawdata[4], rawdata[3]) << "RPM";
    qDebug() << "Fan # " << channel +1 << "max speed:" << rawToRPM(rawdata[6], rawdata[5]) << "RPM";
#endif

}

void FanController::parseDeviceFlags(const QByteArray& rawdata)
{
    bool isAuto, isCelcius, isAudibleAlarm;

    isAuto =    rawdata[2] & bitfenix_flag_auto ? false : true;
    isCelcius = rawdata[2] & bitfenix_flag_celcius ? false : true;
    isAudibleAlarm =   rawdata[2] & bitfenix_flag_alarm ? true : false;

    qDebug() << "##Auto: " << isAuto << "## is Celcius: " << isCelcius
             << "##Audible alarm:" << isAudibleAlarm;
}

void FanController::parseAlarmAndSpeed(int channel, const QByteArray &rawdata)
{
    // Byte 0:  data/packet length
    // Byte 1:  response code
    // Byte 2:  alarm temp
    // Byte 3:  rpm (lo byte)
    // Byte 4:  rpm (hi byte)
    // Byte 5:  checksum


    // char csum = calcChecksum(rawdata, 5);
    // qDebug() << "Calculated checksum: " << (unsigned int)csum;
#ifdef QT_DEBUG

    // TODO: Not sure if the fan speed repoted is the speed to set the fan when
    //       the alarm is reached

    qDebug() << "Alarm temp for channel " << channel + 1 << ":" << rawToTemp(rawdata[2]) << "F";
    qDebug() << "Fan # speed on alarm" << channel + 1 << "@" << rawToRPM(rawdata[4], rawdata[3]) << "RPM";
#endif

}

void FanController::parseDeviceStatus(const QByteArray& rawdata)
{
    m_deviceIsReady = rawdata[2] == 1 ? true : false;
    qDebug() << "Device is: " << (m_deviceIsReady ? "Ready" : "Not Ready");
}

void FanController::parseHandshake(const QByteArray& rawdata)
{

}


void FanController::requestDeviceStatus(void)
{
#if 0
    const fcRequestCodeDef* def;
    QByteArray packet;
    def = m_requestCodes.value(fcReq_GetDeviceStatus);
    if (!def) {
        qDebug() << "Unknown request attempted";
        return;
    }

    packet.append(0x02);      // length
    packet.append(def->code);
    packet.append(calcChecksum(packet, packet.length()));

    qDebug() << "****** Sending Request: " << packet.toHex();
    int byteswritten = m_io_device.sendData(packet);
    qDebug() << "****** Bytes written: " << byteswritten;
#endif
}


int FanController::rawToTemp(unsigned char byte) const
{
    return byte;
}

unsigned FanController::rawToRPM(char highByte, char lowByte) const
{
    return highByte*256 + lowByte;
}


