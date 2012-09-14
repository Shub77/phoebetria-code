#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSettings>
#include <QtSql>

class Database
{

public:

    Database();

    QStringList readProfileNames();
    int readProfile(const QString name, const QString setting, int channel);
    QSqlError saveProfile(const QString name, const QString setting, int channel, int value);
    QSqlError eraseProfile(const QString name);

protected:

    void initCommon(void);

    QSqlError openDb();

private:

    QSqlDatabase db;

    QString databaseNameAndPath(void) const;
    QString m_dbPathAndName;
    //QStringList m_ProfileList();

    static QString m_dbFilename;
    static QString m_dbConnectionName;
};

#endif // DATABASE_H
