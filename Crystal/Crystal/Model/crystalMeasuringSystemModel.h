#ifndef CRYSTALMEASURINGSYSTEMMODEL_H
#define CRYSTALMEASURINGSYSTEMMODEL_H
#include "dbcrystal.h"
class CrystalMeasuringSystemModel : public BaseModel
{
public:
    QString numberA;
    QString numberB;
    QString numberC;
    QString numberD;
    QString name;
    QString fullName;
    QString measuremntProcedureName;
    QString location;
    QString notes;

    BaseModel* copy() {
        BaseModel* ret = new CrystalMeasuringSystemModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("crystalMeasuringSystem");
    }

    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        numberA = record.at(i++).toString();
        numberB = record.at(i++).toString();
        numberC = record.at(i++).toString();
        numberD = record.at(i++).toString();
        name = record.at(i++).toString();
        fullName = record.at(i++).toString();
        measuremntProcedureName = record.at(i++).toString();
        location = record.at(i++).toString();
        notes = record.at(i++).toString();
        lastModification = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }
    QVariantList record()const {
        QVariantList ret;
        ret << id
            << numberA
            << numberB
            << numberC
            << numberD
            << name
            << fullName
            << measuremntProcedureName
            << location
            << notes
            << lastModification
            << userId;
        return ret;
    }
};
#endif // CRYSTALMEASURINGSYSTEMMODEL_H
