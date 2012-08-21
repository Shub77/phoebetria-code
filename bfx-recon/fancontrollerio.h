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

#ifndef FANCONTROLLERIO_H
#define FANCONTROLLERIO_H

#include <QObject>


class FanControllerIO : public QObject
{
    Q_OBJECT
public:

    static const int VendorId;
    static const int ProductId;

    //---------------------------------------------------------------------

    enum ControlByte {

        RX_NULL                         = 0x00,

        TX_CurrentChannel               = 0x10,

        TX_TempAndSpeed_Channel0        = 0x30,
        TX_TempAndSpeed_Channel1        = 0x31,
        TX_TempAndSpeed_Channel2        = 0x32,
        TX_TempAndSpeed_Channel3        = 0x33,
        TX_TempAndSpeed_Channel4        = 0x34,

        RX_TempAndSpeed_Channel0        = 0x40,
        RX_TempAndSpeed_Channel1        = 0x41,
        RX_TempAndSpeed_Channel2        = 0x42,
        RX_TempAndSpeed_Channel3        = 0x43,
        RX_TempAndSpeed_Channel4        = 0x44,

        TX_DeviceSettings               = 0x50,
        RX_DeviceSettings               = 0x60,

        TX_AlarmAndSpeed_Channel0       = 0x70,
        TX_AlarmAndSpeed_Channel1       = 0x71,
        TX_AlarmAndSpeed_Channel2       = 0x72,
        TX_AlarmAndSpeed_Channel3       = 0x73,
        TX_AlarmAndSpeed_Channel4       = 0x74,

        RX_AlarmAndSpeed_Channel0       = 0x80,
        RX_AlarmAndSpeed_Channel1       = 0x81,
        RX_AlarmAndSpeed_Channel2       = 0x82,
        RX_AlarmAndSpeed_Channel3       = 0x83,
        RX_AlarmAndSpeed_Channel4       = 0x84,

        TX_DeviceStatus                 = 0x90,

        RX_ACK                          = 0xF0,
        TX_NAK                          = 0xFA

    };

    //---------------------------------------------------------------------

    enum DeviceSettingsFlag {
        Auto                            = 1U << 0,
        Celcius                         = 1U << 1,
        AudibleAlarm                    = 1U << 2
    };


    //---------------------------------------------------------------------


    static unsigned char calcChecksum(
            ControlByte ctrlByte,
            int blockLen,
            const unsigned char* block
        );


    /* Parsed Input from the device
     */
    class Input {

    public:

    protected:

        // Set from raw data
        bool set(int blockLen, unsigned char* block);

        unsigned char calcChecksum(void) const
            { return FanControllerIO::calcChecksum(RX_NULL, m_dataLen, m_data); }

    private:
        ControlByte m_controlByte;
        unsigned char m_checksum;
        int m_dataLen;              // This may be < sizeof(m_data)
        unsigned char m_data[5];
    };


    //---------------------------------------------------------------------

    class Request {

    protected:
        bool toURB(int blockLen, unsigned char* block, bool pad);

        unsigned char calcChecksum(void) const
            { return FanControllerIO::calcChecksum(m_controlByte, m_dataLen, m_data); }

    private:
        ControlByte m_controlByte;
        int m_dataLen;              // This may be < sizeof(m_data)
        unsigned char m_data[4];    // Can only _send_ 4 data bytes
                                    // (incoming may have 5)
    };


    //---------------------------------------------------------------------

    /* Constructors
     */
    explicit FanControllerIO(QObject *parent = 0);
};

#endif // FANCONTROLLERIO_H
