#ifndef DATABASESTARLINGLAB_H
#define DATABASESTARLINGLAB_H
#include <QObject>
#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QDateTime>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class DatabaseStarlingLab : public QObject
{
public:
    DatabaseStarlingLab();
    int signInUser(const QString &username, const QString &password) const;

private:
    QString _driver;
    QString _connectionName;
    QSqlQuery _query;

    bool exce(const QString &statement) const;
    QVariantList record() const;

    void createDatabase() const;
};

#endif // DATABASESTARLINGLAB_H
