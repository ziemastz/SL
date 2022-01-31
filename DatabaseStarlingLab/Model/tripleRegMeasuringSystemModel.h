#ifndef TRIPLEREGMEASURINGSYSTEMMODEL_H
#define TRIPLEREGMEASURINGSYSTEMMODEL_H
#include "baseModel.h"
class TripleRegMeasuringSystemModel : public BaseModel
{
public:
    QString name;
    QString fullName;
    QString measuremntProcedureName;
    QString location;
    bool isDefault;
    QString notes;

    BaseModel* copy() {
        BaseModel* ret = new TripleRegMeasuringSystemModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("tripleRegMeasuringSystem");
    }

    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        name = record.at(i++).toString();
        fullName = record.at(i++).toString();
        measuremntProcedureName = record.at(i++).toString();
        location = record.at(i++).toString();
        isDefault = record.at(i++).toBool();
        notes = record.at(i++).toString();
        lastModification = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }
    QVariantList record()const {
        QVariantList ret;
        ret << id
            << name
            << fullName
            << measuremntProcedureName
            << location
            << isDefault
            << notes
            << lastModification
            << userId;
        return ret;
    }
};

#endif // TRIPLEREGMEASURINGSYSTEMMODEL_H
