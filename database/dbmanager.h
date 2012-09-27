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

#ifndef PHOEBETRIA_DATABASE_H
#define PHOEBETRIA_DATABASE_H

#include <QStringList>
#include <QtSql>

class DatabaseManager : public QSqlDatabase
{

public:

    typedef enum
    {
        PrimaryDb,
        LoggingDb
    } DatabaseId;

    typedef struct
    {
        const QString connName;
        const char* filename;
    } DbDetails;

    DatabaseManager();
    DatabaseManager(const QSqlDatabase& other);

    static void initAllDatabases(void);

    inline static const QString *dbConnectionName(DatabaseId dbId);
    inline static const QString *primaryDbConnName(void);

    static QStringList tables(const QString& dbConnectionName);

    static QStringList tableFields(const QString &dbConnectionName,
                                   const QString& tablename);

protected:

    QString prependDbPath(const QString& filename) const;

private:

    static QString m_dbPath;

    static const DbDetails m_dbConnectionDetails[];
};



const QString* DatabaseManager::dbConnectionName(DatabaseId dbId)
{
    return &m_dbConnectionDetails[dbId].connName;
}

const QString* DatabaseManager::primaryDbConnName(void)
{
    return dbConnectionName(PrimaryDb);
}


#endif // PHOEBETRIA_DATABASE_H
