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

#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QObject>
#include <QVariant>
#include <QSettings>



/** TODO

    PREFERENCES FOR V1.3

    tooltips on minimize[y/n]       ??
    show tray icon tooltips[y/n]    ??

    start minimized[y/n]
    minimize to tray[y/n]
    startup profile [string]
    shutdown profile [string]
    close vs. quite [y/n]
    channel names
    probe names


    Get rid of current implementation of this class and implement the above...

    */



class Preferences : public QObject
{
    Q_OBJECT

public:

    typedef enum
    {
        PKey_MinimiseToTray,
        PKey_ShowTooltipOnMinimise,
        PKey_IntervalMs_GlobalTimer,
        PKey_IntervalMs_FcCommonSettings,
        PKey_IntervalMs_FcAlarmTempAndMaxSpeed,
        PKey_IntervalMs_FcCurrentTempAndSpeed,

        PKey_PrimaryDb_DeleteOnAnyCreateError
    } KeyId;

    explicit Preferences(QObject *parent = 0);

    static QString filepath(void);

    void set(KeyId id, const QVariant& value);

    bool    minimiseToTray(bool defaultValue = true) const;
    bool    showToolTipOnMinimise(bool defaultValue = false) const;
    int     intervalMs_globalTimer(int defaultValue = 200);
    int     intervalMs_FcCommonSettings(int defaultValue = 200);
    int     intervalMs_FcAlarmTempAndMaxSpeed(int defaultValue = 5000);
    int     intervalMs_FcCurrentTempAndSpeed(int defaultValue = 5000);

protected:

    QString propertyName(KeyId id) const;

    void read(void);
    void write(void);

private:
    static const char* m_userPrefsGroup;

signals:
    
public slots:
    
};

#endif // PREFERENCES_H
