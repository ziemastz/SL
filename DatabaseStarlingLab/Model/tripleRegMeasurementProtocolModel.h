#ifndef TRIPLEREGMEASUREMENTPROTOCOLMODEL_H
#define TRIPLEREGMEASUREMENTPROTOCOLMODEL_H
#include "baseModel.h"
class TripleRegMeasurementProtocolModel : public BaseModel
{
    QVector<int> toVectorInt(const QString& str) const {
        QVector<int> ret;
        QStringList list = str.split("|");
        foreach(QString val, list)
            ret << val.toInt();
        return ret;
    }
    QString toString(const QVector<int>& tab) const {
        QStringList ret;
        foreach(int val,tab)
            ret << QString::number(val);
        return ret.join("|");
    }

public:
    QString name;
    QVector<int> anodaVoltage;
    int voltageShiftA;
    int voltageShiftB;
    int voltageShiftC;
    QVector<int> focusingVoltage;
    int resolvingTime;
    int deadTime;
    double thrA;
    double thrB;
    double thrC;
    QString notes;

    BaseModel* copy() {
        BaseModel* ret = new TripleRegMeasurementProtocolModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("tripleRegMeasurementProtocol");
    }

    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        name = record.at(i++).toString();
        anodaVoltage = toVectorInt(record.at(i++).toString());
        voltageShiftA = record.at(i++).toInt();
        voltageShiftB = record.at(i++).toInt();
        voltageShiftC = record.at(i++).toInt();
        focusingVoltage = toVectorInt(record.at(i++).toString());
        resolvingTime = record.at(i++).toFloat();
        deadTime = record.at(i++).toFloat();
        thrA = record.at(i++).toFloat();
        thrB = record.at(i++).toFloat();
        thrC = record.at(i++).toFloat();
        notes = record.at(i++).toString();
        lastModification = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }

    QVariantList record()const {
        QVariantList ret;
        ret << id
            << name
            << toString(anodaVoltage)
            << voltageShiftA
            << voltageShiftB
            << voltageShiftC
            << toString(focusingVoltage)
            << resolvingTime
            << deadTime
            << thrA
            << thrB
            << thrC
            << notes
            << lastModification
            << userId;
        return ret;
    }
};
#endif // TRIPLEREGMEASUREMENTPROTOCOLMODEL_H
