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
#include "fancontrollerio.h"


//---------------------------------------------------------------------

static const unsigned short int HID_ProductId =   28928;
static const unsigned short HID_VendorId =  3141;


/**********************************************************************
  FanControllerIO::Input
 *********************************************************************/

bool FanControllerIO::Input::set(int blockLen, const unsigned char *block)
{
    /* HID Report as recieved *from* the device
     *
     * Structure for the BitFenix Recon (BfxRecon):
     *
     *  Byte#
     *    0     Data Length (len). The number of bytes of data (0 <= len <= 5)
     *    1     Control Byte (see FanControllerIO::ControlByte)
     *    2-7   Data + checksum. The checksum at the byte after 3 + len.
     *          The bytes after the checksum (if any) are zero padding.
     */

    if (blockLen < 2) {
        qDebug ("FanController::parseRawData() not enough data");
        return false;
    }

    m_dataLen = *block;
    m_controlByte = (ControlByte)*(block+1);

    for (int i = 2; i < m_dataLen; i++) {
        *(m_data + i - 2) = *(block + i);
    }

    m_checksum = *(block + m_dataLen);

    unsigned calculatedChecksum = FanControllerIO::calcChecksum(
                RX_NULL,
                m_dataLen-1,    // Skipping the first byte
                block+1
                );

    // Actual data length does not include bytes 0 and 1 of the input
    m_dataLen = m_dataLen - 2;


#ifdef QT_DEBUG
    if (m_checksum != calculatedChecksum) {

        qDebug() << "File:" << QString(__FILE__)
                 << "Line:" << QString::number(__LINE__)
                 << "++++ Checksum mismatch."
                 << "Expected" << QString::number(m_checksum)
                 << "Got" << QString::number(calculatedChecksum);
#endif

        return false; // Checksum failure
    }

    return true;
}


/**********************************************************************
  FanControllerIO::Request
 *********************************************************************/


FanControllerIO::Request::Request()
{
    m_controlByte = TX_NULL;
    m_dataLen = 0;
}

bool FanControllerIO::Request::toURB(int blockLen,
                                     unsigned char* block,
                                     bool pad)
{
    int i;

    *block = 0x00;              // URB report ID
    *(block + 1) = m_dataLen + 2;
    *(block + 2) = m_controlByte;

    for (i = 3; i < m_dataLen; i++) {
        *(block + i) = m_data[i-3];
    }

    *(block + i) = FanControllerIO::calcChecksum(m_controlByte,
                                                     m_dataLen,
                                                     m_data) - 1;

    qDebug() << "Creating URB, Checksum:" << QString::number((*block + i));
    i++;

    if (pad) {
        for (; i < blockLen; i++) {
            *(block + i) = 0x00;
        }
    }

    return true;
}

/**********************************************************************
  FanControllerIO
 *********************************************************************/

/* Static functions */

unsigned char FanControllerIO::calcChecksum(
        ControlByte ctrlByte,
        int blockLen,
        const unsigned char *block
    )
{

    unsigned checksum;

    checksum = blockLen + 1;
    checksum += ctrlByte;

    for (int i = 0; i < blockLen; ++i) {
        checksum += *(block + i);
    }
    checksum ^= 0xff;
    checksum = (checksum + 1) & 0xff;
    //checksum &= 0xff;

    return checksum;
}

//---------------------------------------------------------------------

FanControllerIO::FanControllerIO(QObject *parent) :
    QObject(parent)
{
    m_pollNumber = 0;
    connectSignals();
}

void FanControllerIO::connectSignals(void)
{
    QObject::connect(&m_io_device, SIGNAL(dataRX(QByteArray)),
                     this, SLOT(onRawData(QByteArray)));
}

bool FanControllerIO::connect(void)
{
    bool r = m_io_device.connect(HID_VendorId, HID_ProductId);

    if (r) emit deviceConnected();

    return r;
}


bool FanControllerIO::isConnected(void) const
{
    return m_io_device.isConnected();
}


void FanControllerIO::disconnect(void)
{
    m_io_device.disconnect();

    emit deviceDisconnected();
}


void FanControllerIO::onPollTimerTriggered(void)
{

    // Check for pending data (from device) every time timer is triggered
    m_io_device.pollForData();

    if (m_pollNumber % 2) {
        requestDeviceFlags();
    }

    m_pollNumber++;
}


void FanControllerIO::onRawData(QByteArray rawdata)
{
    Input parsedData;

    parsedData.set(rawdata.length(), (const unsigned char*)rawdata.constData());
    if (parsedData.m_controlByte == TX_NAK) {
        qDebug() << "NAK";
    }
}

//---------------------------------------------------------------------
// Requests
//---------------------------------------------------------------------
void FanControllerIO::requestDeviceFlags(void)
{
    Request r;

    r.m_controlByte = TX_DeviceSettings;
    r.setURB();

    qDebug() << "URB set";

    int bytesWritten = m_io_device.sendData(r.m_URB, sizeof(r.m_URB));
    qDebug() << "Bytes written:" << QString::number(bytesWritten);
}


//---------------------------------------------------------------------

bool FanControllerIO::setDeviceFlags(bool isCelcius,
                                   bool isAuto,
                                   bool isAudibleAlarm)
{
#if 0
    FcData fcdata;
    const fcCommandDef* cmdDef;

    cmdDef = getCommandDef(fcSet_DeviceFlags, -1);

    fcdata.command = cmdDef;

    unsigned char bits;

    bits = !isCelcius ? bitfenix_flag_celcius : 0;
    bits |= !isAuto ? bitfenix_flag_auto : 0;
    bits |= isAudibleAlarm ? bitfenix_flag_alarm : 0;

    fcdata.data[0] = bits;

    //fcdata.m_blockCommandsAfterExecuting_timeout = blockRequestsDefaultTimeout;
    issueCommand(fcdata);

    m_pollNumber  = 0;
#endif
    return true;
}

bool FanControllerIO::setChannelSettings(int channel,
                                         unsigned thresholdF,
                                         unsigned speed)
{
#if 0
    FcData fcdata;
    const fcCommandDef* cmdDef;

    cmdDef = getCommandDef(fcSet_SetChannelSettings, channel);

    if (!cmdDef) {
        qDebug() << "FanController::setChannelSettings()"
                 << ": Invalid command";
        return false;
    }

    fcdata.command = cmdDef;

    fcdata.data[0] = thresholdF;
    fcdata.data[1] = speed % 256;
    fcdata.data[2] = speed / 256;

    //fcdata.m_blockCommandsAfterExecuting_timeout = blockRequestsDefaultTimeout;
    issueCommand(fcdata);

    m_pollNumber  = 0;
#endif
    return true;
}

bool FanControllerIO::setFromProfile(const FanControllerProfile& profile)
{
#if 0
    setDeviceFlags(profile.isCelcius(), profile.isAuto(), profile.isAudibleAlarm());

    for (int i = 0; i < FC_MAX_CHANNELS; i++) {
        BasicChannelData chd = profile.getChannelSettings(i);
        int speed = chd.speed == -1 ? 65535 : chd.speed;
        setChannelSettings(i, chd.alarmTemp, speed);
    }

    m_pollNumber  = 0;

#endif
    return true;
}


