#include "databasebase.h"

namespace StarlingLab {

IDatabaseEngine *DatabaseBase::_engine = 0;
UserModel *DatabaseBase::_loggedUser = 0;

DatabaseBase::DatabaseBase()
{
    if(_loggedUser == 0){
        _loggedUser = new UserModel;
        _loggedUser->id = 0;
    }

}

DatabaseBase::~DatabaseBase()
{
    if(_engine != 0)
        delete _engine;
    if(_loggedUser != 0)
        delete _loggedUser;
}

void DatabaseBase::addEngine(IDatabaseEngine *engine)
{
    if(_engine != 0)
        delete _engine;
    _engine = engine;
}

bool DatabaseBase::insert(IDatabaseModel *model)
{
    model->timestamp = QDateTime::currentDateTime().toString(FORMAT_TIMESTAMP);
    model->userId = _loggedUser->id;
    bool ret = _engine->insert(model);
    if(!ret) {
        _lastError = tr("ERROR: Wrong insert record of ")+model->tableName()+tr(" table");
    }
    return ret;
}

bool DatabaseBase::update(IDatabaseModel *model)
{
    model->timestamp = QDateTime::currentDateTime().toString(FORMAT_TIMESTAMP);
    model->userId = _loggedUser->id;
    bool ret = _engine->update(model);
    if(!ret) {
        _lastError = tr("ERROR: Wrong update record of ")+model->tableName()+tr(" table");
    }
    return ret;
}

bool DatabaseBase::remove(IDatabaseModel *model)
{
    model->timestamp = QDateTime::currentDateTime().toString(FORMAT_TIMESTAMP);
    model->userId = _loggedUser->id;
    bool ret = _engine->update(model);
    if(!ret) {
        _lastError = tr("ERROR: Wrong remove record of ")+model->tableName()+tr(" table");
    }
    return ret;
}

IDatabaseEngine *DatabaseBase::engine() const
{
    return _engine;
}

bool DatabaseBase::loginUser(const QString &username, const QString &password)
{
    bool ret = false;
    UserModel *user = new UserModel;
    DBResults result = _engine->select(user,"username='"+username+"' AND password='"+password+"' and isActive=1");
    if(result.count() == 1) {
        _loggedUser->setRecord(result.at(0)->record());
        ret = true;
    }else {
        _lastError = tr("FAIL LOGIN");
        ret = false;
    }
    delete user;
    return ret;
}

UserModel *DatabaseBase::getLoggeduser() const
{
    return _loggedUser;
}

UserModel DatabaseBase::getUser(const int &id)
{
    UserModel ret;
    ret.id = 0;
    DBResults results = _engine->select(&ret,"id="+QString::number(id));
    return ret;
}

UserModel DatabaseBase::getUser(const QString &username)
{
    UserModel ret;
    ret.id = 0;
    DBResults results = _engine->select(&ret,"username='"+username+"'");
    return ret;
}

QStringList DatabaseBase::getUsernames()
{
    DBResults results = _engine->select(new UserModel);
    QStringList ret;
    for(int i=0; i<results.count(); i++) {
        ret << results.at(i)->record(1).toString();
    }
    return ret;
}

QString DatabaseBase::lastError()
{
    QString ret = _lastError;
    _lastError.clear();
    return ret;
}

} // namespace StarlingLab
