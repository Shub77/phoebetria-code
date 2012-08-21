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

#include "fancontrollerio.h"


//---------------------------------------------------------------------

/* HID Report as recieved *from* the device
 *
 * Structure for the BitFenix Recon (BfxRecon):
 *
 *  Byte#
 *    0     Control Byte (see FanControllerIO::ControlByte)
 *    1     Data Length (len). The number of bytes of data (0 <= len <= 5)
 *    2-7   Data + checksum. The checksum at the byte after 3 + len.
 *          The bytes after the checksum (if any) are zero padding.
 */
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


FanControllerIO::FanControllerIO(QObject *parent) :
    QObject(parent)
{
}
