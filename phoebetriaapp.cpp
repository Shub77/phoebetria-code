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

    QFile file(":/other/Phoebetria.qss");
    file.open(QFile::ReadOnly);
    QString PhoebetriaStyleSheet = QLatin1String(file.readAll());
    setStyleSheet(PhoebetriaStyleSheet);

    DatabaseManager db;
    db.initAllDatabases();

    m_globalTimer.start(200);
    m_dispatcher.start(200);

    m_fanControllerIO.connect();            // Connect to the IO device
    m_fanControllerIO.connectSignals();

    m_fanControllerIO.fanControllerData().connectSignals();

}

void PhoebetriaApp::commitData(QSessionManager& manager)
{
    shutdown();

    QApplication::commitData(manager);
}


/* This function ensures that the FanControllerIO is shutdown correctly;
   i.e. that all request in the event queue have been processed. This is
   especially required when the app was in software auto mode and the
   Recon needs to be reset back to a pre-software-auto state.
 */

bool PhoebetriaApp::shutdown(void)
{
    // Wait for all pending tasks to be processed
    m_dispatcher.shutdown();

    /* We don't know how many ms have elapsed since the request queue was
       last processed, so delay before the loop to make sure at least 200ms
       have elapsed since the previous processing of the request queue
      */
    ShutdownHelper::wait(200);

    /* Loop until the request queue is emptied
     */
    while (!m_fanControllerIO.shutdown())
    {
        ShutdownHelper::wait(200);
    }
    return true;
}
