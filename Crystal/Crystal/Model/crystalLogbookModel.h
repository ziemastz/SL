#ifndef CRYSTALLOGBOOKMODEL_H
#define CRYSTALLOGBOOKMODEL_H
#include "dbcrystal.h"
class CrystalLogbookModel : public BaseModel
{
public:
    QString type;
    QString description;
    QString root;
    QString element;

    BaseModel* copy() {
        BaseModel* ret = new CrystalLogbookModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("crystalLogbook");
    }
    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        type = record.at(i++).toString();
        description = record.at(i++).toString();
        root = record.at(i++).toString();
        element = record.at(i++).toString();
        lastModification = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }

    QVariantList record()const {
        QVariantList ret;
        ret << id
            << type
            << description
            << root
            << element
            << lastModification
            << userId;
        return ret;
    }
};
#endif // CRYSTALLOGBOOKMODEL_H
