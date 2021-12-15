#ifndef TDKLOGMODEL_H
#define TDKLOGMODEL_H
#include "idatabasemodel.h"
namespace StarlingLab {
class TDKLogModel : public IDatabaseModel
{
public:
    struct MeasurementTime {
        int blank;
        int source;
        int repeating;
    }time;
    QString creationDateTime;
    QString nuclide;
    QString solution;
    int noSources;
    QString sourceId;
    QString sourcePreparationDate;
    QString description;
    QString linked;
    int madeByUserId;
    int status;
    int category;
    int measurementProtocolId;

    IDatabaseModel* copy() {
        IDatabaseModel* ret = new TDKLogModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName() const {
        return QString("tdkLog");
    }

    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        creationDateTime = record.at(i++).toString();
        nuclide = record.at(i++).toString();
        solution = record.at(i++).toString();
        noSources = record.at(i++).toInt();
        sourceId = record.at(i++).toString();
        sourcePreparationDate = record.at(i++).toString();
        description = record.at(i++).toString();
        linked = record.at(i++).toString();
        madeByUserId = record.at(i++).toInt();
        status = record.at(i++).toInt();
        category = record.at(i++).toInt();
        measurementProtocolId = record.at(i++).toInt();
        timestamp = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }

    QVariantList record() const {
        QVariantList ret;
        ret << id
            << creationDateTime
            << nuclide
            << solution
            << noSources
            << sourceId
            << sourcePreparationDate
            << description
            << linked
            << madeByUserId
            << status
            << category
            << measurementProtocolId
            << timestamp
            << userId;
        return ret;
    }
};
}
#endif // TDKLOGMODEL_H
