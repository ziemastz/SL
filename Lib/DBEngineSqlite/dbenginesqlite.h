#ifndef STARLINGLAB_DBENGINESQLITE_H
#define STARLINGLAB_DBENGINESQLITE_H
#include "idatabaseengine.h"
#include "dbresults.h"
#include "utils.h"

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QDebug>
#include <QFile>
#include <QDateTime>

namespace StarlingLab {

class DBEngineSqlite : public IDatabaseEngine
{
public:
    DBEngineSqlite();
    ~DBEngineSqlite();

    bool insert(IDatabaseModel* model);
    DBResults select(IDatabaseModel* model, const QString& filter = QString(), const int& limit = 0, const int& offset = 0);
    bool update(IDatabaseModel* model);
    bool remove(IDatabaseModel* model);

    QStringList getColumnNames(IDatabaseModel* model);

    void setDriver(const QString &driver);
    void setDatabaseName(const QString &databaseName);

private:
    QString _driver;
    QString _databaseName;

    QSqlDatabase *_db;
    QSqlQuery *_query;

    bool exec(const QString& statement);
    DBResults load(IDatabaseModel* model);
};

} // namespace StarlingLab

#endif // STARLINGLAB_DBENGINESQLITE_H
