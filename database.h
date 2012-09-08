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
    QSqlError saveProfile(const QString name, const QString setting, int channel, int &value);


protected:

    void initCommon(void);

    QSqlError openDb();

private:

    QSqlDatabase db;

    bool checkSettingsPath(const QString& path) const;
    QString databaseNameAndPath(void) const;
    QString m_dbPathAndName;
    //QStringList m_ProfileList();
};

#endif // DATABASE_H
