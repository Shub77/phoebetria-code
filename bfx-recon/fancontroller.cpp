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

#include "fancontroller.h"

static const int bitfenixrecon_vendorId = 3141;
static const int bitfenixrecon_productId = 28928;


FanController::FanController(QObject *parent) :
    QObject(parent)
{
    m_isConnected = false;
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

    // TODO: Implement

    if (r) emit deviceConnected();

    return r;
}

bool FanController::disconnect(void)
{
    bool r = false;

    // TODO: Implement

    if (r) emit deviceDisconnected();

    return r;
}

bool FanController::isConnected(void) const
{
    return m_isConnected;   // TODO: probably should query the HID connection instead
}
