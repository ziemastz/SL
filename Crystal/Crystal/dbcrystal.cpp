#include "dbcrystal.h"

DBCrystal::DBCrystal()
{
    setDatabaseName("crystal.db");
    setDriver("QSQLITE");
}

int DBCrystal::countsMeasurement(const QString &systemNumber, const int &year)
{
    exec("SELECT number FROM crystalMeasurementRegisterCounter WHERE year="+QString::number(year)+" AND systemNumber='"+systemNumber+"'");
    if(_records.count() == 1) {
        return _records.at(0).at(0).toInt();
    }else {
        return -1;
    }
}

bool DBCrystal::addCountsMeasurement(const QString &systemNumber, const int &year)
{
    return exec("INSERT INTO crystalMeasurementRegisterCounter VALUES("+QString::number(year)+", '"+systemNumber+"', 0)");
}

bool DBCrystal::increaseCountsMeasurement(const QString &systemNumber, const int &year)
{
    int current = countsMeasurement(systemNumber,year);
    if(current == -1)
        return false;
    current++;
    return exec("UPDATE crystalMeasurementRegisterCounter SET number="+QString::number(current)+" WHERE year="+QString::number(year)+" AND systemNumber='"+systemNumber+"'");
}
