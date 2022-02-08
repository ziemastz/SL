#ifndef COUNTER_H
#define COUNTER_H
#include <QDebug>
#include <QDateTime>
#include "mac3counter.h"
#include "counts.h"

class Counter
{
public:
    Counter(MAC3Counter *pMAC3);
    ~Counter();
    bool isConnect() const;
    QString lastError();

    void start();
    void stop();
    void reset();
    void readData();

    double cpsA();
    double cpsB();
    double cpsC();

    double cpsS();

    double cpsAB();
    double cpsBC();
    double cpsAC();

    double cpsT();
    double cpsD();

    double liveTime();
    double realTime();
    double deadTime();

    int rel1();
    int rel2();

    QDateTime startDateTime() const;
    const Counts &getCounts() const;

    void setCounts(const Counts &newCounts);

private:
    bool _isConnect;
    QDateTime _startDateTime;

    MAC3Counter *mac3;

    Counts counts;
    double cps(const unsigned int& port);
    const double freqLT = 1000; //1kHz - 1s
};

#endif // COUNTER_H
