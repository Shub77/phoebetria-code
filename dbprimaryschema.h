#ifndef PHOEBETRIA_DB_PRIMARY_SCHEMA_H
#define PHOEBETRIA_DB_PRIMARY_SCHEMA_H

class QStringList;      // Fwd decl

class PrimaryDbSchema
{
public:

    typedef struct TableDef
    {

        const char* name;
        const char* ddl;
    } TableDef;


    PrimaryDbSchema();

    static bool checkTables(QStringList* missingTablesList);

protected:

    bool createSchema(void);
    bool createTables(void);
    bool insertDefaultData(void);
};

#endif // PHOEBETRIA_DB_PRIMARY_SCHEMA_H
