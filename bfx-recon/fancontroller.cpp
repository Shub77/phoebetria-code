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

// Uncomment for verbose debugging output
//#define PHO_FC_VERBOSE_DEBUG 1

static const int bitfenixrecon_vendorId = 3141;
static const int bitfenixrecon_productId = 28928;

static const unsigned bitfenix_flag_auto    = 1 << 0;
static const unsigned bitfenix_flag_celcius = 1 << 1;
static const unsigned bitfenix_flag_alarm   = 1 << 2;

static const int blockRequestsDefaultTimeout = 70;

static const fcCommandDef bfxReconCmdDefs[] = {
    { fcResp_TempAndSpeed, 0, (unsigned char)0x40,  QString("Channel 1 Temp & Speed") },
    { fcResp_TempAndSpeed, 1, (unsigned char)0x41,  QString("Channel 2 Temp & Speed") },
    { fcResp_TempAndSpeed, 2, (unsigned char)0x42,  QString("Channel 3 Temp & Speed") },
    { fcResp_TempAndSpeed, 3, (unsigned char)0x43,  QString("Channel 4 Temp & Speed") },
    { fcResp_TempAndSpeed, 4, (unsigned char)0x44,  QString("Channel 5 Temp & Speed") },

    { fcResp_DeviceFlags, -1, (unsigned char)0x60,  QString("Device Flags (Common)") },

    { fcResp_AlarmAndSpeed, 0, (unsigned char)0x80, QString ("Channel 1 Alarm Temp & Speed") },
    { fcResp_AlarmAndSpeed, 1, (unsigned char)0x81, QString ("Channel 2 Alarm Temp & Speed") },
    { fcResp_AlarmAndSpeed, 2, (unsigned char)0x82, QString ("Channel 3 Alarm Temp & Speed") },
    { fcResp_AlarmAndSpeed, 3, (unsigned char)0x83, QString ("Channel 4 Alarm Temp & Speed") },
    { fcResp_AlarmAndSpeed, 4, (unsigned char)0x84, QString ("Channel 5 Alarm Temp & Speed") },

    { fcResp_DeviceStatus, -1, (unsigned char)0xA0, QString("Device Status") },

    { fcResp_Handshake, -1, (unsigned char)0xF0,    QString ("ACK") },
    { fcResp_Handshake, -1, (unsigned char)0xFA,    QString ("NAK") },


    { fcReq_TempAndSpeed, 0, (unsigned char)0x30,   QString ("Req. channel 1 Temp & Speed") },
    { fcReq_TempAndSpeed, 1, (unsigned char)0x31,   QString ("Req. channel 2 Temp & Speed") },
    { fcReq_TempAndSpeed, 2, (unsigned char)0x32,   QString ("Req. channel 3 Temp & Speed") },
    { fcReq_TempAndSpeed, 3, (unsigned char)0x33,   QString ("Req. channel 4 Temp & Speed") },
    { fcReq_TempAndSpeed, 4, (unsigned char)0x34,   QString ("Req. channel 5 Temp & Speed") },

    { fcReq_DeviceFlags, -1, (unsigned char)0x50,   QString ("Req. device flags") },
    { fcReq_DeviceStatus, -1, (unsigned char)0x90,  QString ("Req. device status") },
    { fcReq_CurrentChannel, -1, (unsigned char)0x10, QString ("Req. current channgel") },

    { fcReq_AlarmAndSpeed, 0, (unsigned char)0x70,  QString ("Req. channel 1 Alarm Temp & Speed") },
    { fcReq_AlarmAndSpeed, 1, (unsigned char)0x71,  QString ("Req. channel 2 Alarm Temp & Speed") },
    { fcReq_AlarmAndSpeed, 2, (unsigned char)0x72,  QString ("Req. channel 3 Alarm Temp & Speed") },
    { fcReq_AlarmAndSpeed, 3, (unsigned char)0x73,  QString ("Req. channel 4 Alarm Temp & Speed") },
    { fcReq_AlarmAndSpeed, 4, (unsigned char)0x74,  QString ("Req. channel 5 Alarm Temp & Speed") },


    { fcSet_DeviceFlags, -1, (unsigned char)0x60, QString ("Set device flags") },

    { fcSet_SetRPM, 0, (unsigned char)0x80, QString("Set channel 0 speed") }


};
#define RESPONSE_DEF_COUNT (sizeof(bfxReconCmdDefs) / sizeof(bfxReconCmdDefs[0]))


