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

#include "phoebetriaapp.h"

QTimer PhoebetriaApp::m_fanController_pollTimer;
FanControllerIO PhoebetriaApp::m_fanControllerIO;

PhoebetriaApp::PhoebetriaApp(int &argc, char **argv)
    : QApplication(argc, argv)
{
    m_fanControllerIO.connect();

    QObject::connect(&m_fanController_pollTimer, SIGNAL(timeout()),
                     &m_fanControllerIO, SLOT(onPollTimerTriggered()));

    m_fanController_pollTimer.start(200);
}


/**************************************************************************
 Non-class functions
 *************************************************************************/


PhoebetriaApp* phoebetriaApp(void)
{
    return static_cast<PhoebetriaApp*> qApp;
}

FanControllerData& fanControllerData(void)
{
    return phoebetriaApp()->fanControllerIO().fanControllerData();
}
