#ifndef TRIPLEREGMEASUREMENTRAWMODEL_H
#define TRIPLEREGMEASUREMENTRAWMODEL_H
#include "baseModel.h"
class TripleRegMeasurementRAWModel : public BaseModel
{
public:
    int measurementId;
    QString startMeasurementDateTime;
    int sourceNo;
    QString pointTag;
    int repeat;
    unsigned int A;
    unsigned int B;
    unsigned int C;

    unsigned int S;

    unsigned int AB;
    unsigned int BC;
    unsigned int AC;

    unsigned int T;
    unsigned int D;

    unsigned int LT;
    unsigned int CLK_IN;

    double voltageCh0;
    double voltageCh1;
    double voltageCh2;
    double voltageCh3;

    BaseModel* copy() {
        BaseModel* ret = new TripleRegMeasurementRAWModel;
        ret->setRecord(this->record());
        return ret;
    }

    QString tableName()const {
        return QString("tripleRegMeasurementRAW");
    }
    void setRecord(const QVariantList &record) {
        int i = 0;
        id = record.at(i++).toInt();
        measurementId = record.at(i++).toInt();
        startMeasurementDateTime = record.at(i++).toString();
        sourceNo = record.at(i++).toInt();
        pointTag = record.at(i++).toString();
        repeat = record.at(i++).toInt();
        A = record.at(i++).toUInt();
        B = record.at(i++).toUInt();
        C = record.at(i++).toUInt();
        S = record.at(i++).toUInt();
        AB = record.at(i++).toUInt();
        BC = record.at(i++).toUInt();
        AC = record.at(i++).toUInt();
        T = record.at(i++).toUInt();
        D = record.at(i++).toUInt();
        LT = record.at(i++).toUInt();
        CLK_IN = record.at(i++).toUInt();
        voltageCh0 = record.at(i++).toDouble();
        voltageCh1 = record.at(i++).toDouble();
        voltageCh2 = record.at(i++).toDouble();
        voltageCh3 = record.at(i++).toDouble();
        lastModification = record.at(i++).toString();
        userId = record.at(i++).toInt();

    }

    QVariantList record() const {
        QVariantList ret;
        ret << id
            << measurementId
            << startMeasurementDateTime
            << sourceNo
            << pointTag
            << repeat
            << A
            << B
            << C
            << S
            << AB
            << BC
            << AC
            << T
            << D
            << LT
            << CLK_IN
            << voltageCh0
            << voltageCh1
            << voltageCh2
            << voltageCh3
            << lastModification
            << userId;
        return ret;
    }  
};

#endif // TRIPLEREGMEASUREMENTRAWMODEL_H
