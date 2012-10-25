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
#include <QMessageBox>

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

QString MainDb::profileDescription(const QString& profileName)
{
    QSqlQuery qry(QSqlDatabase::database(dbConnectionName()));

    bool ok = qry.prepare("select description"
                          " from Profile"
                          " where name = :pName;");
    qry.bindValue(":pName", profileName);

    if (!ok) { m_lastSqlError = qry.lastError(); return QString(); }

    ok = qry.exec();

    if (!ok) { m_lastSqlError = qry.lastError(); return QString(); }

    return qry.first() ? qry.value(0).toString() : QString();
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
                profile.isSoftwareAuto()
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

        if (profile.isSoftwareAuto())
        {
            /* TODO: Write ramp */
            //if (!ok) break;
        }
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
                  "     description,"
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
    profile.m_description =      qry.value(0).toString();
    profile.m_isAuto =           qry.value(1).isNull() ? true : qry.value(1).toBool();
    profile.m_isCelcius =        qry.value(2).isNull() ? true : qry.value(2).toBool();
    profile.m_isAudibleAlarm =   qry.value(3).isNull() ? true : qry.value(3).toBool();
    profile.m_isSoftwareAuto =   qry.value(4).isNull() ? false : qry.value(4).toBool();

    for ( ; qry.isValid(); qry.next())
    {
        int channel = qry.value(5).isNull() ? -1 : qry.value(5).toInt();

        if (channel < 0 || channel > FC_MAX_CHANNELS-1)
        {
            qDebug() << "Invalid channel read from profile:" << channel;
            continue;
        }

        int manualRpm       = qry.value(6).toInt();
        int alarmTempF      = qry.value(7).toInt();

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
    int rowsDeleted = qry.numRowsAffected();
    return rowsDeleted == -1 || rowsDeleted == 0 ? false : true;
}

// returns -1 if no match found
int MainDb::getProfileId(const QString& name)
{
    QSqlQuery qry(QSqlDatabase::database(dbConnectionName()));

    bool ok = qry.prepare("select p_id from profile where name = :pName");
    qry.bindValue(":pName", name);

    if (!ok) { m_lastSqlError = qry.lastError(); return -1; }

    ok = qry.exec();

    if (!ok) { m_lastSqlError = qry.lastError(); return -1; }

    // return the p_id if qry has results, otherwise -1
    return qry.first() ? qry.value(0).toInt() : -1;
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

    bool newDatabase = false;
    if (!fileExists(dbPathAndName))
    {
        err = createNewDb(connectionName);
        if (err.type() == QSqlError::NoError)
        {
            newDatabase = true;
        }
    }
    else
        err = checkExistingDb(connectionName);

    if (err.isValid()) return err;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setDatabaseName(dbPathAndName);

    if (!db.open())
        return db.lastError();

    err = enableFkSupport(connectionName);

    if (newDatabase && err.type() == QSqlError::NoError)
        importOldStyleProfiles();

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

int MainDb::importOldStyleProfiles(void)
{
    QSettings settings(QSettings::IniFormat,
                       QSettings::UserScope,
                       "Phoebetria",
                       "Phoebetria");

    QFileInfo path = QFileInfo(settings.fileName()).path() + "/Presets/";

    QDir dir(path.absoluteFilePath());

    if (!dir.exists()) return 0;

    QMessageBox::information(
                NULL,
                QObject::tr("Importing old-style (.ini) profiles."),
                QObject::tr("Phoebetria has changed the way it stores fan profiles.\n"
                            "Your existing profiles will now be imported."),
                QMessageBox::Ok
                );


    return FanControllerProfile::importFromIni(dir);

}
