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
#include "dbmanager.h"

FanControllerIO PhoebetriaApp::m_fanControllerIO;
EventDispatcher PhoebetriaApp::m_dispatcher;
QTimer PhoebetriaApp::m_globalTimer;


ShutdownHelper::ShutdownHelper(QThread *parent)
    : QThread(parent)
{

}

void ShutdownHelper::wait(unsigned long ms)
{
    msleep(ms);
}

PhoebetriaApp::PhoebetriaApp(int &argc, char **argv)
    : QApplication(argc, argv)
{
    setOrganizationName("Phoebetria");
    setApplicationName("Phoebetria");
    QSettings::setDefaultFormat(QSettings::IniFormat);

    DatabaseManager db;
    db.initAllDatabases();

    m_globalTimer.start(200);

    m_dispatcher.start(200);

    m_fanControllerIO.connect();
    m_fanControllerIO.connectSignals();

}

bool PhoebetriaApp::shutdown(void)
{
    // Wait for all pending tasks to be processed
    m_dispatcher.shutdown();

    ShutdownHelper::wait(200);
    //qDebug() << "Shutting down";
    while (!m_fanControllerIO.shutdown())
    {
        //qDebug() << ".";
        ShutdownHelper::wait(200);
    }
    return true;
}
