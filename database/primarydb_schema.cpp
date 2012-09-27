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

#include "primarydb_schema.h"

#include <QStringList>
#include <QSqlDatabase>

#include "dbmanager.h"

#include "utils.h"


static const char* newDbConnName = "pdbs_tmp_newPrimaryDb";
static const char* tmpDbConnName = "pdsb_tmp_pdb";


int PrimaryDbSchema::m_schemaVersion = 1;

static PrimaryDbSchema::TableDef schema[] =
{
    {
        "DatabaseInfo",
        "CREATE TABLE DatabaseInfo ("
        "     name    VARCHAR(32)     PRIMARY KEY"
        "    ,value   TEXT"
        ");"
    },

    {
        "Profile",
        "CREATE TABLE Profile("
        "     p_id           INTEGER        PRIMARY KEY"
        "    ,name           VARCHAR(32)    UNIQUE"
        "    ,isAuto         BOOLEAN        DEFAULT '1'"
        "    ,isCelcius      BOOLEAN        DEFAULT '1'"
        "    ,isAudibleAlarm BOOLEAN        DEFAULT '1'"
        "    ,isSoftwareAuto BOOLEAN        DEFAULT '0'"
        ");"
    },

    {
        "ChannelSetting",
        "CREATE TABLE ChannelSetting ("
        "     p_id       INTEGER"
        "    ,channel    INTEGER"
        "    ,manualRpm  INTEGER"
        "    ,alarmTempF INTEGER"
        "    ,FOREIGN KEY ( p_id ) REFERENCES Profile ( p_id )"
        "         ON DELETE CASCADE DEFERRABLE INITIALLY DEFERRED"
        ");"
    },

    {
        "ChannelName",
        "CREATE TABLE ChannelName ("
        "    channel INTEGER"
        "    ,name    VARCHAR( 32 )"
        "    ,PRIMARY KEY ( channel, name )"
        ");"
    }
};
#define PHOEBETRIA_DB_SCHEMA_TABLE_COUNT ( sizeof schema / sizeof schema[0] )


static const char* defaultDataSql[] =
{
        // Note: schema version is inserted by insertDefaultData()
    "INSERT INTO [Profile] ([p_id], [name], [isAuto], [isCelcius], [isAudibleAlarm], [isSoftwareAuto]) VALUES (1, '__PHOEBETRIA_DEFAULT', 1, 1, 1, 0)",
    "INSERT INTO ChannelSetting (p_id, channel, manualRpm, alarmTempF) VALUES (1, 0, 50000, 194)",
    "INSERT INTO ChannelSetting (p_id, channel, manualRpm, alarmTempF) VALUES (1, 1, 50000, 194)",
    "INSERT INTO ChannelSetting (p_id, channel, manualRpm, alarmTempF) VALUES (1, 2, 50000, 194)",
    "INSERT INTO ChannelSetting (p_id, channel, manualRpm, alarmTempF) VALUES (1, 3, 50000, 194)",
    "INSERT INTO ChannelSetting (p_id, channel, manualRpm, alarmTempF) VALUES (1, 4, 50000, 194)"
};
#define PHOEBETRIA_DB_DEFAULT_DATA_COUNT \
    ( sizeof defaultDataSql / sizeof defaultDataSql[0] )


PrimaryDbSchema::PrimaryDbSchema()
{
}

/*! Verify the database

    Returns true if the correct tables are present and the schema is the
    correct version.

    \pre The database referred to by \e dbFilename exists and is a valid
         database.
*/
bool PrimaryDbSchema::verify(const QString* dbFilename,
                             QStringList* missingTablesList)
{
    return checkTables(*dbFilename, missingTablesList) && schemaVersionOk();
}


/*! Creates a new database with the default tables and data.

    Creates a new database with the filename \e dbFilename.
    If \e oldDbFilename != NULL, then migrate the data from the old database
    to the newly created database.
*/
QSqlError PrimaryDbSchema::create(const QString* newDbFilename,
                                  const QString* oldDbFilename)
{
    QSqlError err;

    QSqlDatabase newDb;
    newDb = QSqlDatabase::addDatabase("QSQLITE", newDbConnName);
    newDb.setDatabaseName(*newDbFilename);
    if (!newDb.open())
        return newDb.lastError();

    if ( (err = createTables()).isValid() ) goto abort;

    if ( (err = migrateData(newDbFilename, oldDbFilename)).isValid()) goto abort;

    err = insertDefaultData();

abort:
    newDb.close();

    return err;
}


