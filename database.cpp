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
#include <QSqlQuery>
#include <QString>
#include <QSettings>
#include <QDebug>
#include <QFile>

#include "dbprimaryschema.h"
#include "preferences.h"
#include "utils.h"

// TODO: Move this to "preferences"
static const bool g_deleteDatabaseOnAnyCreateError = true;

QString Database::m_dbFilename = "phoebetria.sqlite";

QString Database::m_dbConnectionName = "phoebetriaDb";

/**************************************************************************/
/* TODO:

    Add error checking
    Use transactions
 */
/**************************************************************************/


Database::Database()
    : m_dbPath(Preferences::filepath())
{
    m_dbPathAndName = m_dbPath;
    m_dbPathAndName.append(QDir::separator()).append("Phoebetria.sqlite");
    m_dbPathAndName = QDir::toNativeSeparators(m_dbPathAndName);
}

void Database::init(void)
{
    if (!QSqlDatabase::contains(m_dbConnectionName))
        connect();
}


QSqlError Database::connect()
{
    if (!verifyDbAndPathExist())
    {
        QString customErrorMsg = QObject::tr(
                "Error initialising database."
                " Path does not exist"
                " and path could be created: %1")
                    .arg(m_dbPathAndName);

        return QSqlError(customErrorMsg);
    }

    // At this point at least the path exists

    // TODO: ADD ERROR CHECKING!!!!!!

    QSqlError createError = QObject::tr("Error creating database.");

    if (!fileExists(m_dbPathAndName))
    {
        bool ok = PrimaryDbSchema::create(&m_dbPathAndName);
        if (!ok && g_deleteDatabaseOnAnyCreateError)
        {
            if (!QFile::remove(m_dbPathAndName))
                qDebug() << "Failed to delete db file";
            return createError;
        }
    }
    else
    {
        if (!PrimaryDbSchema::verify(&m_dbPathAndName))
        {
            QString oldDbName(m_dbPathAndName);
            oldDbName += ".orig";
            if (fileExists(oldDbName))
            {
                if (!QFile::remove(oldDbName))
                {
                    return QSqlError(QObject::tr("Failed to delete old db"));
                }
            }
            QFile::rename(m_dbPathAndName, oldDbName);

            bool ok = PrimaryDbSchema::create(&m_dbPathAndName, &oldDbName);

            if (!QFile::remove(oldDbName))
            {
                return QSqlError(QObject::tr("Failed to delete old db"));
            }
            if (!ok && g_deleteDatabaseOnAnyCreateError)
            {
                QFile::remove(m_dbPathAndName);
                return createError;
            }
        }
    }

    db = QSqlDatabase::addDatabase("QSQLITE", m_dbConnectionName);
    db.setDatabaseName(m_dbPathAndName);

    if (!db.open())
        return db.lastError();

    // Enable foreign key support
    if (db.driverName() == "QSQLITE")
    {
        QSqlQuery q(db);
        q.exec("PRAGMA foreign_keys = ON");
    }

    return QSqlError();
}

/*! Checks if the database file exists. If not, check the path exists and
 *  create the path if necessary.
 */
bool Database::verifyDbAndPathExist(void) const
{
    if (QFile::exists(m_dbPathAndName))
        return true;
    return checkPath(m_dbPath);
}

bool Database::openProfile()
{
    QSqlRelationalTableModel m_Profile;

    m_Profile.setTable("Profile");
    m_Profile.setRelation(0,QSqlRelation("ChannelSetting","p_id", "name"));

    if (!m_Profile.select())
    {
        qDebug() << m_Profile.lastError();
    }

    return true;
}

QSqlError Database::saveProfile(const QString &name,
                                const QString &setting,
                                int channel, int value)
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

QSqlError Database::eraseProfile(const QString& name)
{
    QSqlQuery query(QSqlDatabase::database(m_dbConnectionName));

    if (!query.prepare(QLatin1String("delete from Profile where name = :name")))
        return query.lastError();
    query.bindValue(":name", name);
    query.exec();

    return QSqlError();
}

int Database::readProfile(const QString &name,
                          const QString &setting,
                          int channel)
{
    QSqlQuery query(QSqlDatabase::database(m_dbConnectionName));

    query.prepare(QLatin1String(
        "select value from Profile"
        " where name = :name and setting = :setting and channel = :channel"));
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
    QStringList profileList;
    QSqlQuery query(QSqlDatabase::database(m_dbConnectionName));

    query.exec(QLatin1String("select distinct name from Profile"));

    while (query.next())
    {
        profileList << query.value(0).toString();
    }

#if 0
    if (profileList.isEmpty())
        return QStringList("** FAILED **");
#endif

    return profileList;
}


