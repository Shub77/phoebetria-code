#ifndef DBFANPROFILESCHEMA_H
#define DBFANPROFILESCHEMA_H

class DbFanProfileSchema
{
public:

    typedef struct TableDef
    {

        const char* m_name;
        const char* m_ddl;
    } TableDef;


    DbFanProfileSchema();

protected:

    bool createSchema(void);
    bool insertDefaultData(void);
};

#endif // DBFANPROFILESCHEMA_H
