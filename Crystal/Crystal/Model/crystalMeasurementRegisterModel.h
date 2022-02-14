#ifndef CRYSTALMEASUREMENTREGISTERMODEL_H
#define CRYSTALMEASUREMENTREGISTERMODEL_H
#include "dbcrystal.h"
class CrystalMeasurementRegisterModel : public BaseModel
{
public:
    QString systemLabel;
    QString measurementId;
    QString measurementDate;
    QString nuclide;
    QStringList sourceId;
    QString geometry;
    int protocolId;
    int blankTime;
    int sourceTime;
    int repeat;
    QString linked;
    QString category;
    QString comments;
    int authorId;
    int acceptedId;
    QString acceptedDateTime;

    BaseModel *copy() {
        CrystalMeasurementRegisterModel *ret = new CrystalMeasurementRegisterModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("crystalMeasurementRegister");
    }
    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        systemLabel = record.at(i++).toString();
        measurementId = record.at(i++).toString();
        measurementDate = record.at(i++).toString();
        nuclide = record.at(i++).toString();
        sourceId = record.at(i++).toString().split("|");
        geometry = record.at(i++).toString();
        protocolId = record.at(i++).toInt();
        blankTime = record.at(i++).toInt();
        sourceTime = record.at(i++).toInt();
        repeat = record.at(i++).toInt();
        linked = record.at(i++).toString();
        category = record.at(i++).toString();
        comments = record.at(i++).toString();
        authorId = record.at(i++).toInt();
        acceptedId = record.at(i++).toInt();
        acceptedDateTime = record.at(i++).toString();
        lastModification = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }
    QVariantList record()const {
        QVariantList ret;
        ret << id
            << systemLabel
            << measurementId
            << measurementDate
            << nuclide
            << sourceId
            << geometry
            << protocolId
            << blankTime
            << sourceTime
            << repeat
            << linked
            << category
            << comments
            << authorId
            << acceptedId
            << acceptedDateTime
            << lastModification
            << userId;
        return ret;
    }
};

#endif // CRYSTALMEASUREMENTREGISTERMODEL_H
