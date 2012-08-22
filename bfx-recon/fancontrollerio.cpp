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

static const int HID_ProductId =  3141;
static const int HID_VendorId =   28928;

//---------------------------------------------------------------------


unsigned char FanControllerIO::calcChecksum(
        ControlByte ctrlByte,
        int blockLen,
        const unsigned char *block
    )
{

    unsigned checksum;

    checksum = blockLen;
    checksum += ctrlByte;

    for (int i = 0; i < blockLen; ++i) {
        checksum += *(block + i);
    }
    checksum ^= 0xff;
    checksum = (checksum + 1) & 0xff;

    return checksum;
}

//---------------------------------------------------------------------

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
        *(m_data + i) = *(block + 2 + i);
    }

    m_checksum = *(block + 2 + m_dataLen);
    if (m_checksum != calcChecksum()) {

#ifdef QT_DEBUG
        qDebug() << "File:" << QString(__FILE__)
                 << "Line:" << QString(__LINE__)
                 << "++++ Checksum mismatch";
#endif

        return false; // Checksum failure
    }

    return true;
}


//---------------------------------------------------------------------

FanControllerIO::FanControllerIO(QObject *parent) :
    QObject(parent)
{
    connectSignals();
}

void FanControllerIO::connectSignals(void)
{
    QObject::connect(&m_io_device, SIGNAL(dataRX(QByteArray)),
                     this, SLOT(onRawData(QByteArray)));
}

bool FanControllerIO::connect(void)
{
    bool r = m_io_device.connect(3141, 28928);//HID_VendorId, HID_ProductId);

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

}


void FanControllerIO::onRawData(QByteArray rawdata)
{
    Input parsedData;

    parsedData.set(rawdata.length(), (const unsigned char*)rawdata.constData());
}
