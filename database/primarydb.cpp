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

#include "primarydb.h"

#include <QSettings>

#include "dbmanager.h"
#include "primarydb_schema.h"
#include "utils.h"

// TODO: Move this to "preferences"
static const bool g_deleteDatabaseOnAnyCreateError = true;

PrimaryDb::PrimaryDb()
{
}

void PrimaryDb::init(void)
{
    QString dbConnName = connectionName();
    if (!QSqlDatabase::contains(dbConnName))
        connect(dbConnName);
}

QStringList PrimaryDb::profileNames()
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

QSqlError PrimaryDb::connect(const QString& connectionName)
{
    if (!verifyDbAndPathExist(connectionName))
    {
        QString customErrorMsg = QObject::tr(
                "Error initialising database."
                " Path does not exist"
                " and path could be created: %1")
                    .arg(m_dbPathAndName);

        return QSqlError(customErrorMsg);
    }

    QSqlError err;

    if (!fileExists(m_dbPathAndName))
        err = createNewDb(connectionName);
    else
        err = checkExistingDb(connectionName);

    if (err.isValid()) return err;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", m_dbConnectionName);
    db.setDatabaseName(m_dbPathAndName);

    if (!db.open())
        return db.lastError();

    err = enableFkSupport(connectionName);

    return err;
}

QSqlError PrimaryDb::createNewDb(const QString &connectionName)
{
    QSqlError err = PrimaryDbSchema::create(&m_dbPathAndName);
    if (err.isValid() && g_deleteDatabaseOnAnyCreateError)
    {
        if (!QFile::remove(m_dbPathAndName))
            qDebug() << "Failed to delete db file";
    }
    return err;
}

QSqlError PrimaryDb::checkExistingDb(const QString &connectionName)
{
    QSqlError err;

    if (!PrimaryDbSchema::verify(&m_dbPathAndName))
        err = recreateDb(connectionName);

    return err;
}

QSqlError PrimaryDb::recreateDb(const QString &connectionName)
{
    QSqlError err;

    QString oldDbName(m_dbPathAndName);
    oldDbName += ".orig";
    if (fileExists(oldDbName))
    {
        if (!QFile::remove(oldDbName))
            return QSqlError(QObject::tr("Failed to delete old db"));
    }
    QFile::rename(m_dbPathAndName, oldDbName);

    err = PrimaryDbSchema::create(&m_dbPathAndName, &oldDbName);

    if (!QFile::remove(oldDbName))
        qDebug() << "Failed to delete old db";

    if (err.isValid() && g_deleteDatabaseOnAnyCreateError)
    {
        if (!QFile::remove(m_dbPathAndName))
            qDebug() << "Failed to remove partially created db";
    }

    return err;
}

// Enable foreign key support
// pre: db is open
QSqlError PrimaryDb::enableFkSupport(const QString &connectionName)
{
    QSqlError err;
    QSqlDatabase db = QSqlDatabase::database(m_dbConnectionName);

    if (db.driverName() == "QSQLITE")
    {
        QSqlQuery q(db);
        if (!q.exec("PRAGMA foreign_keys = ON"))
            err = db.lastError();
    }

    return err;
}


/*! Checks if the database file exists. If not, check the path exists and
 *  create the path if necessary.
 */
bool PrimaryDb::verifyDbAndPathExist(const QString &connectionName) const
{
    if (QFile::exists(m_dbPathAndName))
        return true;
    return checkPath(m_dbPath);
}



#if 0
bool primarydb::openProfile()
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

QSqlError primarydb::saveProfile(const QString &name,
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

QSqlError primarydb::eraseProfile(const QString& name)
{
    QSqlQuery query(QSqlDatabase::database(m_dbConnectionName));

    if (!query.prepare(QLatin1String("delete from Profile where name = :name")))
        return query.lastError();
    query.bindValue(":name", name);
    query.exec();

    return QSqlError();
}

int primarydb::readProfile(const QString &name,
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


#endif
