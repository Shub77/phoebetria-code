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

#include "dispatcher.h"

#include <math.h>

#include "phoebetriaapp.h"


/*************************************************************************/
/*!
    \class  EventDispatcher
    \brief  Responsible for scheduling all 'timer related' tasks that
            require undertaking. E.g. polling the fan controller device.

    This class issues signals on a regular basis based on \e Tasks that
    (should) require processing. The class itself does nothing but issue
    signals that other classes monitor and act upon. The minimum interval
    that signals can be sent is dependendant on minInterval(). Additionally,
    minInterval() is dependant on PhoebetriaApp::m_globalTimer (the
    minimum interval for the dispatcher is set to m_globalTimer's interval
    because the dispatcher is attached to the global timer's timeout()
    signal).

    Internally, signals are issued based on timer \e ticks. Each task has
    an \e interval (in ticks) to indicate when the signal should be issued;
    e.g. if the task interval is 5 then a signal will be issued every 5
    ticks.

    \e intervals have milliseconds as their unit
    \e ticks are an integer representation of milliseconds;
       1 tick == minInterval() milleseconds

    \sa    EventItem, intervalToTick(), tickToInterval()
 */

/*! \class EventDispatcher::Task
 *  \brief Support class for EventDispatcher. Tasks define signals for the
 *         dispatcher to dispatch based on the task's interval.
 */


/*-----------------------------------------------------------------------
  Static members
  -----------------------------------------------------------------------*/

//! Scheduled tasks
QList<EventDispatcher::Task> EventDispatcher::m_tasks;

/*************************************************************************/



/*! Default constructor. Does \e not initalise anything.
 */
EventDispatcher::Task::Task()
{
}

/*! Initialise a task that will issue a signal every interval \e ticks

    \param taskId    The type of signal to emit
    \param interval  Dispatch interval in \e ticks; \sa intervalToTick()

    \sa TaskId, intervalToTick(), tickToInterval()
*/
EventDispatcher::Task::Task(EventDispatcher::TaskId taskId, int interval)
{
    m_taskId = taskId;
    m_interval = interval;
}


EventDispatcher::EventDispatcher(QObject *parent) :
    QObject(parent)
{
}

/*! Initialise default values, issuable events and connects to the
    timer. The interval of the timer is set to minInterval()
*/
void EventDispatcher::init(void)
{
    m_minInterval = ph_phoebetriaApp()->globalTimerInterval();
    m_elapsedTicks = 0;
    initTasks();
    connectToTimerSignal();
}

/*! Populates the dispatcher schedule.

    Populates the list of (default) tasks that the EventDispatcher is
    responsible for issuing. Returns the number of tasks registered with the
    dispatcher.
 */
int EventDispatcher::initTasks(void)
{

    /*
     * Note: initEvents() may be called at a point after initial constructor
     * (e.g. if setBaseInterval() is called) therefore make sure the
     * list is empty
     */
    if (!m_tasks.isEmpty())
    {
        m_tasks.clear();
    }

    addTask(Task(ReqAllDeviceRelated, intervalToTick(30000)));

    addTask(Task(ReqDeviceFlags, intervalToTick(5000)));

    addTask(Task(ReqAlarmTempAndManualRpm, intervalToTick(5000)));
    addTask(Task(ReqTempAndCurrRpmAndMaxRpm, intervalToTick(5000)));

    addTask(Task(LogData, intervalToTick(30000)));

    return m_tasks.size();
}


/*! Add a task to the schedule.
 */
void EventDispatcher::addTask(const Task& e)
{
    m_tasks.append(e);

}

/*! Connect to the timer signal.
 */
void EventDispatcher::connectToTimerSignal(void)
{
    connect(&ph_phoebetriaApp()->m_globalTimer, SIGNAL(timeout()),
            this, SLOT(onTimer()));
}


/*! Convert an interval in milliseconds to timer 'ticks'.

    Returns \e interval converted to dispatch timer ticks.

    \param   interval  The interval in milliseconds
    \returns The interval converted to timer ticks

    \note Ticks are a multiple of EventDispatcher::baseInterval(). If the
    supplied interval is not a multiple of the base interval then it is
    rounded \e up. Related to this is that if \e interval is less than
    minInterval() the returned \e tick will be 1.

    \sa EventDispatcher::tickToInterval()
 */
unsigned EventDispatcher::intervalToTick(unsigned interval) const
{
    return ceil((double)interval / m_minInterval);
}


/*! Returns a \e tick converted into milliseconds.

    Returns \e tick in milliseconds.
*/
unsigned EventDispatcher::tickToInterval(unsigned tick) const
{
    return tick * m_minInterval;
}

/*! The main dispatch function

    Issues a regular tick event (passes on
    the application timer's tick) and issues event signals for those
    due to be issued.
*/
void EventDispatcher::onTimer(void)
{

    emit task(Tock);

    for (int i = 0; i < m_tasks.size(); ++i)
    {
        const Task& item = m_tasks.at(i);
        if (m_elapsedTicks % item.interval() == 0)
        {
            emit task(item.taskId());
        }
    }

    ++m_elapsedTicks;
}
