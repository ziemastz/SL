#ifndef CRYSTALMEASUREMENTPROTOCOLMODEL_H
#define CRYSTALMEASUREMENTPROTOCOLMODEL_H
#include "dbcrystal.h"
class CrystalMeasurementProtocolModel : public BaseModel
{
    QVector<double> toVectorDouble(const QString& str) const {
        QVector<double> ret;
        QStringList list = str.split("|");
        foreach(QString val, list)
            ret << val.toDouble();
        return ret;
    }
    QString toString(const QVector<double>& tab) const {
        QStringList ret;
        foreach(double val,tab)
            ret << QString::number(val);
        return ret.join("|");
    }
public:
    QString measurementId;
    QVector<double> anodeVoltage;
    QVector<double> thresholdVoltage;
    double extendableDeadTime;
    QString notes;

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
        measurementId = record.at(i++).toString();
        anodeVoltage = toVectorDouble(record.at(i++).toString());
        thresholdVoltage = toVectorDouble(record.at(i++).toString());
        extendableDeadTime = record.at(i++).toDouble();
        notes = record.at(i++).toString();
        lastModification = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }
    QVariantList record()const {
        QVariantList ret;
        ret << id
            << measurementId
            << toString(anodeVoltage)
            << toString(thresholdVoltage)
            << extendableDeadTime
            << notes
            << lastModification
            << userId;
        return ret;
    }

};
#endif // CRYSTALMEASUREMENTPROTOCOLMODEL_H
