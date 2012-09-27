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

#include "maindb.h"

#include <QSettings>

#include "dbmanager.h"
#include "maindb_schema.h"
#include "utils.h"
#include "fanprofiles.h"

#include "utils.h"

// TODO: Move this to "preferences"
static const bool g_deleteDatabaseOnAnyCreateError = true;

MainDb::MainDb()
{
}

void MainDb::init(void)
{
    QString dbConnName = dbConnectionName();
    if (!QSqlDatabase::contains(dbConnName))
        connect(dbConnName);
}

QStringList MainDb::profileNames()
{
    QStringList profileList;
    QSqlQuery query(QSqlDatabase::database(dbConnectionName()));

    if (!query.exec(QLatin1String("select name from Profile")))
    {
        m_lastSqlError = query.lastError();
        return profileList;   // return empty list
    }

    while (query.next())
        profileList << query.value(0).toString();

    return profileList;
}

bool MainDb::writeProfile(const QString& name,
                          const FanControllerProfile& profile)
{
    QSqlDatabase db = QSqlDatabase::database(dbConnectionName());

    bool ok = true;

    db.transaction();

    int p_id = writeProfileCommonSettings(
                name,
                profile.isAuto(),
                profile.isCelcius(),
                profile.isAudibleAlarm(),
                false       // FIXME: TODO: set to real val when s/ware auto done
                );

    if (p_id == -1)
    {
        db.rollback();
        return false;
    }

    for (int i = 0; i < FC_MAX_CHANNELS; i++)
    {
        BasicChannelData bcd = profile.getChannelSettings(i);

        ok = writeProfileChannelSettings(
                    p_id,
                    i,
                    bcd.speed,
                    bcd.alarmTemp
                    );

        if (!ok) break;
    }

    if (!ok)
        db.rollback();
    else
        db.commit();

    return ok;
}

// Returns the primary key of the updated or inserted record on success
// -1 on failure
int MainDb::writeProfileCommonSettings(const QString& profileName,
                                       bool isAuto,
                                       bool isCelcius,
                                       bool isAudibleAlarm,
                                       bool isSoftwareAuto)
{
    QSqlQuery qry(QSqlDatabase::database(dbConnectionName()));

    /* Why am I updating/inserting like this when C++ is at disposal?
       Because it's fun! Because I feel like it? Because I can?
       I actually can't remember why. */

    bool ok = qry.prepare("update Profile"
          " set isAuto = :isAuto, isCelcius = :isCelcius,"
          " isAudibleAlarm = :isAudibleAlarm, isSoftwareAuto = :isSwareAuto"
          " where exists (select 1 from Profile where name = :pName)"
          " and name = :pName2;"
          );
    qry.bindValue(":isAuto",            isAuto);
    qry.bindValue(":isCelcius",         isCelcius);
    qry.bindValue(":isAudibleAlarm",    isAudibleAlarm);
    qry.bindValue(":isSwareAuto",       isSoftwareAuto);
    qry.bindValue(":pName",             profileName);
    qry.bindValue(":pName2",            profileName);

    if (!ok) { m_lastSqlError = qry.lastError(); return -1; }

    ok = qry.exec();

    if (!ok) { m_lastSqlError = qry.lastError(); return -1; }


    ok = qry.prepare("insert into Profile"
          " (name, isAuto, isCelcius, isAudibleAlarm, isSoftwareAuto)"
          " select :pName, :isAuto, :isCelcius, :isAudibleAlarm, :isSwareAuto"
          " where not exists (select 1 from Profile where name = :pName2)"
          );
    qry.bindValue(":pName",             profileName);
    qry.bindValue(":isAuto",            isAuto);
    qry.bindValue(":isCelcius",         isCelcius);
    qry.bindValue(":isAudibleAlarm",    isAudibleAlarm);
    qry.bindValue(":isSwareAuto",       isSoftwareAuto);
    qry.bindValue(":pName2",            profileName);

    if (!ok) { m_lastSqlError = qry.lastError(); return -1; }

    ok = qry.exec();

    if (!ok) { m_lastSqlError = qry.lastError(); return -1; }

    return getProfileId(profileName);
}

int MainDb::getProfileId(const QString& name)
{
    QSqlQuery qry(QSqlDatabase::database(dbConnectionName()));

    bool ok = qry.prepare("select p_id from profile where name = :pName");
    qry.bindValue(":pName", name);

    if (!ok) { m_lastSqlError = qry.lastError(); return -1; }

    ok = qry.exec();

    if (!ok) { m_lastSqlError = qry.lastError(); return -1; }

    qry.first();
    return qry.value(0).toInt();
}


