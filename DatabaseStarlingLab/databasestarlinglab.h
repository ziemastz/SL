#ifndef DATABASESTARLINGLAB_H
#define DATABASESTARLINGLAB_H
#include <QObject>
#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QVariantList>
#include <QVector>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

class DatabaseStarlingLab : public QObject
{
public:
    DatabaseStarlingLab();
    int signInUser(const QString &username, const QString &password);

private:
    QString _driver;
    QString _databaseName;
    QVector<QVariantList> _records;

    bool exec(const QString &statement);
    QVector<QVariantList> records() const;

    void createDatabase();
};

#endif // DATABASESTARLINGLAB_H
