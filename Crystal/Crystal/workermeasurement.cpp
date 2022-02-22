#include "workermeasurement.h"

WorkerMeasurement::WorkerMeasurement(const NaICounter::PORT &port, Counter *counter)
{
    _port = port;
    _counter = counter;
}

void WorkerMeasurement::startNewMeasurement(int registerId)
{
    DBCrystal db;
    CrystalMeasurementRegisterModel reg;
    if(!db.select(registerId,&reg)) {
        emit msgBox(tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."),_port);
        return;
    }

}
