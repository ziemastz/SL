#ifndef PROTOCOLMODEL_H
#define PROTOCOLMODEL_H
#include "idatabasemodel.h"
namespace StarlingLab {
QVector<int> toVectorInt(const QString& str) {
    QVector<int> ret;
    QStringList list = str.split("|");
    foreach(QString val, list)
        ret << val.toInt();
    return ret;
}
QStringList toStringList(const QVector<int>& tab) {
    QStringList ret;
    foreach(int val,tab)
        ret << QString::number(val);
    return ret;
}
class ProtocolModel : public IDatabaseModel
{
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
    QString description;

    IDatabaseModel* copy() {
        IDatabaseModel* ret = new ProtocolModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("protocol");
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
        description = record.at(i++).toString();
        timestamp = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }

    QVariantList record()const {
        QVariantList ret;
        ret << id
            << name
            << toStringList(anodaVoltage)
            << voltageShiftA
            << voltageShiftB
            << voltageShiftC
            << toStringList(focusingVoltage)
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
#endif // PROTOCOLMODEL_H
