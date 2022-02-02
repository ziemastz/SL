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
#include "DatabaseResults.h"
#include "Model/baseModel.h"
#include "Model/userModel.h"
#include "Model/tripleRegSettingsModel.h"
#include "Model/tripleRegProtocolModel.h"
#include "Model/tripleRegMeasurementProtocolModel.h"
#include "Model/tripleRegMeasurementRegisterModel.h"
#include "Model/tripleRegMeasuringSystemModel.h"
#include "Model/tripleRegMeasurementRAWModel.h"

class DatabaseStarlingLab : public QObject
{
public:
    DatabaseStarlingLab();
    void createDatabase(const QString &configFile);

    int signInUser(const QString &username, const QString &password);
    int isAvailableUsername(const QString &username);

    int isAvailableProtocolName(const QString &protocolName);

    int countMeasurementFrom(const QString &date);

    bool select(const int &id, BaseModel *model);
    DatabaseResults select(BaseModel *model, const QString &filter = QString(), const int &limit = 0, const int &offset = 0);
    bool update(BaseModel *model);
    bool insert(BaseModel *model);
    bool remove(BaseModel *model);

    int lastInsertId() const;


private:
    QString _driver;
    QString _databaseName;
    QVector<QVariantList> _records;
    int _lastInsertId;

    QStringList fieldName(BaseModel *model) const;

    bool exec(const QString &statement);
    QVector<QVariantList> records() const;

};

#endif // DATABASESTARLINGLAB_H
