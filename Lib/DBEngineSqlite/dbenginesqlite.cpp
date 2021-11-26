#include "dbenginesqlite.h"

namespace StarlingLab {

DBEngineSqlite::DBEngineSqlite()
{
    _driver = "QSQLITE";
    _databaseName = "starlingLab.db";
    _db = nullptr;
    _query = nullptr;
}

DBEngineSqlite::~DBEngineSqlite()
{
    if(_query != nullptr) {
        _query->finish();
        delete _query;
    }
    if(_db != nullptr) {
        QString connectionName = _db->connectionName();
        _db->close();
        delete _db;
        QSqlDatabase::removeDatabase(connectionName);
    }
}

bool DBEngineSqlite::insert(IDatabaseModel *model)
{
    model->id = 0;
    QStringList values = Utils::toStringList(model->record());
    if(!values.isEmpty() && values.first().toInt() == 0) {
        values[0] = "NULL";
    }
    bool ret = exec("INSERT INTO "+model->tableName()+" VALUES("+values.join(", ")+")");
    //qDebug() << "Last inserID: " << _query.lastInsertId();
    model->id = _query->lastInsertId().toInt();
    return ret;
}

DBResults DBEngineSqlite::select(IDatabaseModel *model, const QString &filter, const int &limit, const int &offset)
{
    QString statement = "SELECT * FROM "+model->tableName();

    if(!filter.isEmpty())
        statement.append(" WHERE "+filter);

    if(limit !=0)
        statement.append(" LIMIT "+QString::number(limit)+" OFFSET "+QString::number(offset));

    if(!exec(statement))
        return DBResults();

    return load(model);
}

bool DBEngineSqlite::update(IDatabaseModel *model)
{
    //update nie sprawdza pozycji w modelu ID,TIMESTAMP
    bool ret = true;
    QVariantList newValues = model->record();
    IDatabaseModel *oldModel = model->copy();
    DBResults result = select(oldModel,"id="+model->record(0).toString());
    if(result.count() == 1) {
        QVariantList oldValues = oldModel->record();
        QStringList columnNames = getColumnNames(model);
        QStringList setNewValues;
        for(int i=1; i<oldValues.count()-2; i++) {
            if(oldValues.at(i) != newValues.at(i))
                setNewValues << columnNames.at(i)+"="+Utils::toString(newValues.at(i));
        }
        if(oldValues.last() != newValues.last())
            setNewValues << "userId="+Utils::toString(newValues.last());
        if(setNewValues.count() > 0) {
            setNewValues << "timestamp="+Utils::toString(QDateTime::currentDateTime());
            if(!exec("UPDATE "+model->tableName()+" SET "+setNewValues.join(", ")+" WHERE id="+QString::number(model->id)))
                ret = false;
        }
    }else {
        ret = false;
    }
    delete oldModel;
    return ret;
}

bool DBEngineSqlite::remove(IDatabaseModel *model)
{
    return exec("DELETE FROM "+model->tableName()+" WHERE id="+QString::number(model->id));
}

QStringList DBEngineSqlite::getColumnNames(IDatabaseModel *model)
{
    QStringList ret;
    if(exec("SELECT * FROM "+model->tableName()+" LIMIT 1")) {
        for(int i=0; i<_query->record().count(); i++) {
            ret << _query->record().fieldName(i);
        }
    }
    return ret;
}

void DBEngineSqlite::setDriver(const QString &driver)
{
    _driver = driver;
}

void DBEngineSqlite::setDatabaseName(const QString &databaseName)
{
    _databaseName = databaseName;
}

bool DBEngineSqlite::exec(const QString &statement)
{
    if(_db == nullptr) {
        _db = new QSqlDatabase;
        *_db = QSqlDatabase::addDatabase(_driver,QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz"));
        _db->setDatabaseName(_databaseName);
    }
    if(!_db->isOpen()) {
        if(!_db->open()) {
            qWarning() << _db->lastError().text();
            return false;
        }
        _query = new QSqlQuery(*_db);
    }

    if(!_query->exec(statement)) {
        qWarning() << _query->lastError().text();
        return false;
    }else {
        return true;
    }
}

DBResults DBEngineSqlite::load(IDatabaseModel *model)
{
    DBResults ret;
    //query.setForwardOnly(true);
    while (_query->next()) {
        QVariantList record;
        for(int i=0;i<_query->record().count();i++) {
            record << _query->value(i);
        }
        model->setRecord(record);
        IDatabaseModel *next = model->copy();
        //next->setRecord(record);
        ret.add(next);
    }
    return ret;
}

} // namespace StarlingLab
