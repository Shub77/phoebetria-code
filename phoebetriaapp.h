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

#ifndef PHOEBETRIA_APP_H
#define PHOEBETRIA_APP_H

#include <QApplication>
#include <QTimer>
#include "bfx-recon/fancontroller.h"

class PhoebetriaApp : public QApplication
{
public:
    PhoebetriaApp(int &argc, char **argv);

    QTimer& fanController_pollTimer(void) { return m_fanController_pollTimer; }

private:
    static QTimer m_fanController_pollTimer;
    static FanController m_fanController;
};


#endif // PHOEBETRIA_APP_H
