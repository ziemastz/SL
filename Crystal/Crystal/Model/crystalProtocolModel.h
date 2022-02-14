#ifndef CRYSTALPROTOCOLMODEL_H
#define CRYSTALPROTOCOLMODEL_H
#include "dbcrystal.h"
class CrystalProtocolModel : public BaseModel
{
public:
    QString systemLabel;
    double anodeVoltage;
    double thresholdVoltage;
    double extendableDeadTime;
    QString notes;

    BaseModel *copy() {
        CrystalProtocolModel *ret = new CrystalProtocolModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("crystalProtocol");
    }
    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        systemLabel = record.at(i++).toString();
        anodeVoltage = record.at(i++).toDouble();
        thresholdVoltage = record.at(i++).toDouble();
        extendableDeadTime = record.at(i++).toDouble();
        notes = record.at(i++).toString();
        lastModification = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }
    QVariantList record()const {
        QVariantList ret;
        ret << id
            << systemLabel
            << anodeVoltage
            << thresholdVoltage
            << extendableDeadTime
            << notes
            << lastModification
            << userId;
        return ret;
    }

};

#endif // CRYSTALPROTOCOLMODEL_H
