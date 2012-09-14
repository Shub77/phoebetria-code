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

#ifndef PHOEBETRIA_DATABASE_H
#define PHOEBETRIA_DATABASE_H


#include <QString>
#include <QSettings>
#include <QtSql>

class Database
{

public:

    Database();

    static QStringList readProfileNames();

    static int readProfile(const QString& name,
                           const QString& setting,
                           int channel);

    static QSqlError saveProfile(const QString& name,
                                 const QString& setting,
                                 int channel,
                                 int value);

    static QSqlError eraseProfile(const QString name);

protected:

    void initCommon(void);

    QSqlError openDb();

private:

    QSqlDatabase db;

    QString m_dbPathAndName;

    static QString m_dbFilename;
    static QString m_dbConnectionName;
};

#endif // PHOEBETRIA_DATABASE_H
