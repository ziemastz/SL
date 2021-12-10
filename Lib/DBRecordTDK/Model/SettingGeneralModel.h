#ifndef SETTINGGENERALMODEL_H
#define SETTINGGENERALMODEL_H
#include "idatabasemodel.h"
namespace StarlingLab {
class SettingGeneralModel : public IDatabaseModel
{
public:
    //int id;
    int blankTime;
    int sourceTime;
    int repeated;
    int delayedStart;
    int voltageMax;
    int amperMax;

    //QString timestamp;
    //int userId;

    IDatabaseModel* copy() {
        SettingGeneralModel *ret = new SettingGeneralModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("settingGeneral");
    }
    void setRecord(const QVariantList& record) {
        int i=0;
        id = record.at(i++).toInt();
        blankTime = record.at(i++).toInt();
        sourceTime = record.at(i++).toInt();
        repeated = record.at(i++).toInt();
        delayedStart = record.at(i++).toInt();
        voltageMax = record.at(i++).toInt();
        amperMax = record.at(i++).toInt();
        timestamp = record.at(i++).toString();
        userId = record.at(i++).toInt();
    }
    QVariantList record()const {
        QVariantList ret;
        ret << id
            << blankTime
            << sourceTime
            << repeated
            << delayedStart
            << voltageMax
            << amperMax
            << timestamp
            << userId;
        return ret;
    }
};
}
#endif // SETTINGGENERALMODEL_H
