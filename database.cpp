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

#include "database.h"

#include <QtSql>
#include <QString>
#include <QSettings>
#include <QDebug>

#include "utils.h"

QString Database::m_dbFilename = "phoebetria.sqlite";

QString Database::m_dbConnectionName = "phoebetriaDb";


Database::Database()
{
    initCommon();
}

void Database::initCommon(void)
{
    if (!QSqlDatabase::contains(m_dbConnectionName))
    {
        openDb();
    }
}


QString Database::databaseNameAndPath(void) const
{
    return m_dbPathAndName;
}

QSqlError Database::openDb()
{
    QString dbPath;


    QSettings settings(QSettings::IniFormat,
                       QSettings::UserScope,
                       "Phoebetria",
                       "Phoebetria");
    dbPath = QFileInfo(settings.fileName()).path();

    // If the database doesn't exist try and create it
    if( !QFile::exists(m_dbPathAndName))
    {
        // Filename doesn't exist? If not, check that at least the path does
        if (!checkPath(dbPath))
        {
            return QSqlError ("Error initialising database. Path does not exist"
                              " and could be created.");
        }
    }

    // At this point at least the path exists

    m_dbPathAndName = dbPath;
    m_dbPathAndName.append(QDir::separator()).append("Phoebetria.sqlite");
    m_dbPathAndName = QDir::toNativeSeparators(m_dbPathAndName);

    db = QSqlDatabase::addDatabase("QSQLITE", m_dbConnectionName);
    db.setDatabaseName(m_dbPathAndName);

    if (!db.open())
        return db.lastError();

    // Check default schema

    QStringList tables = db.tables();
    if (!tables.contains("Profile", Qt::CaseInsensitive))
    {
        QSqlQuery q(db);
        if (!q.exec(QLatin1String("create table Profile(name varchar, channel integer, setting varchar, value integer, primary key (name, channel, setting))")))
        {
            qDebug() << "****" << q.lastError();
            return q.lastError();
        }
    }

    return QSqlError();
}


QSqlError Database::saveProfile(const QString name, const QString setting, int channel, int value)
{
    QSqlQuery query(QSqlDatabase::database(m_dbConnectionName));

    if (!query.prepare(QLatin1String("insert or replace into Profile(name, setting, channel, value) values(:name, :setting, :channel, :value)")))
        return query.lastError();
    query.bindValue(":name", name);
    query.bindValue(":setting", setting);
    query.bindValue(":channel", channel);
    query.bindValue(":value", value);
    query.exec();

    return QSqlError();
}

QSqlError Database::eraseProfile(const QString name)
{
    QSqlQuery query(QSqlDatabase::database(m_dbConnectionName));

    if (!query.prepare(QLatin1String("delete from Profile where name = :name")))
        return query.lastError();
    query.bindValue(":name", name);
    query.exec();

    return QSqlError();
}

int Database::readProfile(const QString name, const QString setting, int channel)
{
    QSqlQuery query(QSqlDatabase::database(m_dbConnectionName));

    query.prepare(QLatin1String("select value from Profile where name = :name and setting = :setting and channel = :channel"));
    query.bindValue(":name", name, QSql::Out);
    query.bindValue(":setting", setting, QSql::Out);
    query.bindValue(":channel", channel, QSql::Out);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "SQL Query failed:" << query.lastError()
                 << "("
                 << "File:" << __FILE__ << ", Line: " << __LINE__
                 << ")";
#endif
        return -1;  // TODO: Need a better mechanism for reporting failure (valid returns may indeed be -1)
    }

    // Check number of rows selected
    if (query.size() > 0 && query.size() > 1)
    {
#ifdef QT_DEBUG
        qDebug() << "SQL Query returned wrong number of results:"
                 << query.lastError()
                 << "("
                 << "File:" << __FILE__ << ", Line: " << __LINE__
                 << ")";
#endif
        return -1;  // TODO: Need a better mechanism for reporting failure (valid returns may indeed be -1)
    }

    if (!query.first())
    {
        qDebug() << "Could not position on first query result!"
                 << "("
                 << "File:" << __FILE__ << ", Line: " << __LINE__
                 << ")";

        return -1;  // TODO: Need a better mechanism for reporting failure (valid returns may indeed be -1)
    }

    // return the value of the first row (there should only be one row)
    return query.value(0).toInt();
}

QStringList Database::readProfileNames()
{
    //qDebug() << m_dbConnectionName;

    QStringList m_ProfileList;
    QSqlQuery query(QSqlDatabase::database(m_dbConnectionName));

    //qDebug() << db.connectionName();
    query.exec(QLatin1String("select distinct name from Profile"));

    while( query.next() )
    {
        m_ProfileList << query.value(0).toString();
    }

    if (m_ProfileList.isEmpty())
    {
        return QStringList("** FAILED **");
    }

    return m_ProfileList;
}
