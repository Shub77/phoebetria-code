#include "dbprimaryschema.h"

#include <stdlib.h>
#include <QStringList>
#include <QSqlDatabase>

#include "database.h"

#include "utils.h"

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
#define PHOEBETRIA_DB_SCHEMA_TABLE_COUNT \
    ( sizeof schema / sizeof schema[0] )


PrimaryDbSchema::PrimaryDbSchema()
{
}


/*! Basic schema check: check that the correct tables are present.

    This functions provides a basic check of the database. It only checks that
    the required tables are present; no other checks are made.

    If the required tables are present in the database, true is returned. If
    false is returned and \e missingTablesList != NULL then missingTablesList
    will be populated with the names of the tables that are missing.

    \note If \e missingTablesList is supplied (i.e. !NULL) it is cleared upon
         calling this function.

    \post If \e missingTablesList != NULL and the return value == true, then
         missingTablesList->size() == 0
*/
bool PrimaryDbSchema::checkTables(QStringList* missingTablesList)
{
    bool ok = true;
    QSqlDatabase db = QSqlDatabase::database(Database::connectionName());

    QStringList db_tables = db.tables();

    if (missingTablesList) missingTablesList->clear();

    for (unsigned i = 0 ; i < PHOEBETRIA_DB_SCHEMA_TABLE_COUNT; i++)
    {
        if (db_tables.indexOf(schema[i].name) == -1)
        {
            ok = false;
            if (missingTablesList)
                missingTablesList->append(schema[i].name);
        }
    }

    return ok;
}


/*! Create the schema. Any existing tables are deleted (dropped).

    Creates the tables and inserts default data. If an error occurs, false
    will be returned and the current state of the database will remain
    unchanged.

    \note If tables already exist, they will be deleted (and their data lost)
          and the table re-created.
 */
bool PrimaryDbSchema::createSchema(void)
{
    PHOEBETRIA_STUB_FUNCTION
}

/*! Create the tables for the schema.

    Creates all the tables for the database. Note that this function does not
    delete (drop) a table if it's already present. Because of this, if the
    table is already present but "incorrect" (e.g. wrong columns etc) the
    database will have the correct tables but remain incorrect/corrupted.
    Therefore in many cases it may be more appropriate that createSchema() is
    used rather than calling this function directly.

*/
bool PrimaryDbSchema::createTables(void)
{
    PHOEBETRIA_STUB_FUNCTION
}


