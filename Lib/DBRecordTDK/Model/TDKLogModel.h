#ifndef TDKLOGMODEL_H
#define TDKLOGMODEL_H
#include "idatabasemodel.h"
namespace StarlingLab {
class TDKLogModel : public IDatabaseModel
{
public:
    QString nuclide;
    QString creationDateTime;
    QString measurementObject;
    QString description;
    QString linked;
    int madeByUserId;
    int status;

    IDatabaseModel* copy() {
        IDatabaseModel* ret = new TDKLogModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName() const {
        return QString("tdklog");
    }

    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        nuclide = record.at(i++).toString();
        creationDateTime = record.at(i++).toString();
        measurementObject = record.at(i++).toString();
        description = record.at(i++).toString();
        linked = record.at(i++).toString();
        madeByUserId = record.at(i++).toInt();
        status = record.at(i++).toInt();
        timestamp = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }

    QVariantList record() const {
        QVariantList ret;
        ret << id
            << nuclide
            << creationDateTime
            << measurementObject
            << description
            << linked
            << madeByUserId
            << status
            << timestamp
            << userId;
        return ret;
    }
};
}
#endif // TDKLOGMODEL_H