// ProfileId is the primary key (p_id) for the profile
bool MainDb::writeProfileChannelSettings(int profileId,
                                         int channel,
                                         int rpm,
                                         int alarmTempInF)
{
    QSqlQuery qry(QSqlDatabase::database(dbConnectionName()));

    bool ok = qry.prepare("delete from ChannelSetting"
                          " where p_id = :profileId and channel = :channel");
    qry.bindValue(":profileId", profileId);
    qry.bindValue(":channel", channel);

    if (!ok) { m_lastSqlError = qry.lastError(); return false; }

    ok = qry.exec();

    if (!ok) { m_lastSqlError = qry.lastError(); return false; }

    qry.prepare("insert into ChannelSetting"
                " values (:profileId, :channel, :manualRpm, :alarmTempF)");
    qry.bindValue(":profileId",  profileId);
    qry.bindValue(":channel",    channel);
    qry.bindValue(":manualRpm",  rpm);
    qry.bindValue(":alarmTempF", alarmTempInF);

    if (!ok) { m_lastSqlError = qry.lastError(); return false; }

    ok = qry.exec();

    if (!ok) { m_lastSqlError = qry.lastError(); return false; }

    return true;
}


QSqlError MainDb::connect(const QString& connectionName)
{
    QString dbPathAndName
            = DatabaseManager::dbFilenameWithPath(DatabaseManager::PrimaryDb);

    if (!verifyDbAndPathExist())
    {
        QString customErrorMsg = QObject::tr(
                "Error initialising database."
                " Path does not exist"
                " and path could be created: %1")
                    .arg(dbPathAndName);

        return QSqlError(customErrorMsg);
    }

    QSqlError err;

    if (!fileExists(dbPathAndName))
        err = createNewDb(connectionName);
    else
        err = checkExistingDb(connectionName);

    if (err.isValid()) return err;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setDatabaseName(dbPathAndName);

    if (!db.open())
        return db.lastError();

    err = enableFkSupport(connectionName);

    return err;
}

QSqlError MainDb::createNewDb(const QString &connectionName)
{
    QString dbPathAndName
            = DatabaseManager::dbFilenameWithPath(DatabaseManager::PrimaryDb);

    QSqlError err = MainDbSchema::create(&dbPathAndName);
    if (err.isValid() && g_deleteDatabaseOnAnyCreateError)
    {
        if (!QFile::remove(dbPathAndName))
            qDebug() << "Failed to delete db file";
    }
    return err;
}

QSqlError MainDb::checkExistingDb(const QString &connectionName)
{
    QSqlError err;

    QString dbPathAndName
            = DatabaseManager::dbFilenameWithPath(DatabaseManager::PrimaryDb);

    if (!MainDbSchema::verify(&dbPathAndName))
        err = recreateDb(dbConnectionName());

    return err;
}

QSqlError MainDb::recreateDb(const QString &connectionName)
{
    QSqlError err;

    QString dbPathAndName
            = DatabaseManager::dbFilenameWithPath(DatabaseManager::PrimaryDb);

    QString oldDbName(dbPathAndName);
    oldDbName += ".orig";
    if (fileExists(oldDbName))
    {
        if (!QFile::remove(oldDbName))
            return QSqlError(QObject::tr("Failed to delete old db"));
    }
    QFile::rename(dbPathAndName, oldDbName);

    err = MainDbSchema::create(&dbPathAndName, &oldDbName);

    if (!QFile::remove(oldDbName))
        qDebug() << "Failed to delete old db";

    if (err.isValid() && g_deleteDatabaseOnAnyCreateError)
    {
        if (!QFile::remove(dbPathAndName))
            qDebug() << "Failed to remove partially created db";
    }

    return err;
}

// Enable foreign key support
// pre: db is open
QSqlError MainDb::enableFkSupport(const QString &connectionName)
{
    QSqlError err;
    QSqlDatabase db = QSqlDatabase::database(dbConnectionName());

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
bool MainDb::verifyDbAndPathExist(void)
{
    QString dbPathAndName
            = DatabaseManager::dbFilenameWithPath(DatabaseManager::PrimaryDb);

    if (QFile::exists(dbPathAndName))
        return true;
    return checkPath(DatabaseManager::pathToDatabases());
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
