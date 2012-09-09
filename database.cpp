#include <QtSql>
#include <QString>
#include <QSettings>
#include <QDebug>
#include "database.h"


QString Database::m_dbFilename = "phoebetria.sqlite";

QString Database::m_dbConnectionName = "phoebetriaDb";


Database::Database()
{
    initCommon();
}

void Database::initCommon(void)
{
    if (!QSqlDatabase::contains(m_dbConnectionName))
    {
        openDb();
    }
}

// Check the settings path. If it doesn't exist, create it.
bool Database::checkSettingsPath(const QString& path) const
{
    QDir dir(path);
    if (!dir.exists())
    {
        if (!dir.mkpath(path))
            return false;
    }
    return dir.exists();
}


QString Database::databaseNameAndPath(void) const
{
    return m_dbPathAndName;
}

QSqlError Database::openDb()
{
    QString dbPath;


    QSettings settings(QSettings::IniFormat,
                       QSettings::UserScope,
                       "Phoebetria",
                       "Phoebetria");
    dbPath = QFileInfo(settings.fileName()).path();

    // If the database doesn't exist try and create it
    if( !QFile::exists(m_dbPathAndName))
    {
        // Filename doesn't exist? If not, check that at least the path does
        if (!checkSettingsPath(dbPath))
        {
            return QSqlError ("Error initialising database. Path does not exist"
                              " and could be created.");
        }
    }

    // At this point at least the path exists

    m_dbPathAndName = dbPath;
    m_dbPathAndName.append(QDir::separator()).append("Phoebetria.sqlite");
    m_dbPathAndName = QDir::toNativeSeparators(m_dbPathAndName);

    db = QSqlDatabase::addDatabase("QSQLITE", m_dbConnectionName);
    db.setDatabaseName(m_dbPathAndName);

    if (!db.open())
        return db.lastError();

    // Check default schema

    QStringList tables = db.tables();
    if (!tables.contains("Profile", Qt::CaseInsensitive))
    {
        QSqlQuery q(db);
        if (!q.exec(QLatin1String("create table Profile(name varchar, channel integer, setting varchar, value integer, primary key (name, channel, setting))")))
        {
            qDebug() << "****" << q.lastError();
            return q.lastError();
        }
    }

    return QSqlError();
}


QSqlError Database::saveProfile(const QString name, const QString setting, int channel, int value)
{
    QSqlQuery query(QSqlDatabase::database(m_dbConnectionName));

    if (!query.prepare(QLatin1String("insert or replace into Profile(name, setting, channel, value) values(:name, :setting, :channel, :value)")))
        return query.lastError();
    query.bindValue(":name", name);
    query.bindValue(":setting", setting);
    query.bindValue(":channel", channel);
    query.bindValue(":value", value);
    query.exec();

    return QSqlError();
}

int Database::readProfile(const QString name, const QString setting, int channel)
{
    int m_value;

    QSqlQuery query(QSqlDatabase::database(m_dbConnectionName));

    query.prepare(QLatin1String("select value from Profile where name = :name and setting = :setting and channel = :channel"));
    query.bindValue(":name", name, QSql::Out);
    query.bindValue(":setting", setting, QSql::Out);
    query.bindValue(":channel", channel, QSql::Out);

    m_value = query.exec();

    return m_value;
}

QStringList Database::readProfileNames()
{
    //qDebug() << m_dbConnectionName;

    QStringList m_ProfileList;
    QSqlQuery query(QSqlDatabase::database(m_dbConnectionName));

    //qDebug() << db.connectionName();
    query.exec(QLatin1String("select distinct name from Profile"));

    while( query.next() )
    {
        m_ProfileList << query.value(0).toString();
    }

    if (m_ProfileList.isEmpty())
    {
        return QStringList("** FAILED **");
    }

    return m_ProfileList;
}