static const int MAX_COMMANDQUEUE_LEN = 128;



/****************************************************************************
 ****************************************************************************
 class fcData
 ***************************************************************************/

FcData::FcData()
{
    m_dataLen = -1;
    m_blockCommandsAfterExecuting_timeout = 0;
}

FcData::FcData(const QByteArray &rawData)
{
    m_dataLen = -1;
    m_blockCommandsAfterExecuting_timeout = 0;
    setFromRawData(rawData);
}

int FcData::dataLen(void) const
{
    /* It is possible for the array to hold just one
     * 0x00 character. QByteArray::size() returns 0 for
     * the data length in this case, which is not what
     * is required.
     */
    //qDebug() << "Data len: " << QString::number(data.length());
    if (data.length() > 0) return data.length();

    return data.isNull() ? 0 : 1;
}

unsigned char FcData::calcChecksum(bool isRequest) const
{
    int len = dataLen();
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
    responseDef = FanController::getResponseDef(rawdata.at(1));
    if (responseDef == NULL) {
        qDebug() << "============== Unknown response code from device:"
                 << (qint8)rawdata.at(1);
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

#if defined QT_DEBUG
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

    int dataLen = this->dataLen();

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
 ****************************************************************************
 class FanController
 ***************************************************************************/

FanController::FanController(QObject *parent) :
    QObject(parent)
{
    m_deviceIsReady = false;
    m_pollNumber = 0;
    m_channelCycle = 0;
    m_blockRequestsTimeout = 0;
    connectSignals();
}

void FanController::connectSignals(void)
{
    QObject::connect(&m_io_device, SIGNAL(dataRX(QByteArray)),
                     this, SLOT(onRawData(QByteArray)));
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
    bool r = m_io_device.connect(bitfenixrecon_vendorId,
                                 bitfenixrecon_productId);

    if (r) emit deviceConnected();

    m_deviceIsReady = false;
    if (m_deviceIsReady) {
        requestDeviceStatus();
    }
    return r;
}

void FanController::disconnect(void)
{
    m_io_device.disconnect();

    emit deviceDisconnected();
}


bool FanController::isReady(void)
{    
    if (m_deviceIsReady) return true;
    requestDeviceStatus();

    return m_deviceIsReady;
}

bool FanController::isInterfaceConnected(void) const
{
    return m_io_device.isConnected();
}

const fcCommandDef* FanController::getResponseDef(unsigned char cmd)
{
    const fcCommandDef* found = NULL;
    for (unsigned i = 0; i < RESPONSE_DEF_COUNT; i++) {
        if (bfxReconCmdDefs[i].commandByte == cmd) {
            found = &bfxReconCmdDefs[i];
            break;
        }
    }
    return found;
}

const fcCommandDef* FanController::getCommandDef(
        fcCommandCategory category,
        int channel)
{
    const fcCommandDef* found = NULL;
    for (unsigned i = 0; i < RESPONSE_DEF_COUNT; i++) {
        if (bfxReconCmdDefs[i].category == category
                && bfxReconCmdDefs[i].channel == channel) {
            found = &bfxReconCmdDefs[i];
            break;
        }
    }
    return found;
}

/*--------------------------------------------------------------------------
  Responses (INPUT from device)
  -------------------------------------------------------------------------*/


/*
 */
void FanController::onPollTimerTriggered(void)
{
    if (!isInterfaceConnected()) return;

    processCommandQueue();

    if (m_blockRequestsTimeout > 0) {
        m_blockRequestsTimeout--;
        return;
    }

    // Check for pending data (from device) every time timer is triggered
    m_io_device.pollForData();

    if (m_pollNumber % 26 == 0) {  // 100ms*26 = 2.6s
        requestDeviceFlags(); // C/F, Auto/Manual, Alarm Audible/NotAudible
    } else if (m_pollNumber % 2 == 0 || m_pollNumber < 20) {
        requestAlarmAndSpeed(m_channelCycle + 1);
        requestTempAndSpeed(m_channelCycle + 1);
        m_channelCycle++;
        m_channelCycle %= 5;
    }

    m_pollNumber++;
}

void FanController::onRawData(QByteArray rawdata)
{
    FcData parsedData;
    parseRawData(rawdata, &parsedData);
}

bool FanController::parseRawData(QByteArray rawdata, FcData *parsedData)
{
    if (!parsedData->setFromRawData(rawdata)) {
        // Unknown response from device
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
#ifdef QT_DEBUG
        qDebug() << parsedData->command->desc;
#endif
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

    emit currentTemp(channel, rawToTemp(rawdata.at(2)));
    emit currentRPM(channel, rawToRPM(rawdata.at(4), rawdata.at(3)));
    emit maxRPM(channel, rawToRPM(rawdata.at(6), rawdata.at(5)));

#if defined QT_DEBUG// && PHO_FC_VERBOSE_DEBUG
    qDebug() << "Channel" << channel + 1
             << "----probe temp------" << rawToTemp(rawdata.at(2)) << "F";
    qDebug() << "Channel" << channel + 1
             << "----current RPM-----" << rawToRPM(rawdata.at(4), rawdata.at(3))
             << "RPM";
    qDebug() << "Channel" << channel + 1
             << "----max RPM---------" << rawToRPM(rawdata.at(6), rawdata.at(5))
             << "RPM";
#endif

}

void FanController::parseDeviceFlags(const QByteArray& rawdata)
{
    bool isAuto, isCelcius, isAudibleAlarm;

    isAuto =    rawdata[2] & bitfenix_flag_auto ? false : true;
    isCelcius = rawdata[2] & bitfenix_flag_celcius ? false : true;
    isAudibleAlarm =   rawdata[2] & bitfenix_flag_alarm ? true : false;

    emit deviceSettings(isCelcius, isAuto, isAudibleAlarm);

#if defined QT_DEBUG && PHO_FC_VERBOSE_DEBUG
    qDebug() << "##Auto: " << isAuto << "## is Celcius: " << isCelcius
             << "##Audible alarm:" << isAudibleAlarm;
#endif
}

void FanController::parseAlarmAndSpeed(int channel, const QByteArray &rawdata)
{
    // Byte 0:  data/packet length
    // Byte 1:  response code
    // Byte 2:  alarm temp
    // Byte 3:  alarm rpm (lo byte)       ??? TODO: Current Manual Speed ????
    // Byte 4:  alarm rpm (hi byte)       ??? TODO: Current Manual Speed ????
    // Byte 5:  checksum

    emit currentAlarmTemp(channel, rawToTemp(rawdata[2]));
    // TODO ??? emit currentRpmOnAlarm(channel, rawToRPM(rawdata[4], rawdata[3]));

#if defined QT_DEBUG && PHO_FC_VERBOSE_DEBUG
    qDebug() << "Channel" << channel + 1 << "----alarm temp------"
             << rawToTemp(rawdata[2]) << "F";
    qDebug() << "Channel" << channel + 1 << "----on alarm speed--"
             << rawToRPM(rawdata[4], rawdata[3]) << "RPM";
#endif
}

void FanController::parseDeviceStatus(const QByteArray& rawdata)
{
    m_deviceIsReady = rawdata[2] == 1 ? true : false;

#if defined QT_DEBUG && PHO_FC_VERBOSE_DEBUG
    qDebug() << "Device is: " << (m_deviceIsReady ? "Ready" : "Not Ready");
#endif
}

void FanController::parseHandshake(const QByteArray& rawdata)
{

}

int FanController::rawToTemp(unsigned char byte) const
{
    return (unsigned char)byte;
}

int FanController::rawToRPM(char highByte, char lowByte) const
{
    return (unsigned char)highByte*256 + (unsigned char)lowByte;
}

/*--------------------------------------------------------------------------
  Handling of the command queue
 -------------------------------------------------------------------------*/

void FanController::issueCommand(const FcData& cmd)
{
    // Discard old commands
    while (m_cmdQueue.length() > MAX_COMMANDQUEUE_LEN - 1) {
        m_cmdQueue.removeFirst();
    }
    m_cmdQueue.append(cmd);
}

void  FanController::processCommandQueue(void)
{
    /* We don't want to process all the commands at once because the device
     * only supports sending one command at a time; i.e. if more than one
     * command is sent only the last command sent is processed by the device
     */
    if (m_cmdQueue.isEmpty()) return;

    char reqBuff[8];    // Needs to be one more than max request size
    FcData dataToSend = m_cmdQueue.takeFirst();

    if (dataToSend.command) {
        blockSignals(true);
        dataToSend.toRawData(reqBuff, sizeof(reqBuff));

        if (dataToSend.m_blockCommandsAfterExecuting_timeout > 0) {
            blockRequests(dataToSend.m_blockCommandsAfterExecuting_timeout);
        }

        m_io_device.sendData(reqBuff, 8);

        blockSignals(false);
    }
#if 0
    QByteArray ba(reqBuff);
    qDebug() << "To Device: " << ba.toHex();
#endif
}

/*--------------------------------------------------------------------------
  Requests (OUTPUT to device)
  -------------------------------------------------------------------------*/

void FanController::requestDeviceStatus(void)
{
    FcData fcdata;
    const fcCommandDef* cmdDef;

    cmdDef = getCommandDef(fcReq_DeviceStatus, -1);
    fcdata.command = cmdDef;

    issueCommand(fcdata);
}

void FanController::requestTempAndSpeed(int channel)
{
    FcData fcdata;
    const fcCommandDef* cmdDef;

    Q_ASSERT (channel > 0 && channel <= 5);

    cmdDef = getCommandDef(fcReq_TempAndSpeed, channel-1);

    if (!cmdDef) {
#       ifdef QT_DEBUG
        qDebug() << "Requested Invalid Command. Temp and Speed, channel"
                 << QString::number(channel)
                 << "File: " << __FILE__ << "Line:" << __LINE__;
#       endif
        return;
    }

    fcdata.command = cmdDef;
    issueCommand(fcdata);
}

void FanController::requestAlarmAndSpeed(int channel)
{
    FcData fcdata;
    const fcCommandDef* cmdDef;

    Q_ASSERT (channel > 0 && channel <= 5);

    cmdDef = getCommandDef(fcReq_AlarmAndSpeed, channel-1);

    fcdata.command = cmdDef;
    issueCommand(fcdata);
}

void FanController::requestDeviceFlags(void)
{
    FcData fcdata;
    const fcCommandDef* cmdDef;

    cmdDef = getCommandDef(fcReq_DeviceFlags, -1);

    fcdata.command = cmdDef;
    issueCommand(fcdata);
}

bool FanController::setDeviceFlags(bool isCelcius,
                                   bool isAuto,
                                   bool isAudibleAlarm)
{

    FcData fcdata;
    const fcCommandDef* cmdDef;

    cmdDef = getCommandDef(fcSet_DeviceFlags, -1);

    fcdata.command = cmdDef;

    unsigned char bits;

    bits = !isCelcius ? bitfenix_flag_celcius : 0;
    bits |= !isAuto ? bitfenix_flag_auto : 0;
    bits |= isAudibleAlarm ? bitfenix_flag_alarm : 0;

    fcdata.data[0] = bits;

    fcdata.m_blockCommandsAfterExecuting_timeout = blockRequestsDefaultTimeout;
    issueCommand(fcdata);

    return true;
}

bool FanController::setChannelSettings(int channel,
                                         unsigned thresholdF,
                                         unsigned speed)
{
    FcData fcdata;
    const fcCommandDef* cmdDef;

    cmdDef = getCommandDef(fcSet_SetRPM, channel);

    fcdata.command = cmdDef;

    fcdata.data[0] = 90;
    fcdata.data[1] = speed % 256;
    fcdata.data[2] = speed / 256;

    fcdata.m_blockCommandsAfterExecuting_timeout = blockRequestsDefaultTimeout;
    issueCommand(fcdata);

    return true;
}
