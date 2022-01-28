#ifndef TRIPLEREGMEASUREMENTREGISTERMODEL_H
#define TRIPLEREGMEASUREMENTREGISTERMODEL_H
#include "baseModel.h"
class TripleRegMeasurementRegisterModel : public BaseModel
{
public:
    QString measurementId;
    QString measurementDate;
    QString nuclide;
    QString solutionId;
    QString sourceId;
    int sourceNo;
    bool isBlank;
    int blankTime;
    int sourceTime;
    int repeat;
    int protocolId;
    QString linked;
    QString category;
    QString comments;

    BaseModel* copy() {
        BaseModel* ret = new TripleRegMeasurementRegisterModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("tripleRegMeasurementRegister");
    }
    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        measurementId = record.at(i++).toString();
        measurementDate = record.at(i++).toString();
        nuclide = record.at(i++).toString();
        solutionId = record.at(i++).toString();
        sourceId = record.at(i++).toString();
        sourceNo = record.at(i++).toInt();
        isBlank = record.at(i++).toBool();
        blankTime = record.at(i++).toInt();
        sourceTime = record.at(i++).toInt();
        repeat = record.at(i++).toInt();
        protocolId = record.at(i++).toInt();
        linked = record.at(i++).toString();
        category = record.at(i++).toString();
        comments = record.at(i++).toString();
        lastModification = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }
    QVariantList record()const {
        QVariantList ret;
        ret << id
            << measurementId
            << measurementDate
            << nuclide
            << solutionId
            << sourceId
            << sourceNo
            << isBlank
            << blankTime
            << sourceTime
            << repeat
            << protocolId
            << linked
            << category
            << comments
            << lastModification
            << userId;
        return ret;
    }
};
#endif // TRIPLEREGMEASUREMENTREGISTERMODEL_H
