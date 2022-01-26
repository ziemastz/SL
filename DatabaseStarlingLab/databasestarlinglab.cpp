#include "databasestarlinglab.h"

DatabaseStarlingLab::DatabaseStarlingLab()
{
    _driver = "QSQLITE";
    _databaseName = "sl.db";
    if(!QFile::exists(_databaseName)) {
        createDatabase();
    }
}

int DatabaseStarlingLab::signInUser(const QString &username, const QString &password)
{
    int ret = 0;
    if(exec("SELECT id FROM user WHERE username='"+username+"' AND password='"+password+"' AND isActive=1")) {
        if(records().count() == 1) {
            ret = records().at(0).at(0).toInt();
        }
    }
    return ret;
}

bool DatabaseStarlingLab::exec(const QString &statement)
{
    QString connectionName;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(_driver,QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz"));
        db.setDatabaseName(_databaseName);
        if(!db.open()) {
            qWarning() << db.lastError().text();
            return false;
        }
        connectionName = db.connectionName();
        QSqlQuery query(db);

        if(!query.exec(statement)) {
            qWarning() << query.lastError().text();
            return false;
        }
        _records.clear();
        if(query.isSelect()) {
            while(query.next()) {
                _records << QVariantList();
                for(int i=0; i<query.record().count(); i++) {
                    _records.last() << query.value(i);
                }
            }
        };
        db.close();
    }
    QSqlDatabase::removeDatabase(connectionName);
    return true;
}

QVector<QVariantList> DatabaseStarlingLab::records() const
{
    return _records;
}

void DatabaseStarlingLab::createDatabase()
{
    QFile file(_databaseName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString config = file.readAll();
    QStringList sqlStatements = config.split(";");

    foreach(QString statement, sqlStatements) {
        if(!exec(statement)){
            qWarning() << "Error creation database!";
            return;
        }
    }
}
