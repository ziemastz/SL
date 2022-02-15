#include "counter.h"

Counter::Counter()
{
    DBCrystal db;
    CrystalSettingModel settings;
    if(db.select(1,&settings)) {
        _deviceName = settings.deviceName;
    }
    connect();
}

Counter::~Counter()
{
    nai.disconnect();
}

void Counter::connect()
{
    nai.setDeviceName(_deviceName.toStdString());
    nai.disconnect();
    _isConnect = nai.connect();
}
void Counter::setDeviceName(const QString &deviceName)
{
    _deviceName = deviceName;
    connect();
}

bool Counter::isConnect() const
{
    return _isConnect;
}

void Counter::readData()
{
    _countsA = nai.getCounts(NaICounter::PORT_A);
    _countsB = nai.getCounts(NaICounter::PORT_B);
    _countsC = nai.getCounts(NaICounter::PORT_C);
    _countsD = nai.getCounts(NaICounter::PORT_D);

    _liveTimeA = nai.getLiveTime(NaICounter::PORT_A);
    _liveTimeB = nai.getLiveTime(NaICounter::PORT_B);
    _liveTimeC = nai.getLiveTime(NaICounter::PORT_C);
    _liveTimeD = nai.getLiveTime(NaICounter::PORT_D);

    _realTimeA = nai.getRealTime(NaICounter::PORT_A);
    _realTimeB = nai.getRealTime(NaICounter::PORT_B);
    _realTimeC = nai.getRealTime(NaICounter::PORT_C);
    _realTimeD = nai.getRealTime(NaICounter::PORT_D);
}

bool Counter::startA()
{
    return setStart(NaICounter::PORT_A);
}

bool Counter::startB()
{
    return setStart(NaICounter::PORT_B);
}

bool Counter::startC()
{
    return setStart(NaICounter::PORT_C);
}

bool Counter::startD()
{
    return setStart(NaICounter::PORT_D);
}

bool Counter::stopA()
{
    return setStop(NaICounter::PORT_A);
}

bool Counter::stopB()
{
    return setStop(NaICounter::PORT_B);
}

bool Counter::stopC()
{
    return setStop(NaICounter::PORT_C);
}

bool Counter::stopD()
{
    return setStop(NaICounter::PORT_D);
}

bool Counter::resetA()
{
    return setReset(NaICounter::PORT_A);
}

bool Counter::resetB()
{
    return setReset(NaICounter::PORT_B);
}

bool Counter::resetC()
{
    return setReset(NaICounter::PORT_C);
}

bool Counter::resetD()
{
    return setReset(NaICounter::PORT_D);
}

unsigned int Counter::countsA() const
{
    return _countsA;
}

unsigned int Counter::countsB() const
{
    return _countsB;
}

unsigned int Counter::countsC() const
{
    return _countsC;
}

unsigned int Counter::countsD() const
{
    return _countsD;
}

double Counter::cpsA() const
{
    return (double)_countsA / liveTimeA();

}

double Counter::cpsB() const
{
    return (double)_countsB / liveTimeB();
}

double Counter::cpsC() const
{
    return (double)_countsC / liveTimeC();
}

double Counter::cpsD() const
{
    return (double)_countsD / liveTimeD();
}

double Counter::liveTimeA() const
{
    return (double)_liveTimeA / freq;
}

double Counter::liveTimeB() const
{
    return (double)_liveTimeB / freq;
}

double Counter::liveTimeC() const
{
    return (double)_liveTimeC / freq;
}

double Counter::liveTimeD() const
{
    return (double)_liveTimeD / freq;
}

double Counter::realTimeA() const
{
    return (double)_realTimeA / freq;
}

double Counter::realTimeB() const
{
    return (double)_realTimeB / freq;
}

double Counter::realTimeC() const
{
    return (double)_realTimeC / freq;
}

double Counter::realTimeD() const
{
    return (double)_realTimeD / freq;
}

double Counter::deadTimeA() const
{
    return 100 - (liveTimeA()*100/realTimeA());
}

double Counter::deadTimeB() const
{
    return 100 - (liveTimeB()*100/realTimeB());
}

double Counter::deadTimeC() const
{
    return 100 - (liveTimeC()*100/realTimeC());
}

double Counter::deadTimeD() const
{
    return 100 - (liveTimeD()*100/realTimeD());
}


bool Counter::setStart(const NaICounter::PORT &id)
{
    if(nai.setEnable(id,true) && nai.setReset(id,false)) {
        return true;
    }else{
        //message warning
        qWarning() << "Starting error!";
        return false;
    }
}

bool Counter::setStop(const NaICounter::PORT &id)
{
    if(nai.setEnable(id,false) && nai.setReset(id,false)) {
        return true;
    }else{
        //message warning
        qWarning() << "Stoping error!";
        return false;
    }
}

bool Counter::setReset(const NaICounter::PORT &id)
{
    if(nai.setEnable(id,false) && nai.setReset(id,true)) {
        return true;
    }else{
        //message warning
        qWarning() << "Stoping error!";
        return false;
    }
}
