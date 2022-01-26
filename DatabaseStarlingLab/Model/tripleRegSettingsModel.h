#ifndef TRIPLEREGSETTINGSMODEL_H
#define TRIPLEREGSETTINGSMODEL_H
#include "baseModel.h"
class TripleRegSettingsModel : public BaseModel
{
public:
    int blankTime;
    int sourceTime;
    int repeat;
    int startDelay;
    int voltageMax;
    QString port;
    QString braudRate;
    int lBusAddress;
    QString deviceName;
    bool isExtClk;

    BaseModel *copy() {
        TripleRegSettingsModel *ret = new TripleRegSettingsModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
            return QString("tripleRegSettings");
    }
    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        blankTime = record.at(i++).toInt();
        sourceTime = record.at(i++).toInt();
        repeat = record.at(i++).toInt();
        startDelay = record.at(i++).toInt();
        voltageMax = record.at(i++).toInt();
        port = record.at(i++).toString();
        braudRate = record.at(i++).toString();
        lBusAddress = record.at(i++).toInt();
        deviceName = record.at(i++).toString();
        isExtClk = record.at(i++).toBool();
        lastModification = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }
    QVariantList record()const {
        QVariantList ret;
        ret << id
            << blankTime
            << sourceTime
            << repeat
            << startDelay
            << voltageMax
            << port
            << braudRate
            << lBusAddress
            << deviceName
            << isExtClk
            << lastModification
            << userId;
        return ret;
    }
};

#endif // TRIPLEREGSETTINGSMODEL_H
