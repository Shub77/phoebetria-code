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

#include "dbmanager.h"

#include <QtSql>
#include <QSqlQuery>
#include <QString>
#include <QSettings>
#include <QDebug>
#include <QFile>

#include "maindb.h"
#include "preferences.h"
#include "utils.h"

QString DatabaseManager::m_dbPath = Preferences::filepath();


/* These *MUST* be in the same order as PhoebetriaDbMgr::DatabaseId
 */
const DatabaseManager::DbDetails DatabaseManager::m_dbConnectionDetails[]  =
{
    { QString("primaryDb"), "phoebetria.sqlite" },
    { QString("logDb"), "sessionlog.sqlite" }
};


DatabaseManager::DatabaseManager()
    : QSqlDatabase()
{
}

DatabaseManager::DatabaseManager(const QSqlDatabase& other)
    : QSqlDatabase(other)
{
}

void DatabaseManager::initAllDatabases(void)
{
    MainDb::init();
}

QString DatabaseManager::prependDbPath(const QString& filename)
{
    QString result(m_dbPath);
    result.append(QDir::separator());
    result.append(filename);
    return result;
}



QStringList DatabaseManager::tables(const QString &dbConnectionName)
{
    return QSqlDatabase::database(dbConnectionName).tables();
}


QStringList DatabaseManager::tableFields(const QString &dbConnectionName,
                                         const QString& tablename)
{
    QSqlRecord rec(QSqlDatabase::database(dbConnectionName).record(tablename));

    QStringList fields;

    for (int i = 0; i < rec.count(); ++i)
        fields.append(rec.fieldName(i));

    return fields;
}





