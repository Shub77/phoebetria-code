#ifndef PHOEBETRIA_DB_PRIMARY_SCHEMA_H
#define PHOEBETRIA_DB_PRIMARY_SCHEMA_H

#include <stdlib.h>

class QStringList;      // Fwd decl
class QString;          // Fwd decl

class PrimaryDbSchema
{
public:

    typedef struct TableDef
    {
        const char* name;
        const char* ddl;
    } TableDef;

    PrimaryDbSchema();

    static bool verify(const QString* dbFilename,
                       QStringList *missingTablesList = NULL);

    static bool create(const QString* newDbFilename,
                       const QString* oldDbFilename = NULL);

protected:

    static bool checkTables(const QString &dbFilename,
                            QStringList *missingTablesList);

    static bool schemaVersionOk(void);

    static bool createSchema(void);

    static bool createTables(void);

    static bool migrateData(const QString* newDbFilename,
                            const QString* oldDbFilename);

    static bool insertDefaultData(void);

private:

    static int m_schemaVersion;
};

#endif // PHOEBETRIA_DB_PRIMARY_SCHEMA_H
