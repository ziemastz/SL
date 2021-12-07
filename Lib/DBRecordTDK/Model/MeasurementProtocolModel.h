#ifndef MEASUREMENTPROTOCOLMODEL_H
#define MEASUREMENTPROTOCOLMODEL_H
#include "idatabasemodel.h"
namespace StarlingLab {
class MeasurementProtocol : public IDatabaseModel
{
public:
    QString name;
    int anodaVoltage;
    int voltageShiftA;
    int voltageShiftB;
    int voltageShiftC;
    int focusingVoltage;
    float resolvingTime;
    float deadTime;
    float thrA;
    float thrB;
    float thrC;
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
        anodaVoltage = record.at(i++).toInt();
        voltageShiftA = record.at(i++).toInt();
        voltageShiftB = record.at(i++).toInt();
        voltageShiftC = record.at(i++).toInt();
        focusingVoltage = record.at(i++).toInt();
        resolvingTime = record.at(i++).toFloat();
        deadTime = record.at(i++).toFloat();
        thrA = record.at(i++).toFloat();
        thrB = record.at(i++).toFloat();
        thrC = record.at(i++).toFloat();
        description = record.at(i++).toString();
        timestamp = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }

    QVariantList record()const {
        QVariantList ret;
        ret << id
            << name
            << anodaVoltage
            << voltageShiftA
            << voltageShiftB
            << voltageShiftC
            << focusingVoltage
            << resolvingTime
            << deadTime
            << thrA
            << thrB
            << thrC
            << description
            << timestamp
            << userId;
        return ret;
    }
};
}
#endif // MEASUREMENTPROTOCOLMODEL_H
