#include "counter.h"

Counter::Counter()
{
    _isConnect = mac3.connect();
}

Counter::~Counter()
{
    mac3.disconnect();
}

bool Counter::isConnect() const
{
    return _isConnect;
}

QString Counter::lastError()
{
    return QString::fromStdString(mac3.lastError());
}

void Counter::start()
{
    if(mac3.enable() != MAC3Counter::ACTIVE) {
        _startDateTime = QDateTime::currentDateTime();
    }
    mac3.setEnable(true);
    mac3.setReset(false);
}

void Counter::stop()
{
    mac3.setEnable(false);
    mac3.setReset(false);   
}

void Counter::reset()
{
    mac3.setEnable(false);
    mac3.setReset(true);
}

void Counter::readData()
{
    counts.A = mac3.getPortCount(MAC3Counter::PORT_A);
    counts.B = mac3.getPortCount(MAC3Counter::PORT_B);
    counts.C = mac3.getPortCount(MAC3Counter::PORT_C);

    counts.S = mac3.getPortCount(MAC3Counter::PORT_S);

    counts.AB = mac3.getPortCount(MAC3Counter::PORT_AB);
    counts.BC = mac3.getPortCount(MAC3Counter::PORT_BC);
    counts.AC = mac3.getPortCount(MAC3Counter::PORT_AC);

    counts.T = mac3.getPortCount(MAC3Counter::PORT_T);
    counts.D = mac3.getPortCount(MAC3Counter::PORT_D);

    counts.LT = mac3.getPortCount(MAC3Counter::PORT_LT);
    counts.CLK_IN = mac3.getPortCount(MAC3Counter::PORT_CLK_IN);
}

double Counter::cpsA()
{
    return cps(counts.A);
}

double Counter::cpsB()
{
    return cps(counts.B);
}

double Counter::cpsC()
{
    return cps(counts.C);
}

double Counter::cpsS()
{
    return cps(counts.S);
}

double Counter::cpsAB()
{
    return cps(counts.AB);
}

double Counter::cpsBC()
{
    return cps(counts.BC);
}

double Counter::cpsAC()
{
    return cps(counts.AC);
}

double Counter::cpsT()
{
    return cps(counts.T);
}

double Counter::cpsD()
{
    return cps(counts.D);
}

double Counter::liveTime()
{
    //qDebug() << "Live-Time: " << ((double)counts.LT) / freqLT;
    return ((double)counts.LT) / freqLT;
}

double Counter::realTime()
{
    //qDebug() << "Real-time: " << ((double)counts.CLK_IN) / freqLT;
    return ((double)counts.CLK_IN) / freqLT;
}

double Counter::deadTime()
{
    //qDebug() << "DeadTime: " << realTime()-liveTime();
    return realTime()-liveTime();
}

int Counter::rel1()
{
    return counts.A + counts.B + counts.C - counts.S - counts.T - counts.D;
}

int Counter::rel2()
{
    return counts.AB + counts.BC + counts.AC - (2*counts.T) - counts.D;
}

QDateTime Counter::startDateTime() const
{
    return _startDateTime;
}

const Counts &Counter::getCounts() const
{
    return counts;
}

double Counter::cps(const unsigned int &port)
{
    return (double)port / ( ((double)counts.LT) / freqLT);
}
