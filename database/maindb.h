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

#ifndef PHOEBETRIA_PRIMARYDB_H
#define PHOEBETRIA_PRIMARYDB_H

#include <QStringList>
#include <QtSql>
#include "dbmanager.h"

class MainDb
{
public:
    MainDb();

    inline static QString dbConnectionName(void);

    static void init(void);

    static QStringList profileNames();

protected:
    static QSqlError connect(const QString &connectionName);

    static QSqlError createNewDb(const QString &connectionName);
    static QSqlError checkExistingDb(const QString &connectionName);
    static QSqlError recreateDb(const QString &connectionName);
    static QSqlError enableFkSupport(const QString &connectionName);

    static bool verifyDbAndPathExist(void);

    bool openProfile();

};


QString MainDb::dbConnectionName(void)
{
    return QString(*DatabaseManager::primaryDbConnName());
}


#endif // PHOEBETRIA_PRIMARYDB_H
