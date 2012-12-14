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
#include <QString>


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

    */

#if defined Q_WS_MAC
#   define DEFAULT_CLOSEBEHAVIOUR false
#else
#   define DEFAULT_CLOSEBEHAVIOUR true
#endif


class Preferences : public QObject
{
    Q_OBJECT

public:

    explicit Preferences(QObject *parent = 0);

    static QString filepath(void);

    bool    startMinimised(bool defaultVal = false) const;

    bool    minimiseToTray(bool defaultVal = true) const;

    bool    showTrayIconTooltips(bool defaultVal = true) const;

    QString startupProfile(QString defaultVal = "") const;

    QString shutdownProfile(QString defaultVal = "") const;

    bool    quitOnCloseButton(bool defaultVal = DEFAULT_CLOSEBEHAVIOUR) const;

    QString channelName(unsigned channel, QString defaultVal = "") const;
    QString probeName(unsigned channel, QString defaultVal = "") const;

protected:

private:

    QSettings m_settings;

signals:
    
public slots:
    
};

#undef DEFAULT_CLOSEBEHAVIOUR

#endif // PREFERENCES_H
