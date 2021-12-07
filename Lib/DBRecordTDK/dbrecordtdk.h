#ifndef STARLINGLAB_DBRECORDTDK_H
#define STARLINGLAB_DBRECORDTDK_H
#include "databasebase.h"
#include "dbenginesqlite.h"
#include "Model/SettingGeneralModel.h"
namespace StarlingLab {

class DBRecordTDK : public DatabaseBase
{
public:
    DBRecordTDK();
    SettingGeneralModel getSettingGeneral();

};

} // namespace StarlingLab

#endif // STARLINGLAB_DBRECORDTDK_H
