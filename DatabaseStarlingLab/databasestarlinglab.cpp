#include "databasestarlinglab.h"

DatabaseStarlingLab::DatabaseStarlingLab()
{
    _driver = "QSQLITE";
    _databaseName = "sl.db";
    if(!QFile::exists(_databaseName)) {
        createDatabase();
    }
}

int DatabaseStarlingLab::signInUser(const QString &username, const QString &password) const
{
    int ret = 0;
    if(exec("SELECT id FROM user WHERE username='"+username+"' AND password='"+password+"' AND isActive=1")) {
        if(record().count() == 1) {
            ret = record().at(0).at(0).toInt();
        }
    }
    return ret;
}

bool DatabaseStarlingLab::exce(const QString &statement) const
{
    QString connectionName;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(_driver,QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz"));
        db.setDatabaseName(_databaseName);
        if(!db.open()) {
            qWarnig() << db.lastError().text();
            return false;
        }
        connectName = db.connectionName();
        _query = QSqlQuery(db);
        if(!_query.exec(statement)) {
            qWarnig() << _query.lastError().text();
            return false;
        }
        db.close()
    }
    QSqlDatabase::removeDatabase(connectionName);
    return true;
}

void DatabaseStarlingLab::createDatabase() const
{
    QFile file(_connectionName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString config = file.readAll();
    QStringList sqlStatements = config.split(";");

    foreach(QString statement, sqlStatements) {
        if(!exec(statement)){
            qWarnig() << _query.lastError().text();
        }
    }
}
