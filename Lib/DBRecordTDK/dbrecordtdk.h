#ifndef STARLINGLAB_DBRECORDTDK_H
#define STARLINGLAB_DBRECORDTDK_H
#include "databasebase.h"
#include "dbenginesqlite.h"
#include "Model/SettingGeneralModel.h"
#include "Model/SettingConnectionModel.h"
#include "Model/TDKLogModel.h"
#include "Model/ProtocolModel.h"
#include "Model/MeasurementRAWModel.h"

namespace StarlingLab {

class DBRecordTDK : public DatabaseBase
{
public:
    DBRecordTDK();
    SettingGeneralModel getSettingGeneral();
    SettingConnectionModel getSettingConnection();

};

} // namespace StarlingLab

#endif // STARLINGLAB_DBRECORDTDK_H
