#include "databasestarlinglab.h"

DatabaseStarlingLab::DatabaseStarlingLab()
{
    _driver = "QSQLITE";
    _databaseName = "sl.db";
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

int DatabaseStarlingLab::isAvailableUsername(const QString &username)
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

int DatabaseStarlingLab::isAvailableProtocolName(const QString &protocolName)
{
    exec("SELECT COUNT(*) FROM tripleRegProtocol WHERE name='"+protocolName+"'");
    if(_records.count() == 1) {
        if(_records.at(0).at(0).toInt() == 0) {
            return 1;
        }else {
            return 0;
        }
    }
    return -1;
}

bool DatabaseStarlingLab::select(const int &id, BaseModel *model)
{
    if(exec("SELECT * FROM "+model->tableName()+" WHERE id="+QString::number(id))) {
        if(_records.count() == 1) {
            model->setRecord(_records.at(0));
            return true;
        }
    }
    return false;
}

DatabaseResults DatabaseStarlingLab::select(BaseModel *model, const QString &filter, const int &limit, const int &offset)
{
    DatabaseResults ret;
    QString statement = "SELECT * FROM "+model->tableName();
    if(!filter.isEmpty())
        statement.append(" WHERE "+filter);

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

bool DatabaseStarlingLab::update(BaseModel *model)
{
    //update nie sprawdza pozycji w modelu ID,TIMESTAMP
    bool ret = true;
    QVariantList newValues = model->record();
    BaseModel *oldModel = model->copy();
    if(!select(1,oldModel))
        return false;

    QVariantList oldValues = oldModel->record();
    QStringList columnNames = fieldName(model);
    QStringList setNewValues;
    for(int i=1; i<oldValues.count()-2; i++) {
        if(oldValues.at(i) != newValues.at(i))
            setNewValues << columnNames.at(i)+"="+Utils::toString(newValues.at(i));
    }
    if(oldValues.last() != newValues.last())
        setNewValues << "userId="+Utils::toString(newValues.last());
    if(setNewValues.count() > 0) {
        setNewValues << "lastModification="+Utils::toString(QDateTime::currentDateTime());
        if(!exec("UPDATE "+model->tableName()+" SET "+setNewValues.join(", ")+" WHERE id="+QString::number(model->id)))
            ret = false;
    }
    delete oldModel;
    return ret;
}

bool DatabaseStarlingLab::insert(BaseModel *model)
{
    model->id = 0;
    model->lastModification = Utils::toString(QDateTime::currentDateTime());

    QStringList values = Utils::toStringList(model->record());
    if(!values.isEmpty() && values.first().toInt() == 0) {
        values[0] = "NULL";
    }
    bool ret = exec("INSERT INTO "+model->tableName()+" VALUES("+values.join(", ")+")");
    model->id = lastInsertId();
    return ret;
}

int DatabaseStarlingLab::lastInsertId() const
{
    return _lastInsertId;
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

QVector<QVariantList> DatabaseStarlingLab::records() const
{
    return _records;
}

void DatabaseStarlingLab::createDatabase(const QString &configFile)
{
    QFile file(configFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString config = file.readAll();
    QStringList sqlStatements = config.split(";",Qt::SkipEmptyParts);

    foreach(QString statement, sqlStatements) {
        if(!exec(statement)){
            qWarning() << "Error creation database!";
            return;
        }
    }
}

QStringList DatabaseStarlingLab::fieldName(BaseModel *model) const
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
