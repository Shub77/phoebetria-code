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
#include <QTimer>


class EventDispatcher : public QObject
{
    Q_OBJECT

    typedef enum TaskId
    {
        ReqAllDeviceRelated, //!< All channel related reqs
        ReqDeviceFlags,      //!< Device flags
        ReqAlarmTemps,       //!< Alarm temps (all channels)
        ReqMaxRpms,          //!< Max RPM (all channels)
        ReqCurrentRpms,      //!< Current RPM (all channels)
        ReqProbeTemps,       //!< Probe temp (all "channels")

        LogData              //!< Log data

    } TaskId; //!< Signal "types" that can be issued.

    class Task
    {
    public:
        Task();
        Task(EventDispatcher::TaskId e, int interval);

        int tock(void) const { return m_interval; }

    private:
        TaskId m_event;
        int m_interval;    // the task dispatch interval, for this task
    };

public:
    explicit EventDispatcher(QObject *parent = 0);

    //! The minumum interval (in milliseconds) that can be set
    int minInterval(void) const
        { return m_minInterval; }

    int intervalToTick(int interval) const;
    int tickToInterval(int tick) const;

protected:

    int initEvents(void);
    void addEvent(const Task& e);
    void connectToTimerSignal(void);

private:

    static QTimer m_timer;

    static int m_minInterval;       // The mininum interval that can be set
    static QList<Task> m_tasks;     // Scheduled tasks

    int m_elapsedTicks; // The number of ticks elapsed since the timer started

signals:
    
public slots:

    void onTimer(void);
};

#endif // PHOEBETRIA_DISPATCHER_H
