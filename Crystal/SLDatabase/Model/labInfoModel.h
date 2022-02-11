#ifndef LABINFOMODEL_H
#define LABINFOMODEL_H
#include "baseModel.h"
class LabInfoModel : public BaseModel
{
public:
    QString institute;
    QString deparment;
    QString lab;
    QString addressLine1;
    QString addressLine2;
    QString zip;
    QString city;
    QString country;
    QString phone;
    QString email;

    BaseModel* copy() {
        BaseModel* ret = new LabInfoModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("labInfo");
    }
    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        institute = record.at(i++).toString();
        deparment = record.at(i++).toString();
        lab = record.at(i++).toString();
        addressLine1 = record.at(i++).toString();
        addressLine2 = record.at(i++).toString();
        zip = record.at(i++).toString();
        city = record.at(i++).toString();
        country = record.at(i++).toString();
        phone = record.at(i++).toString();
        email = record.at(i++).toString();
        lastModification = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }

    QVariantList record()const {
        QVariantList ret;
        ret << id
            << institute
            << deparment
            << lab
            << addressLine1
            << addressLine2
            << zip
            << city
            << country
            << phone
            << email
            << lastModification
            << userId;
        return ret;
    }
};

#endif // LABINFOMODEL_H
