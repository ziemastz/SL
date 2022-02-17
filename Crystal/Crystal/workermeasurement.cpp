#include "workermeasurement.h"

WorkerMeasurement::WorkerMeasurement(const NaICounter::PORT &port, Counter *counter)
{
    _port = port;
    _counter = counter;
}

void WorkerMeasurement::startNewMeasurement(int registerId)
{

}
