#include "sldatabase.h"

SLDatabase::SLDatabase()
{
    _driver = "QSQLITE";
    _databaseName = "sl.db";
}

void SLDatabase::configDatabase(const QString &configSqlFile)
{
    QFile file(configSqlFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString config = file.readAll();
    QStringList sqlStatements = config.split("^_",Qt::SkipEmptyParts);

    foreach(QString statement, sqlStatements) {
        if(!exec(statement)){
            qWarning() << "Error creation database!";
            return;
        }
    }
}

void SLDatabase::setDriver(const QString &newDriver)
{
    _driver = newDriver;
}

void SLDatabase::setDatabaseName(const QString &newDatabaseName)
{
    _databaseName = newDatabaseName;
}

int SLDatabase::signInUser(const QString &username, const QString &password)
{
    int ret = 0;
    if(exec("SELECT id FROM user WHERE username='"+username+"' AND password='"+password+"' AND isActive=1")) {
        if(records().count() == 1) {
            ret = records().at(0).at(0).toInt();
        }
    }
    return ret;
}

int SLDatabase::isAvailableUsername(const QString &username)
{
    exec("SELECT COUNT(*) FROM user WHERE username='"+username+"'");
    if(_records.count() == 1) {
        if(_records.at(0).at(0).toInt() == 0) {
            return 1;
        }else {
            return 0;
        }
    }
    return -1;
}

int SLDatabase::countRecord(BaseModel *model)
{
    exec("SELECT COUNT(*) FROM "+model->tableName());
    if(_records.count() == 1) {
        return _records.at(0).at(0).toInt();
    }else {
        return -1;
    }
}
bool SLDatabase::select(const int &id, BaseModel *model)
{
    if(exec("SELECT * FROM "+model->tableName()+" WHERE id="+QString::number(id))) {
        if(_records.count() == 1) {
            model->setRecord(_records.at(0));
            return true;
        }
    }
    return false;
}

DatabaseResults SLDatabase::select(BaseModel *model, const QString &filter,const Order &sort, const int &limit, const int &offset)
{
    DatabaseResults ret;
    QString statement = "SELECT * FROM "+model->tableName();
    if(!filter.isEmpty())
        statement.append(" WHERE "+filter);

    switch (sort) {
    case SLDatabase::NoOrder:
        break;
    case SLDatabase::ASC:
        statement.append(" ORDER BY 1 ASC");
        break;
    case SLDatabase::DESC:
        statement.append(" ORDER BY 1 DESC");
        break;

    }

    if(limit !=0)
        statement.append(" LIMIT "+QString::number(limit)+" OFFSET "+QString::number(offset));

    if(exec(statement)) {
        for(int i=0; i<_records.count(); i++) {
            BaseModel* next = model->copy();
            next->setRecord(_records.at(i));
            ret.add(next);
        }
    }
    return ret;
}

bool SLDatabase::update(BaseModel *model)
{
    //update nie sprawdza pozycji w modelu ID,TIMESTAMP
    bool ret = true;
    QVariantList newValues = model->record();
    BaseModel *oldModel = model->copy();
    if(!select(oldModel->id,oldModel))
        return false;

    QVariantList oldValues = oldModel->record();
    QStringList columnNames = fieldName(model);
    QStringList setNewValues;
    for(int i=1; i<oldValues.count()-2; i++) {
        if(oldValues.at(i) != newValues.at(i))
            setNewValues << columnNames.at(i)+"="+Utils::toString(newValues.at(i));
    }
    if(setNewValues.count() > 0) {
        if(oldValues.last() != newValues.last())
            setNewValues << "userId="+Utils::toString(newValues.last());
        setNewValues << "lastModification="+Utils::toString(QDateTime::currentDateTime());
        if(!exec("UPDATE "+model->tableName()+" SET "+setNewValues.join(", ")+" WHERE id="+QString::number(model->id)))
            ret = false;
    }
    delete oldModel;
    return ret;
}

bool SLDatabase::insert(BaseModel *model)
{
    model->id = 0;
    model->lastModification = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    QStringList values = Utils::toStringList(model->record());
    if(!values.isEmpty() && values.first().toInt() == 0) {
        values[0] = "NULL";
    }
    bool ret = exec("INSERT INTO "+model->tableName()+" VALUES("+values.join(", ")+")");
    model->id = _lastInsertId;
    return ret;
}

bool SLDatabase::remove(BaseModel *model)
{
    return exec("DELETE FROM "+model->tableName()+" WHERE id="+QString::number(model->id));
}

bool SLDatabase::remove(BaseModel *model, const QString &filter)
{
    return exec("DELETE FROM "+model->tableName()+" WHERE "+filter);
}

QStringList SLDatabase::fieldName(BaseModel *model) const
{
    QString connectionName;
    QStringList ret;
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(_driver,QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz"));
        db.setDatabaseName(_databaseName);
        if(!db.open()) {
            qWarning() << db.lastError().text();
            return ret;
        }
        connectionName = db.connectionName();
        QSqlRecord record = db.driver()->record(model->tableName());
        for(int i=0; i<record.count(); i++)
            ret << record.fieldName(i);
        db.close();
    }
    QSqlDatabase::removeDatabase(connectionName);
    return ret;
}

bool SLDatabase::exec(const QString &statement)
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
        }else {
            if(query.lastInsertId().isValid())
                _lastInsertId = query.lastInsertId().toInt();
            else
                _lastInsertId = 0;
        }
        db.close();
    }
    QSqlDatabase::removeDatabase(connectionName);
    return true;
}

QVector<QVariantList> SLDatabase::records() const
{
    return _records;
}
