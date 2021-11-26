#ifndef USERMODEL_H
#define USERMODEL_H
#include "idatabasemodel.h"
namespace StarlingLab {
class UserModel : public IDatabaseModel
{
public:
    QString username;
    QString password;
    bool isActive;
    QString firstName;
    QString secondName;
    QString lastName;

    IDatabaseModel* copy() {
        IDatabaseModel *ret = new UserModel;
        ret->setRecord(record());
        return ret;
    }
    QString tableName()const {
        return QString("users");
    }
    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        username = record.at(i++).toString();
        password = record.at(i++).toString();
        isActive = record.at(i++).toBool();
        firstName = record.at(i++).toString();
        secondName = record.at(i++).toString();
        lastName = record.at(i++).toString();
        timestamp = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }
    QVariantList record()const {
        QVariantList ret;
        ret << id
            << username
            << password
            << isActive
            << firstName
            << secondName
            << lastName
            << timestamp
            << userId;
        return ret;
    }

    QString signature()const {
        QString ret = firstName;
        if(!secondName.isEmpty())
            ret.append(" ").append(secondName.at(0)).append(".");
        ret.append(" ").append(lastName);
        return ret;
    }
    QString signatureShort()const {
        QString ret = firstName.at(0);
        ret.append(".");
        if(!secondName.isEmpty())
            ret.append(" ").append(secondName.at(0)).append(".");
        ret.append(" ").append(lastName);
        return ret;
    }
};
}
#endif // USERMODEL_H
