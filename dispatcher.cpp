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

/*-----------------------------------------------------------------------
  Static members
  -----------------------------------------------------------------------*/
int EventDispatcher::m_minInterval = 100;

QList<EventDispatcher::EventItem> EventDispatcher::m_events;



/*************************************************************************/
/*! @class EventItem
 *  @brief Support class for EventDispatcher. Used to assign an interval
 *         (in \e ticks) when an event signal should be dispatched.
 */


/*! @brief Default constructor. Does \e not initalise anything.
 */
EventDispatcher::EventItem::EventItem()
{
}

/*! @brief Initialise to an event \e that will issue a signal every \e tock
 *  intervals.
 *
 * @param e         @see EventDispatcher::Event
 * @param tock      The event e will be dispatched every \i tock ticks.
 *
 * @note            @param tock is a multiple of the timer's base interval.
 *
 * @see EventDispatcher::intervalToTick()
 * @see EventDispatcher::tickToInterval()
 */
EventDispatcher::EventItem::EventItem(EventSignal e, int tock)
{
    m_event = e;
    m_tock = tock;
}



/*************************************************************************/
/*! @class  EventDispatcher
 *  @brief  Responsible for scheduling all 'timer related' tasks that
 *          require undertaking. E.g. polling the fan controller device.
 *
 *  This class issues signals on a regular basis based on \e Events that
 *  (should) require processing. The class itself does nothing but issue
 *  signals that other classes monitor and act upon. The minimum interval
 *  that signals can be sent is dependendant on the global timer interval
 *  (this class connects to the global timer's timeout signal).
 *
 *  Internally, signals are issued based on timer \e ticks. Each event has
 *  a \e tock to indicate when the signal should be issued; i.e. if
 *  \e tock (for the event) is set to 5 then the signal will be issued every
 *  5 ticks.
 *
 * @see:    EventItem
 * @see:    EventDispatcher::intervalToTick()
 * @see:    EventDispatcher::tickToInterval()
 */

/*!
 * @brief Initialise default values, issuable events and connects to the
 * application's (global) timer.
 *
 * The interval is dependant on the global timer's timout value.
 * Therefore, the minimum interval for the dispatcher is the same as the
 * global timer interval; m_minInterval is set, by default, to match the
 * global timer.
 *
 */
EventDispatcher::EventDispatcher(QObject *parent) :
    QObject(parent)
{
    m_minInterval = ph_phoebetriaApp()->pollTimerInterval();
    m_baseInterval = m_minInterval;
    m_totalTicks = 0;
    initEvents();
    connectToTimerSignal();
}


/*!
 * @brief Populates the list of events that are issuable.
 *
 * Populates the list of (default) events that the EventDispatcher is
 * responsible for issuing. Returns the number of events registered with the
 * dispatcher.
 *
 */
int EventDispatcher::initEvents(void)
{

    /*
     * Note: initEvents() may be called at a point after initial constructor
     * (e.g. if setBaseInterval() is called) therefore make sure the
     * list is empty
     */
    if (!m_events.isEmpty())
    {
        m_events.clear();
    }

    addEvent(EventItem(ReqAllDeviceRelated, intervalToTick(30000)));

    addEvent(EventItem(ReqDeviceFlags, intervalToTick(5000)));
    addEvent(EventItem(ReqAlarmTemps, intervalToTick(5000)));
    addEvent(EventItem(ReqMaxRpms, intervalToTick(5000)));
    addEvent(EventItem(ReqCurrentRpms, intervalToTick(5000)));
    addEvent(EventItem(ReqProbeTemps, intervalToTick(5000)));

    addEvent(EventItem(LogData, intervalToTick(30000)));

    return m_events.size();
}


/*! @brief Add an event to the list of events to dispatch.
 */
void EventDispatcher::addEvent(const EventItem& e)
{
    m_events.append(e);

}

/*! @brief Connect to the global timer signal.
 */
void EventDispatcher::connectToTimerSignal(void)
{
    connect(&(ph_phoebetriaApp()->pollTimer()), SIGNAL(timeout()),
            this, SLOT(onTimer()));
}


/*!
 * @brief Convert an interval in milliseconds to timer 'ticks'.
 *
 * @param   interval  The interval in milliseconds
 * @returns The interval converted to timer ticks
 *
 * @note Ticks are a multiple of EventDispatcher::baseInterval(). If the
 * supplied interval is not a multiple of the base interval then it is
 * rounded \e up.
 *
 * @see EventDispatcher::tickToInterval()
 */
int EventDispatcher::intervalToTick(int interval) const
{
    return ceil((double)interval / m_baseInterval);
}


/*!
 * @brief Returns a \e tick converted into milliseconds.
 *
 * @see EventDispatcher::intervalToTick()
 */
int EventDispatcher::tickToInterval(int tick) const
{
    return tick * m_baseInterval;
}

/*!
 * @brief The main dispatch function. Issues a regular tick event (passes on
 *        the application timer's tick) and issues event signals for those
 *        due to be issued.
 */
void EventDispatcher::onTimer(void)
{

    // TODO: Issue "Tick event"

    for (int i = 0; i < m_events.size(); ++i)
    {
        const EventItem& item = m_events.at(i);
        if (m_totalTicks % item.tock() == 0)
        {
            // TODO: issue event
        }
    }

    ++m_totalTicks;
}
