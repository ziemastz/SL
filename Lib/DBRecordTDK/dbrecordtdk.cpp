#include "dbrecordtdk.h"

namespace StarlingLab {

DBRecordTDK::DBRecordTDK() : DatabaseBase()
{
    DBEngineSqlite *sqlite = new DBEngineSqlite();
    sqlite->setDatabaseName("recordTDK.db");
    addEngine(sqlite);
}

SettingGeneralModel DBRecordTDK::getSettingGeneral()
{
    SettingGeneralModel ret;
    ret.id = 0;
    DBResults result = engine()->select(&ret);
    if(result.count() == 1) {
        ret.setRecord(result.at(0)->record());
    }
    return ret;
}

SettingConnectionModel DBRecordTDK::getSettingConnection()
{
    SettingConnectionModel ret;
    ret.id = 0;
    DBResults result = engine()->select(&ret);
    if(result.count() == 1) {
        ret.setRecord(result.at(0)->record());
    }
    return ret;
}

ProtocolModel DBRecordTDK::getProtocol(const QString &name)
{
    ProtocolModel ret;
    ret.id = 0;
    DBResults result = engine()->select(&ret,"name='"+name+"'");
    if(result.count() == 1) {
        ret.setRecord(result.at(0)->record());
    };
    return ret;
}

ProtocolModel DBRecordTDK::getProtocol(const int &id)
{
    ProtocolModel ret;
    ret.id = 0;
    DBResults result = engine()->select(&ret,"id="+QString::number(id));
    if(result.count() == 1) {
        ret.setRecord(result.at(0)->record());
    };
    return ret;
}

QStringList DBRecordTDK::getProtocolNames()
{
    QStringList ret;
    ProtocolModel model;
    DBResults results = engine()->select(&model);
    for(int i=0; i<results.count() ; i++) {
        model.setRecord(results.at(i)->record());
        ret << model.name;
    }
    return ret;
}

} // namespace StarlingLab
