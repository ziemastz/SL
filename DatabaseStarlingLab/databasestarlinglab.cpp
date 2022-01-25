#include "databasestarlinglab.h"

DatabaseStarlingLab::DatabaseStarlingLab()
{
    _driver = "QSQLITE";
    _connectionName = "sl.db";
    if(!QFile::exists(_connectionName)) {
        createDatabase();
    }
}

void DatabaseStarlingLab::createDatabase() const
{
    QFile file("sl.sql");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString config = file.readAll();
    QStringList sqlStatement = config.split(";");


}
