#ifndef DBCRYSTAL_H
#define DBCRYSTAL_H

#include <QObject>
#include "sldatabase.h"

#include "Model/crystalMeasurementProtocolModel.h"
#include "Model/crystalMeasurementRegisterModel.h"
#include "Model/crystalMeasuringSystemModel.h"
#include "Model/crystalProtocolModel.h"
#include "Model/crystalSettingsModel.h"
#include "Model/crystalMeasurementRAWModel.h"
#include "Model/crystalLogbookModel.h"

class DBCrystal : public SLDatabase
{
public:
    DBCrystal();
    int countsMeasurement(const QString &systemNumber, const int &year);
    bool addCountsMeasurement(const QString &systemNumber, const int &year);
    bool increaseCountsMeasurement(const QString &systemNumber, const int &year);
    bool remove(CrystalMeasurementRegisterModel *model, const int &loggedUserId);
};

#endif // DBCRYSTAL_H
