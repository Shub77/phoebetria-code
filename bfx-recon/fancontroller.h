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

#ifndef PHOEBETRIA_FANCONTROLLER_H
#define PHOEBETRIA_FANCONTROLLER_H

#include <QObject>

class FanController : public QObject
{
    Q_OBJECT
public:
    explicit FanController(QObject *parent = 0);
    
    static int HID_vendorId(void);
    static int HID_productId(void);

    bool connect(void);
    bool disconnect(void);

    bool isConnected(void) const;

signals:
    void deviceConnected(void);
    void deviceDisconnected(void);

public slots:

private:
    bool m_isConnected;
};

#endif // PHOEBETRIA_FANCONTROLLER_H
