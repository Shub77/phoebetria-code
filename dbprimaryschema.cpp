#include "dbprimaryschema.h"

#include <stdlib.h>
#include <QStringList>
#include <QSqlDatabase>

#include "database.h"

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
        "DatabaseInfo",
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
 *
 *  This functions provides a basic check of the database. It only checks that
 *  the required tables are present; no other checks are made.
 *
 *  If the required tables are present in the database, true is returned. If
 *  false is returned and \e missingTablesList != NULL then missingTablesList
 *  will be populated with the names of the tables that are missing.
 *
 *  \note If \e missingTablesList is supplied (i.e. !NULL) it is cleared upon
 *        calling this function.
 *
 *  \post If \e missingTablesList != NULL and the return value == true, then
 *        missingTablesList->size() == 0
 */
bool PrimaryDbSchema::checkTables(QStringList* missingTablesList)
{
    bool tableMissing = false;
    QSqlDatabase db = QSqlDatabase::database(Database::connectionName());

    QStringList db_tables = db.tables();

    if (missingTablesList) missingTablesList->clear();

    for (unsigned i = 0 ; i < PHOEBETRIA_DB_SCHEMA_TABLE_COUNT; i++)
    {
        if (db_tables.indexOf(schema[i].name) == -1)
        {
            tableMissing = true;
            if (missingTablesList)
                missingTablesList->append(schema[i].name);
        }
    }

    return tableMissing;
}
