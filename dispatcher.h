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

#ifndef PHOEBETRIA_DISPATCHER_H
#define PHOEBETRIA_DISPATCHER_H

#include <QObject>
#include <QList>


// Dispatch/Action types
// --------------
//
// **** These are for scheduled/regular issuing of device requests or other
// **** actions. No actual request is actually made (or action undergone),
// **** rather a signal that the action is to undertaken is dispatched and
// **** the classes watching those signals carry out the actual action(s)
// ****
// **** The signals are issued based on a schedule with a minumum
// **** timeout of minInterval(). Different action types can have different
// **** schedules that are a multiple of minInterval()
//
// AllDeviceRelated         : Issue requests for all channel related reqs
//
// Device flags             : Issue request to device for device flags
// Channels alarm temps     : Issue request to device for alarm temps
// Channels current RPM     : Issue request to device for current RPMs
// Channels max RPM         : Issue request to device for max RPMs
// Probe temps              : Issue request to device for probe temps
// Log data                 : Issue request that data be logged
//


class EventDispatcher : public QObject
{
    Q_OBJECT

    typedef enum EventSignal
    {
        ReqAllDeviceRelated, //!< All channel related reqs
        ReqDeviceFlags,      //!< Device flags
        ReqAlarmTemps,       //!< Alarm temps (all channels)
        ReqMaxRpms,          //!< Max RPM (all channels)
        ReqCurrentRpms,      //!< Current RPM (all channels)
        ReqProbeTemps,       //!< Probe temp (all "channels")

        LogData              //!< Log data

    } EventSignal; //!< Signal "types" that can be issued.

    class EventItem
    {
    public:
        EventItem();
        EventItem(EventSignal e, int tock);

        int tock(void) const { return m_tock; }

    private:
        EventSignal m_event;
        int m_tock;         // 'tock' is the tick on which to issue the event
    };

public:
    explicit EventDispatcher(QObject *parent = 0);

    int intervalToTick(int interval) const;
    int tickToInterval(int tick) const;

protected:

    int initEvents(void);
    void addEvent(const EventItem& e);
    void connectToTimerSignal(void);

private:

    // The mininum interval that can be set
    static int m_minInterval;
    static QList<EventItem> m_events;

    // The interval (in ms) that the signal dispatcher is called
    int m_baseInterval;

    int m_totalTicks;

    // cmd, interval


signals:
    
public slots:

    void onTimer(void);
};

#endif // PHOEBETRIA_DISPATCHER_H
