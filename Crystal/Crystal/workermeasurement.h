#ifndef WORKERMEASUREMENT_H
#define WORKERMEASUREMENT_H
#include <QObject>
#include "dbcrystal.h"
#include "counter.h"
class WorkerMeasurement : public QObject
{
public:
    WorkerMeasurement(const NaICounter::PORT &port, Counter *counter);

signals:
    void setNuclide(const QString &nuclide);
    void setSourceId(const QString &sourceId);
    void setGeometry(const QString &geometry);
    void setProcess(const QString &process);
    void setCurrentRepeat(const int &value);
    void setRepeat(const int &value);
    void setEndTime(const QString &endTime);
    void setActivity(const double &value);
    void setCounts(const double &value);
    void setDeadTime(const double &value);

public slots:
    void startNewMeasurement(int registerId);

private:
    NaICounter::PORT _port;
    Counter *_counter;
};

#endif // WORKERMEASUREMENT_H
