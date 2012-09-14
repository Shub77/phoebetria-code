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
#include "bfx-recon/fancontrollerio.h"


#define ph_phoebetriaApp() (static_cast<PhoebetriaApp*> qApp)
#define ph_fanControllerData() (ph_phoebetriaApp()->fcd())
#define ph_fanControllerIO() (ph_phoebetriaApp()->fanControllerIO())

class PhoebetriaApp : public QApplication
{
public:
    PhoebetriaApp(int &argc, char **argv);

    FanControllerIO& fanControllerIO(void)
        { return m_fanControllerIO; }

    FanControllerData& fcd(void)
        { return m_fanControllerIO.fanControllerData(); }

private:
    static FanControllerIO m_fanControllerIO;
};


#endif // PHOEBETRIA_APP_H
