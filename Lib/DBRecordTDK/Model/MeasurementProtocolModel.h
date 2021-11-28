#ifndef MEASUREMENTPROTOCOLMODEL_H
#define MEASUREMENTPROTOCOLMODEL_H
#include "idatabasemodel.h"
namespace StarlingLab {
class MeasurementProtocol : public IDatabaseModel
{
public:
    QString name;
    int blankTime;
    int sourceTime;
    int repeated;
    int anodaVoltage;
    int voltageShiftA;
    int voltageShiftB;
    int voltageShiftC;
    int focusingVoltage;
    QString description;

    IDatabaseModel* copy() {
        IDatabaseModel* ret = new MeasurementProtocol;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("measurementProtocol");
    }

    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        name = record.at(i++).toString();
        blankTime = record.at(i++).toInt();
        sourceTime = record.at(i++).toInt();
        repeated = record.at(i++).toInt();
        anodaVoltage = record.at(i++).toInt();
        voltageShiftA = record.at(i++).toInt();
        voltageShiftB = record.at(i++).toInt();
        voltageShiftC = record.at(i++).toInt();
        focusingVoltage = record.at(i++).toInt();
        description = record.at(i++).toString();
        timestamp = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }

    QVariantList record()const {
        QVariantList ret;
        ret << id
            << name
            << blankTime
            << sourceTime
            << repeated
            << anodaVoltage
            << voltageShiftA
            << voltageShiftB
            << voltageShiftC
            << focusingVoltage
            << description
            << timestamp
            << userId;
        return ret;
    }
};
}
#endif // MEASUREMENTPROTOCOLMODEL_H
