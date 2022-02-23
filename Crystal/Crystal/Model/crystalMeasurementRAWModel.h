#ifndef CRYSTALMEASUREMENTRAWMODEL_H
#define CRYSTALMEASUREMENTRAWMODEL_H
#include "dbcrystal.h"
class CrystalMeasurementRAWModel : public BaseModel
{
public:
    int measurementId;
    QString startMeasurementDateTime;
    int sourceNo;
    QString pointTag;
    int repeat;
    unsigned int counts;
    unsigned int liveTime;
    unsigned int realTime;


    BaseModel *copy() {
        CrystalMeasurementRAWModel *ret = new CrystalMeasurementRAWModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("crystalMeasurementRAW");
    }
    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        measurementId = record.at(i++).toInt();
        startMeasurementDateTime = record.at(i++).toString();
        sourceNo = record.at(i++).toInt();
        pointTag = record.at(i++).toString();
        repeat = record.at(i++).toInt();
        counts = record.at(i++).toUInt();
        liveTime = record.at(i++).toUInt();
        realTime = record.at(i++).toUInt();
        lastModification = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }
    QVariantList record()const {
        QVariantList ret;
        ret << id
            << measurementId
            << startMeasurementDateTime
            << sourceNo
            << pointTag
            << repeat
            << counts
            << liveTime
            << realTime
            << lastModification
            << userId;
        return ret;
    }
};
#endif // CRYSTALMEASUREMENTRAWMODEL_H
