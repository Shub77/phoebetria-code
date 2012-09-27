#ifndef PHOEBETRIA_DB_PRIMARY_SCHEMA_H
#define PHOEBETRIA_DB_PRIMARY_SCHEMA_H

#include <stdlib.h>

class QStringList;      // Fwd decl
class QString;          // Fwd decl
class QSqlError;

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

    static QSqlError create(const QString* newDbFilename,
                            const QString* oldDbFilename = NULL);

protected:

    static bool checkTables(const QString &dbFilename,
                            QStringList *missingTablesList);

    static bool schemaVersionOk(void);

    static QSqlError createSchema(void);

    static QSqlError createTables(void);

    static QSqlError migrateData(const QString* newDbFilename,
                                 const QString* oldDbFilename);

    static QSqlError insertDefaultData(void);

private:

    static int m_schemaVersion;
};

#endif // PHOEBETRIA_DB_PRIMARY_SCHEMA_H
