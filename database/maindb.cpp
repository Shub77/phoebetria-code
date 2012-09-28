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
       I actually can't remember why.

       TODO: Implement an exists() function; probably as an abstract base
             class that this class can be a subclass of
    */

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

bool MainDb::readProfile(const QString&name, FanControllerProfile& profile)
{
    QSqlQuery qry(QSqlDatabase::database(dbConnectionName()));

    /* Could probably use QSqlQuery::bind(), but &val in that function is
     * const???
     */
    bool ok = qry.prepare(
                  "select "
                  "     isAuto,"
                  "     isCelcius,"
                  "     isAudibleAlarm,"
                  "     isSoftwareAuto,"
                  "     channel,"
                  "     manualRpm,"
                  "     alarmTempF"
                  " from Profile"
                  " join ChannelSetting on ChannelSetting.p_id = Profile.p_id"
                " where Profile.name = :pName"
                );

    qry.bindValue(":pName", name);

    if (!ok) { m_lastSqlError = qry.lastError(); return false; }

    ok = qry.exec();
    if (!ok) { m_lastSqlError = qry.lastError(); return false; }

    if (!qry.first())
    {
        // Empty result
        m_lastSqlError = QSqlError();
        return false;
    }

    // Get the common settings from the first result
    profile.m_name =             name;
    profile.m_isAuto =           qry.value(0).isNull() ? true : qry.value(0).toBool();
    profile.m_isCelcius =        qry.value(1).isNull() ? true : qry.value(1).toBool();;
    profile.m_isAudibleAlarm =   qry.value(2).isNull() ? true : qry.value(2).toBool();;

    for ( ; qry.isValid(); qry.next())
    {
        int channel = qry.value(4).isNull() ? -1 : qry.value(4).toInt();

        if (channel < 0 || channel > FC_MAX_CHANNELS-1)
        {
            qDebug() << "Invalid channel read from profile:" << channel;
            continue;
        }

        int manualRpm       = qry.value(5).toInt();
        int alarmTempF      = qry.value(6).toInt();

        profile.m_channelSettings[channel].speed        = manualRpm;
        profile.m_channelSettings[channel].alarmTemp    = alarmTempF;
    }

    return true;
}


bool MainDb::deleteProfile(const QString& profileName)
{
    QSqlQuery qry(QSqlDatabase::database(dbConnectionName()));

    bool ok = qry.prepare("delete from Profile"
                          " where name = :profileName");
    qry.bindValue(":profileName", profileName);

    if (!ok) { m_lastSqlError = qry.lastError(); return false; }

    QSqlDatabase db = QSqlDatabase::database(dbConnectionName());
    db.transaction();
    ok = qry.exec();

    if (!ok)
    {
        db.rollback();
        m_lastSqlError = qry.lastError();
        return false;
    }

    db.commit();
    return true;
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