/*! Basic schema check: check that the correct tables are present.

    This functions provides a \b basic check of the database. It only checks
    that the required tables are present; no other checks are made.

    If the required tables are present in the database, true is returned. If
    false is returned and \e missingTablesList != NULL then missingTablesList
    will be populated with the names of the tables that are missing.

    \note If \e missingTablesList is supplied (i.e. !NULL) it is cleared upon
         calling this function.

    \post If \e missingTablesList != NULL and the return value == true, then
         missingTablesList->size() == 0
*/
bool PrimaryDbSchema::checkTables(const QString& dbFilename,
                                  QStringList* missingTablesList)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", tmpDbConnName);
    db.setDatabaseName(dbFilename);
    if (!db.open())
        return false;

    bool ok = true;

    QStringList db_tables = db.tables();

    if (missingTablesList) missingTablesList->clear();

    for (unsigned i = 0 ; i < PHOEBETRIA_DB_SCHEMA_TABLE_COUNT; i++)
    {
        if (!db_tables.contains(schema[i].name))
        {
            ok = false;
            if (missingTablesList)
                missingTablesList->append(schema[i].name);
        }
    }

    db.close();

    return ok;
}

/*! Check if the database's schema version matches the internal version.

    \pre A connection named \e newDbConnectionName (static global in this file)
         has been established.
*/
bool PrimaryDbSchema::schemaVersionOk(void)
{
    PHOEBETRIA_STUB_FUNCTION
    return true; // TODO IMPLEMENT
}


/*! Create the schema.

    Creates the tables and inserts default data.
 */
QSqlError PrimaryDbSchema::createSchema(void)
{
    QSqlError err;

    if ( (err = createTables()).isValid() ) return err;

    return insertDefaultData();
}


/*! Create the tables for the schema.

    Creates all the tables for the database. Note that this function does not
    delete (drop) a table if it's already present.

    \pre A connection named \e newDbConnectionName (static global in this file)
         has been established.
*/
QSqlError PrimaryDbSchema::createTables(void)
{
    QSqlError err;

    QSqlDatabase db = QSqlDatabase::database(newDbConnName);
    QStringList db_tables = db.tables();

    for (unsigned i = 0 ; i < PHOEBETRIA_DB_SCHEMA_TABLE_COUNT; i++)
    {
        // If the table doesn't exist, create it
        if (!db_tables.contains(schema[i].name))
        {
            QSqlQuery qry(db);

            if (!qry.exec(schema[i].ddl))
            {
                err = db.lastError();
                break;
            }
        }
    }

    return err;
}

/*! Migrate data from the old database to the new database.

    \pre    newDbFilename != NULL, oldDbFilename != NULL
*/
QSqlError PrimaryDbSchema::migrateData(const QString* newDbFilename,
                                       const QString* oldDbFilename)
{
    /* This is the first version of the schema, so there is nothing to
     * do here
     */

    (void)newDbFilename;    // Unused
    (void)oldDbFilename;    // Unused

    return QSqlError(); // no error
}

/*!
    \pre A connection named \e newDbConnectionName (static global in this file)
         has been established.
*/
QSqlError PrimaryDbSchema::insertDefaultData(void)
{
    QSqlError err;

    QSqlDatabase db = QSqlDatabase::database(newDbConnName);
    QSqlQuery qry(db);

    db.transaction();

    for (unsigned i = 0 ; i < PHOEBETRIA_DB_DEFAULT_DATA_COUNT; i++)
    {
        if (!qry.exec(defaultDataSql[i]))
        {
            err = db.lastError();
            break;
        }
    }

    if (!err.isValid())
    {
        qry.prepare("INSERT INTO DatabaseInfo (name, value)"
                    " VALUES (:keyname, :version)");
        qry.bindValue(":keyname", "schemaVersion");
        qry.bindValue(":version", m_schemaVersion);
        if (!qry.exec())
            err = db.lastError();
    }


    if (!err.isValid())
        db.commit();
    else
    {
        db.rollback();
        qDebug() << db.lastError();
    }
    return err;
}
