#ifndef CRYSTALSETTINGSMODEL_H
#define CRYSTALSETTINGSMODEL_H
#include "dbcrystal.h"
class CrystalSettingModel : public BaseModel
{
public:
    int blankTime;
    int sourceTime;
    int repeat;
    QString deviceName;

    BaseModel *copy() {
        CrystalSettingModel *ret = new CrystalSettingModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("crystalSettings");
    }
    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        blankTime = record.at(i++).toInt();
        sourceTime = record.at(i++).toInt();
        repeat = record.at(i++).toInt();
        deviceName = record.at(i++).toString();
        lastModification = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }
    QVariantList record()const {
        QVariantList ret;
        ret << id
            << blankTime
            << sourceTime
            << repeat
            << deviceName
            << lastModification
            << userId;
        return ret;
    }
};

#endif // CRYSTALSETTINGSMODEL_H
