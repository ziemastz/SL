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
    enum STATUS_LOG {
        Deleted = -1,
        Insert = 0,
        Finished = 1,

    };
    DBRecordTDK();
    SettingGeneralModel getSettingGeneral();
    SettingConnectionModel getSettingConnection();
    ProtocolModel getProtocol(const QString& name);
    QStringList getProtocolNames();

};

} // namespace StarlingLab

#endif // STARLINGLAB_DBRECORDTDK_H
