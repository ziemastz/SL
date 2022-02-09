#ifndef TRIPLEREGLOGBOOKMODEL_H
#define TRIPLEREGLOGBOOKMODEL_H
#include "baseModel.h"
class TripleRegLogbookModel : public BaseModel
{
public:
    QString type;
    QString description;
    QString root;
    QString element;

    BaseModel* copy() {
        BaseModel* ret = new TripleRegLogbookModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("tripleRegLogbook");
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

#endif // TRIPLEREGLOGBOOKMODEL_H
