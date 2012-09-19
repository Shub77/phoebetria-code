#include "dbprimaryschema.h"

#include <QStringList>
#include <QSqlDatabase>

#include "database.h"

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
        "     p_id           INTEGER        PRIMARY KEY AUTOINCREMENT"
        "    ,name           VARCHAR(32)"
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
    }
};
#define PHOEBETRIA_DB_SCHEMA_TABLE_COUNT ( sizeof schema / sizeof schema[0] )


static PrimaryDbSchema::DefaultData defaultDataSql[] =
{

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
bool PrimaryDbSchema::create(const QString* newDbFilename,
                             const QString* oldDbFilename)
{
    QSqlDatabase newDb;
    newDb = QSqlDatabase::addDatabase("QSQLITE", newDbConnName);
    newDb.setDatabaseName(*newDbFilename);
    if (!newDb.open())
        return false;

    createTables();
    migrateData(newDbFilename, oldDbFilename);
    insertDefaultData();

    newDb.close();

    return true;
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
bool PrimaryDbSchema::createSchema(void)
{
    if (!createTables()) return false;

    return insertDefaultData();
}


/*! Create the tables for the schema.

    Creates all the tables for the database. Note that this function does not
    delete (drop) a table if it's already present.

    \pre A connection named \e newDbConnectionName (static global in this file)
         has been established.
*/
bool PrimaryDbSchema::createTables(void)
{

    bool success = true;

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
                success = false;
                break;
            }
        }
    }

    return success;
}

/*! Migrate data from the old database to the new database.

    \pre    newDbFilename != NULL, oldDbFilename != NULL
*/
bool PrimaryDbSchema::migrateData(const QString* newDbFilename,
                                  const QString* oldDbFilename)
{
    PHOEBETRIA_STUB_FUNCTION
    return true;       // TODO: Implement
}


bool PrimaryDbSchema::insertDefaultData(void)
{
     PHOEBETRIA_STUB_FUNCTION
     return true;       // TODO: Implement
}
