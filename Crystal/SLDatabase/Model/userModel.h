#ifndef USERMODEL_H
#define USERMODEL_H
#include "baseModel.h"
class UserModel : public BaseModel
{
public:
    QString username;
    QString password;
    QString email;
    QString degree;
    QString firstName;
    QString secondName;
    QString lastName;
    QString position;
    bool isActive;
    QByteArray signature;

    BaseModel *copy() {
        UserModel *ret = new UserModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("user");
    }
    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        username = record.at(i++).toString();
        password = record.at(i++).toString();
        email = record.at(i++).toString();
        degree = record.at(i++).toString();
        firstName = record.at(i++).toString();
        secondName = record.at(i++).toString();
        lastName = record.at(i++).toString();
        position = record.at(i++).toString();
        isActive = record.at(i++).toBool();
        signature = record.at(i++).toByteArray();
        lastModification = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }
    QVariantList record()const {
        QVariantList ret;
        ret << id
            << username
            << password
            << email
            << degree
            << firstName
            << secondName
            << lastName
            << position
            << isActive
            << signature
            << lastModification
            << userId;
        return ret;
    }

    QString caption()const {
        if(firstName.isEmpty())
            return QString();
        QString ret;
        if(!degree.isEmpty()) {
            ret = degree;
            ret.append(" ").append(firstName);
        }else {
            ret = firstName;
        }

        if(!secondName.isEmpty())
            ret.append(" ").append(secondName.at(0)).append(".");
        ret.append(" ").append(lastName);
        return ret;
    }
    QString captionShort()const {
        if(firstName.isEmpty())
            return QString();
        QString ret = firstName.at(0);
        ret.append(".");
        if(!secondName.isEmpty())
            ret.append(" ").append(secondName.at(0)).append(".");
        ret.append(" ").append(lastName);
        return ret;
    }
};

#endif // USERMODEL_H
