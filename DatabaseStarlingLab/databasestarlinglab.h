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
#include <QSqlDriver>

#include "utils.h"
#include "Model/baseModel.h"
#include "Model/tripleRegSettingsModel.h"
#include "Model/userModel.h"

class DatabaseStarlingLab : public QObject
{
public:
    DatabaseStarlingLab();
    int signInUser(const QString &username, const QString &password);
    bool select(const int &id, BaseModel *model);
    bool update(BaseModel *model);

private:
    QString _driver;
    QString _databaseName;
    QVector<QVariantList> _records;

    QStringList fieldName(BaseModel *model) const;

    bool exec(const QString &statement);
    QVector<QVariantList> records() const;

    void createDatabase();
};

#endif // DATABASESTARLINGLAB_H
