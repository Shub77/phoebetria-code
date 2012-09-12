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
#include "database.h"

QTimer PhoebetriaApp::m_pollTimer;
FanControllerIO PhoebetriaApp::m_fanControllerIO;

PhoebetriaApp::PhoebetriaApp(int &argc, char **argv)
    : QApplication(argc, argv)
{
	Database();

    m_fanControllerIO.connect();

    QObject::connect(&m_pollTimer, SIGNAL(timeout()),
                     &m_fanControllerIO, SLOT(onPollTimerTriggered()));

    m_pollTimer.start(200);
}
