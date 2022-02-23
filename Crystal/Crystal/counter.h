#ifndef COUNTER_H
#define COUNTER_H
#include <QObject>
#include <QDebug>
#include <QDateTime>
#include "naicounter.h"
#include "dbcrystal.h"
class Counter
{
public:
    Counter();
    ~Counter();
    void setDeviceName(const QString &deviceName);
    bool isConnect() const;
public slots:
    void readData();
    bool setStart(const NaICounter::PORT &id);
    bool setStop(const NaICounter::PORT &id);
    bool setReset(const NaICounter::PORT &id);
    bool setDeadTime(const NaICounter::PORT &id, const double &value);

    bool startA();
    bool startB();
    bool startC();
    bool startD();

    bool stopA();
    bool stopB();
    bool stopC();
    bool stopD();

    bool resetA();
    bool resetB();
    bool resetC();
    bool resetD();

    unsigned int counts(const NaICounter::PORT &id) const;
    unsigned int countsA() const;
    unsigned int countsB() const;
    unsigned int countsC() const;
    unsigned int countsD() const;

    double cps(const NaICounter::PORT &id);
    double cpsA() const;
    double cpsB() const;
    double cpsC() const;
    double cpsD() const;

    unsigned int countsLiveTime(const NaICounter::PORT &id) const;
    double liveTimeA() const;
    double liveTimeB() const;
    double liveTimeC() const;
    double liveTimeD() const;

    unsigned int countsRealTime(const NaICounter::PORT &id) const;
    double realTime(const NaICounter::PORT &id);
    double realTimeA() const;
    double realTimeB() const;
    double realTimeC() const;
    double realTimeD() const;

    double deadTime(const NaICounter::PORT &id);
    double deadTimeA() const;
    double deadTimeB() const;
    double deadTimeC() const;
    double deadTimeD() const;

    QDateTime startDateTime(const NaICounter::PORT &id) const;


private:
    void connect();
    bool _isConnect;
    QString _deviceName;
    NaICounter nai;
    const double freq = 1000.0; //  freq = counts/ 1 second

    //counter
    unsigned int _countsA;
    unsigned int _countsB;
    unsigned int _countsC;
    unsigned int _countsD;

    unsigned int _liveTimeA;
    unsigned int _liveTimeB;
    unsigned int _liveTimeC;
    unsigned int _liveTimeD;

    unsigned int _realTimeA;
    unsigned int _realTimeB;
    unsigned int _realTimeC;
    unsigned int _realTimeD;

    QDateTime _startA;
    QDateTime _startB;
    QDateTime _startC;
    QDateTime _startD;

};

#endif // COUNTER_H
