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

FanControllerIO PhoebetriaApp::m_fanControllerIO;
EventDispatcher PhoebetriaApp::m_dispatcher;
QTimer PhoebetriaApp::m_globalTimer;

PhoebetriaApp::PhoebetriaApp(int &argc, char **argv)
    : QApplication(argc, argv)
{
    Database db;

    db.open();

    m_globalTimer.start(200);

    m_dispatcher.start(200);

    m_fanControllerIO.connect();
    m_fanControllerIO.connectSignals();

}
