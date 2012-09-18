#include "dbfanprofileschema.h"

#include <stdlib.h>

static DbFanProfileSchema::TableDef schema[] =
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



DbFanProfileSchema::DbFanProfileSchema()
{
}
