#ifndef CRYSTALMEASUREMENTPROTOCOLMODEL_H
#define CRYSTALMEASUREMENTPROTOCOLMODEL_H
#include "dbcrystal.h"
class CrystalMeasurementProtocolModel : public BaseModel
{
public:
    double anodeVoltage;
    double thresholdVoltage;
    double extendableDeadTime;
    QString notes;
    QString typePoints;
    QStringList points;

    BaseModel *copy() {
        CrystalMeasurementProtocolModel *ret = new CrystalMeasurementProtocolModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("crystalMeasurementProtocol");
    }
    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        anodeVoltage = record.at(i++).toDouble();
        thresholdVoltage = record.at(i++).toDouble();
        extendableDeadTime = record.at(i++).toDouble();
        notes = record.at(i++).toString();
        typePoints = record.at(i++).toString();
        points = record.at(i++).toString().split("|");
        lastModification = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }
    QVariantList record()const {
        QVariantList ret;
        ret << id
            << anodeVoltage
            << thresholdVoltage
            << extendableDeadTime
            << notes
            << typePoints
            << points
            << lastModification
            << userId;
        return ret;
    }

};
#endif // CRYSTALMEASUREMENTPROTOCOLMODEL_H
