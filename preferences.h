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
#include <QHash>

class Preferences : public QObject
{
    Q_OBJECT

    /* At the moment just a wrapper around QVariant. Using a wrapper in case
     * entries become more complex.
     */
    class Entry
    {
    public:
        Entry();

        void set(int value) { m_value = value; }

        void set(bool value) { m_value = value; }

        QVariant value (void) const { return m_value; }

    private:

        QVariant m_value;

    };

public:
    explicit Preferences(QObject *parent = 0);


    void set(const QString& key, int value);
    void set(const QString& key, bool value);

private:

    QHash<QString, QVariant> m_prefs;   // Key, Value

signals:
    
public slots:
    
};

#endif // PREFERENCES_H
