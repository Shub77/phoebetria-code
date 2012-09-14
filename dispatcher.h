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

class PhoebetriaApp;    // fwd decl

class EventDispatcher : public QObject
{
    Q_OBJECT

    friend class PhoebetriaApp;

    typedef enum TaskId
    {
        //!< Emitted every time the timer is triggered
        Tock,

        //!< All channel related reqs
        ReqAllDeviceRelated,

        //!< Device flags
        ReqDeviceFlags,

        //! Alarm temp and manual rpm (all channels)
        ReqAlarmTempAndManualRpm,

        //! Current temp and rpm (all channels)
        ReqTempAndCurrRpmAndMaxRpm,

        //!< Log data
        LogData

    } TaskId; //!< Signal "types" that can be issued.


    class Task
    {
    public:
        Task();
        Task(EventDispatcher::TaskId taskId, int interval);

        TaskId taskId(void) const { return m_taskId; }
        int interval(void) const { return m_interval; }

    private:
        TaskId m_taskId;
        int m_interval;    // the task dispatch interval, for this task
    };

public:
    explicit EventDispatcher(QObject *parent = 0);

    void init(void);

    //! The minumum interval (in milliseconds) that can be set
    unsigned minInterval(void) const
        { return m_minInterval; }

    unsigned intervalToTick(unsigned interval) const;
    unsigned tickToInterval(unsigned tick) const;

protected:

    int initTasks(void);
    void addTask(const Task& e);
    void connectToTimerSignal(void);

private:

    static QList<Task> m_tasks;

    unsigned m_minInterval;
    unsigned m_elapsedTicks;

signals:

    void task(TaskId task);

public slots:

    void onTimer(void);
};

#endif // PHOEBETRIA_DISPATCHER_H
