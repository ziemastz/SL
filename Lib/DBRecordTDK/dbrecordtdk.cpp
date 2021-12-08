#include "dbrecordtdk.h"

namespace StarlingLab {

DBRecordTDK::DBRecordTDK():DatabaseBase()
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

} // namespace StarlingLab
