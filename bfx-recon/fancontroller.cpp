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

static const fcCommandDef bfxReconResponseDefs[] = {
    { fcResp_TempAndSpeed, 0, (unsigned char)0x40,  QString("Channel 1 Temp & Speed") },
    { fcResp_TempAndSpeed, 1, (unsigned char)0x41,  QString("Channel 2 Temp & Speed") },
    { fcResp_TempAndSpeed, 2, (unsigned char)0x42,  QString("Channel 3 Temp & Speed") },
    { fcResp_TempAndSpeed, 3, (unsigned char)0x43,  QString("Channel 4 Temp & Speed") },
    { fcResp_TempAndSpeed, 4, (unsigned char)0x44,  QString("Channel 5 Temp & Speed") },

    { fcResp_DeviceFlags, -1, (unsigned char)0x60,  QString("Device Flags (Common)") },

    { fcResp_AlarmAndSpeed, 0, (unsigned char)0x80, QString ("Channel 1 Alarm Temp & Current Speed") },
    { fcResp_AlarmAndSpeed, 1, (unsigned char)0x81, QString ("Channel 2 Alarm Temp & Current Speed") },
    { fcResp_AlarmAndSpeed, 2, (unsigned char)0x82, QString ("Channel 3 Alarm Temp & Current Speed") },
    { fcResp_AlarmAndSpeed, 3, (unsigned char)0x83, QString ("Channel 4 Alarm Temp & Current Speed") },
    { fcResp_AlarmAndSpeed, 4, (unsigned char)0x84, QString ("Channel 5 Alarm Temp & Current Speed") },

    { fcResp_DeviceStatus, -1, (unsigned char)0xA0, QString("Device Status") },

    { fcResp_Handshake, -1, (unsigned char)0xF0,    QString ("ACK") },
    { fcResp_Handshake, -1, (unsigned char)0xFA,    QString ("NAK") },

    { fcReq_GetChannelSettings, 0,  (unsigned char)0x30, "Request Channel 1 Temp & Speed" },
    { fcReq_GetChannelSettings, 1,  (unsigned char)0x31, "Request Channel 2 Temp & Speed" },
    { fcReq_GetChannelSettings, 2,  (unsigned char)0x32, "Request Channel 3 Temp & Speed" },
    { fcReq_GetChannelSettings, 3,  (unsigned char)0x33, "Request Channel 4 Temp & Speed" },
    { fcReq_GetChannelSettings, 4,  (unsigned char)0x34, "Request Channel 5 Temp & Speed" },
    { fcReq_GetDeviceStatus,    -1, (unsigned char)0x90, "Request device status" },
    { fcReq_GetCurrentChannel,  -1, (unsigned char)0x10, "Request current channel" },
    { fcReq_GetDeviceFlags,     -1, (unsigned char)0x50, "Request device flags" }
};
#define RESPONSE_DEF_COUNT (sizeof(bfxReconResponseDefs) / sizeof(bfxReconResponseDefs[0]))


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


unsigned char FcData::calcChecksum(bool isRequest) const
{
    int len = data.length();
    unsigned checksum = len + 1;

    if (isRequest) checksum += command->commandByte;

    for (int i = 0; i < len; ++i) {
        checksum += data.at(i);
    }
    checksum ^= 0xff;
    checksum = (checksum + 1) & 0xff;

    return checksum;
}


bool FcData::setFromRawData(const QByteArray& rawdata)
{
    const fcCommandDef* responseDef;

    if (rawdata.length() < 2) {
        qDebug ("FanController::parseRawData() not enough data");
        return false;
    }
    responseDef = FanController::getResponseDef(rawdata[1]);
    if (responseDef == NULL) {
        qDebug("============== Unknown response code from device");
        return false;
    }

    // TODO: Add bounds checking

    command = responseDef;
    channel = responseDef->channel;
    int len = rawdata.at(0);
    data.clear();
    for (int i = 1; i < len; i++) {   // copy data apart from checksum
        data.append(rawdata.at(i));
    }
    checksum = rawdata.at(len);

#ifdef QT_DEBUG
    if (checksum != calcChecksum(false)) {
        qDebug() << "Checksum failed (calculated" << calcChecksum(false)
                 << "expected" << checksum << ")";
    }
#endif

    return true;
}


