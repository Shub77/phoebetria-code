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

    This class issues signals on a regular basis based on \e Events that
    (should) require processing. The class itself does nothing but issue
    signals that other classes monitor and act upon. The minimum interval
    that signals can be sent is dependendant on the global timer interval
    (this class connects to the global timer's timeout signal).

    Internally, signals are issued based on timer \e ticks. Each event has
    a \e tock to indicate when the signal should be issued; i.e. if
    \e tock (for the event) is set to 5 then the signal will be issued every
    5 ticks.

    \e intervals have milliseconds as their unit
    \e ticks are an integer representation of milliseconds;
       1 tick == minInterval() milleseconds

    \sa    EventItem, intervalToTick(), tickToInterval()
 */

/*! \class EventDispatcher::EventItem
 *  \brief Support class for EventDispatcher. Used to assign an interval
 *         (in \e ticks) when an event signal should be dispatched.
 */



/*-----------------------------------------------------------------------
  Static members
  -----------------------------------------------------------------------*/

//! The mininum interval that can be set
unsigned EventDispatcher::m_minInterval = 200;

//! Scheduled tasks
QList<EventDispatcher::Task> EventDispatcher::m_tasks;

//! Ticks elapsed since the timer started
QTimer EventDispatcher::m_timer;

/*************************************************************************/



/*! Default constructor. Does \e not initalise anything.
 */
EventDispatcher::Task::Task()
{
}

/*! Initialise to an event that will issue a signal every interval \e ticks

    \param e         TODO: Document
    \param interval  Dispatch interval in \e ticks; \sa intervalToTick()

    \note            \e tock is a multiple of the timer's interval.

    \sa intervalToTick(), tickToInterval()
*/
EventDispatcher::Task::Task(EventDispatcher::TaskId e, int interval)
{
    m_event = e;
    m_interval = interval;
}


/*! Initialise default values, issuable events and connects to the
    timer. The interval of the timer is set to minInterval()
*/
EventDispatcher::EventDispatcher(QObject *parent) :
    QObject(parent)
{
    m_timer.setInterval(m_minInterval);
    m_elapsedTicks = 0;
    initEvents();
    connectToTimerSignal();
}


/*! Populates the list of events that are issuable.

    Populates the list of (default) events that the EventDispatcher is
    responsible for issuing. Returns the number of events registered with the
    dispatcher.
 */
int EventDispatcher::initEvents(void)
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

    addEvent(Task(ReqAllDeviceRelated, intervalToTick(30000)));

    addEvent(Task(ReqDeviceFlags, intervalToTick(5000)));
    addEvent(Task(ReqAlarmTemps, intervalToTick(5000)));
    addEvent(Task(ReqMaxRpms, intervalToTick(5000)));
    addEvent(Task(ReqCurrentRpms, intervalToTick(5000)));
    addEvent(Task(ReqProbeTemps, intervalToTick(5000)));

    addEvent(Task(LogData, intervalToTick(30000)));

    return m_tasks.size();
}


/*! Add an event to the list of events to dispatch.
 */
void EventDispatcher::addEvent(const Task& e)
{
    m_tasks.append(e);

}

/*! Connect to the global timer signal.
 */
void EventDispatcher::connectToTimerSignal(void)
{
    connect(&(ph_phoebetriaApp()->pollTimer()), SIGNAL(timeout()),
            this, SLOT(onTimer()));
}


/*! Convert an interval in milliseconds to timer 'ticks'.

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
    return ceil((double)interval / m_timer.interval());
}


/*! Returns a \e tick converted into milliseconds.
*/
unsigned EventDispatcher::tickToInterval(unsigned tick) const
{
    return tick * m_timer.interval();
}

/*! The main dispatch function

    Issues a regular tick event (passes on
    the application timer's tick) and issues event signals for those
    due to be issued.
*/
void EventDispatcher::onTimer(void)
{

    // TODO: Issue "Tick event"

    for (int i = 0; i < m_tasks.size(); ++i)
    {
        const Task& item = m_tasks.at(i);
        if (m_elapsedTicks % item.tock() == 0)
        {
            // TODO: issue event
        }
    }

    ++m_elapsedTicks;
}
