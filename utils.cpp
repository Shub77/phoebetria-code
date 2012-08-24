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

#include "utils.h"

QString toHexString(const unsigned char *data, int len)
{
    /* QByteArray can do a similar thing, but as far as I know it cannot be
     * made to format the output in this manner
     */
    static const char* hexDigits = "0123456789ABCDEF";

    QString result;

    for (int i = 0; i < len; i++) {
        unsigned char cc = *(data + i);
        if (i != 0) result.append(' ');
        result.append(hexDigits[(cc >> 4) & 0x0f]);
        result.append(hexDigits[cc & 0x0f]);
    }

    return result;
}