bool FcData::toRawData(char *dest, int buffLen, bool pad)
{
    // pre: Always need 3 extra bytes for:
    //      1) the data length
    //      2) the command
    //      3) the checksum at the end
    Q_ASSERT (buffLen >= data.length() + 3);

    int dataLen = data.length();

    *(dest) = dataLen + 2;
    *(dest + 1) = command->commandByte;
    int i;
    for (i = 0; i < dataLen; i++) {
        *(dest + i + 2) = data.at(i);
    }
    *(dest + i + 2) = calcChecksum(true) - 1;
    i++;
    if (pad) {
        for (; i < buffLen; i++) {
            *(dest + i + 2) = (char)0x00;
        }
    }

    return true;
}


/****************************************************************************
 class FanController
 ***************************************************************************/


FanController::FanController(QObject *parent) :
    QObject(parent)
{
    m_deviceIsReady = false;
    m_pollNumber = 0;

    connectSignals();
}

const fcCommandDef* FanController::getResponseDef(unsigned char cmd)
{
    const fcCommandDef* found = NULL;
    for (unsigned i = 0; i < RESPONSE_DEF_COUNT; i++) {
        if (bfxReconResponseDefs[i].commandByte == cmd) {
            found = &bfxReconResponseDefs[i];
            break;
        }
    }
    return found;
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
    bool r = m_io_device.connect(bitfenixrecon_vendorId, bitfenixrecon_productId);

    if (r) emit deviceConnected();

    m_deviceIsReady = true; // Assume device is ready until it tells us otherwise
    return r;
}

void FanController::disconnect(void)
{
    m_io_device.disconnect();

    emit deviceDisconnected();
}

/** This function is different to isInterfaceConnected() in several aspects. First,
  * if the actual HID I/O device is not connected then this function
  * will: (a) attempt to make a connection; and (b) if the connection is
  * successful asks the device (rather than the interface) if it's ready.
  * In contrast, isInterfaceConnected() is at a lower level to see if the device
  * interface is connected (whether or not the device is "ready" is not
  * tested for beyond the level of the interface).
  *
  * @internal m_deviceIsReady is set (not in this function) by sending a
  *           request to the device to ask if it's ready (assuming the HID
  *           connection is established). isInterfaceConnected() may be true and this
  *           function still return false (i.e. if the interface is established
  *           but for whatever the actual device reports that it's not ready).
  */
bool FanController::isReady(void)
{
    if (!isInterfaceConnected()) {
        if (!connect()) {
            return false;
        }
    }
    requestDeviceStatus();
    return m_deviceIsReady;
}

/** Check if the I/O interface to the device is established. In most cases it's
  * probably better to use isReady() which not only checks if the interface is
  * established, but additionally whether or not the device has reported that
  * it's ready.
  *
  * @returns true == the I/O interface is established, otherwise false.
  */
bool FanController::isInterfaceConnected(void) const
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
    m_pollNumber++;
    m_pollNumber &= 0x07;       // 0 <= m_pollNumber <= 7

    // isReady() will try to connect the device iface if not already connected
    if (!isReady()) return;

    // Check for pending data (from device) every time timer is triggered
    m_io_device.pollForData();

    // Check device status every 8th poll
    if (m_pollNumber % 8 == 0) requestDeviceStatus();

}

void FanController::onRawData(QByteArray rawdata)
{
    FcData parsedData;
    parseRawData(rawdata, &parsedData);
}

bool FanController::parseRawData(QByteArray rawdata, FcData *parsedData)
{
    parsedData->setFromRawData(rawdata);

    if (!parsedData) {
        return false;
    }

    switch (parsedData->command->category)
    {
    case fcResp_TempAndSpeed:
        parseTempAndSpeed(parsedData->command->channel, rawdata);
        break;
    case fcResp_DeviceFlags:
        parseDeviceFlags(rawdata);
        break;
    case fcResp_AlarmAndSpeed:
        parseAlarmAndSpeed(parsedData->command->channel, rawdata);
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

#ifdef QT_DEBUG

    // TODO: Not sure if the fan speed reported is the speed to set the fan when
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


int FanController::rawToTemp(unsigned char byte) const
{
    return byte;
}

unsigned FanController::rawToRPM(char highByte, char lowByte) const
{
    return highByte*256 + lowByte;
}

void FanController::requestDeviceStatus(void)
{
    FcData fcdata;
    char reqBuff[9];

    fcdata.command = getResponseDef(0x90);
    if (fcdata.command == NULL) {
        qDebug() << "Requested unknown command. File: " << __FILE__ << "Line: " << __LINE__;
    }

    fcdata.toRawData(reqBuff, sizeof(reqBuff));  

    m_io_device.sendData(reqBuff);
}

