#ifndef MEASUREMENTOBJECTMODEL_H
#define MEASUREMENTOBJECTMODEL_H
#include "idatabasemodel.h"
namespace StarlingLab {
class MeasurementObjectModel : public IDatabaseModel
{
public:
    QString solution;
    QString noSourcesId;
    int noSources;
    QString sourcePreparationDate;
    QString description;

    IDatabaseModel* copy() {
        IDatabaseModel* ret = new MeasurementObjectModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("measurementObject");
    }

    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        solution = record.at(i++).toString();
        noSourcesId = record.at(i++).toString();
        noSources = record.at(i++).toInt();
        sourcePreparationDate = record.at(i++).toString();
        description = record.at(i++).toString();
        timestamp = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }

    QVariantList record()const {
        QVariantList ret;
        ret << id
            << solution
            << noSourcesId
            << noSources
            << sourcePreparationDate
            << description
            << timestamp
            << userId;
        return ret;
    }

    QString measurementObject() const {
        QString ret;
        if(!solution.isEmpty())
            ret.append(solution);
        if(!noSourcesId.isEmpty())
            ret.append(" "+noSourcesId);
        if(!sourcePreparationDate.isEmpty())
            ret.append(" "+sourcePreparationDate);
        return ret;
    }
};
}
#endif // MEASUREMENTOBJECTMODEL_H
