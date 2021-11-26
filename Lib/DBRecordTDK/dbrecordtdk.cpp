#include "dbrecordtdk.h"

namespace StarlingLab {

DBRecordTDK::DBRecordTDK()
{
    DBEngineSqlite *sqlite = new DBEngineSqlite();
    sqlite->setDatabaseName("recordTDK.db");
    addEngine(sqlite);
}

} // namespace StarlingLab
