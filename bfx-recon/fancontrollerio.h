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

    enum ControlByte {

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


    enum DeviceSettingsFlag {
        Auto                            = 1U << 0,
        Celcius                         = 1U << 1,
        AudibleAlarm                    = 1U << 2
    };

    /* USB Request Block
     *
     * Structure for the BitFenix Recon (BfxRecon):
     *
     *  Byte#
     *    0     USB Report ID (0x00 for the recon)
     *    1     Control Byte (see FanControllerIO::ControlByte)
     *    2     Data Length (len). The number of bytes of data (0 <= len <= 4)
     *    3-8   Data + checksum. The checksum at the byte after 3 + len.
     *          The bytes after the checksum (if any) are zero padding.
     */
    class URB {
        unsigned char m_data[8];
    };


    /* This is the URB without the USB Report ID, BfxRecon control byte,
     * the data length byte (preceding the data in the actual URB),
     * and the trailing checksum.
     */
    class URB_Fragment {
        ControlByte controlByte;
        unsigned char data[4];
    };


    /* Constructors
     */
    explicit FanControllerIO(QObject *parent = 0);
};

#endif // FANCONTROLLERIO_H
