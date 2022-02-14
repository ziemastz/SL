#ifndef DBCRYSTAL_H
#define DBCRYSTAL_H

#include <QObject>
#include "sldatabase.h"

#include "Model/crystalMeasurementProtocolModel.h"
#include "Model/crystalMeasurementRegisterModel.h"
#include "Model/crystalMeasuringSystemModel.h"
#include "Model/crystalProtocolModel.h"
#include "Model/crystalSettingsModel.h"

class DBCrystal : public SLDatabase
{
public:
    DBCrystal();

signals:

};

#endif // DBCRYSTAL_H
