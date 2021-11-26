#ifndef SETTINGCONNECTIONMODEL_H
#define SETTINGCONNECTIONMODEL_H
#include "idatabasemodel.h"
namespace StarlingLab {
class SettingConnectionModel : public IDatabaseModel
{
public:
    //int id;
    QString port;
    QString braudRate;
    int lBusAddress;
    QString deviceName;
    bool isExtClk;
    //QString timestamp;
    //int userId;

    IDatabaseModel* copy() {
        SettingConnectionModel *ret = new SettingConnectionModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("settingConnection");
    }
    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        port = record.at(i++).toString();
        braudRate = record.at(i++).toString();
        lBusAddress = record.at(i++).toInt();
        deviceName = record.at(i++).toString();
        isExtClk = record.at(i++).toBool();
        timestamp = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }
    QVariantList record()const {
        QVariantList ret;
        ret << id
            << port
            << braudRate
            << lBusAddress
            << deviceName
            << isExtClk
            << timestamp
            << userId;
        return ret;
    }
    };
}
#endif // SETTINGCONNECTIONMODEL_H
