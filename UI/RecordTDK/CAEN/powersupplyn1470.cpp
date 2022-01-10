#include "powersupplyn1470.h"
QString PowerSupplyN1470::_port = QString("COM1");
QString PowerSupplyN1470::_baudRate = QString("115200");
QString PowerSupplyN1470::_lBusAddress = QString("0");

PowerSupplyN1470::PowerSupplyN1470()
{
    _isConnect = connect();
    refresh();
    _voltCh0 = getVolt(CH0);
    _voltCh1 = getVolt(CH1);
    _voltCh2 = getVolt(CH2);
    _voltCh3 = getVolt(CH3);
}

PowerSupplyN1470::~PowerSupplyN1470()
{
    disconnect();
}

void PowerSupplyN1470::setPort(const QString &newPort)
{
    _port = newPort;
}

void PowerSupplyN1470::setBaudRate(const QString &newBaudRate)
{
    _baudRate = newBaudRate;
}

void PowerSupplyN1470::setLBusAddress(const QString &newLBusAddress)
{
    _lBusAddress = newLBusAddress;
}

QString PowerSupplyN1470::lastError()
{
    QString ret = _lastError;
    _lastError.clear();
    return ret;
}

bool PowerSupplyN1470::setTurnOff(const CHANNEL &ch)
{
    if(!_isConnect)
        return false;

    unsigned long val = 0;
    res = CAENHV_SetChParam(handle,0,"Pw",1,&chList[ch],&val);
    if(res == CAENHV_OK) {
        return true;
    }else {
        _lastError = QString(CAENHV_GetError(handle));
        return false;
    }
}

bool PowerSupplyN1470::setTurnOn(const CHANNEL &ch)
{
    if(!_isConnect)
        return false;

    unsigned long val = 1;
    res = CAENHV_SetChParam(handle,0,"Pw",1,&chList[ch],&val);
    if(res == CAENHV_OK) {
        return true;
    }else {
        _lastError = QString(CAENHV_GetError(handle));
        return false;
    }
}

bool PowerSupplyN1470::isTurnOn(const CHANNEL &ch)
{
    if(!_isConnect)
        return false;

    unsigned long val = 0;
    res = CAENHV_GetChParam(handle,0,"Pw",1,&chList[ch],&val);
    if(res == CAENHV_OK) {
        return val;
    }else {
        _lastError = QString(CAENHV_GetError(handle));
        return val;
    }
}

bool PowerSupplyN1470::setVolt(float voltage, const CHANNEL &ch)
{
    if(!_isConnect)
        return false;

    res = CAENHV_SetChParam(handle,0,"VSet",1,&chList[ch],&voltage);
    if(res == CAENHV_OK) {
        return true;
    }else {
        _lastError = QString(CAENHV_GetError(handle));
        return false;
    }
}

float PowerSupplyN1470::monVolt(const CHANNEL &ch)
{
    float ret = -1;
    if(!_isConnect)
        return ret;

    res = CAENHV_GetChParam(handle,0,"VMon",1,&chList[ch],&ret);
    if(res == CAENHV_OK) {
        return ret;
    }else {
        _lastError = QString(CAENHV_GetError(handle));
        return ret;
    }
}

float PowerSupplyN1470::getVolt(const CHANNEL &ch)
{
    float ret = -1;
    if(!_isConnect)
        return ret;

    res = CAENHV_GetChParam(handle,0,"VSet",1,&chList[ch],&ret);
    if(res == CAENHV_OK) {
        return ret;
    }else {
        _lastError = QString(CAENHV_GetError(handle));
        return ret;
    }
}

QString PowerSupplyN1470::monStatus(const CHANNEL &ch)
{
    QString ret;
    if(!_isConnect)
        return ret;

    unsigned long value;
    res = CAENHV_GetChParam(handle,0,"ChStatus",1,&chList[ch],&value);
    if(res == CAENHV_OK) {
        std::bitset<32> bitfield = std::bitset<32>(value);

        if(bitfield[0]){
            ret.append("ON");
        }else {
            ret.append("OFF");
        }
        if(bitfield[1])
            ret.append("|Ramping Up");
        if(bitfield[2])
            ret.append("|Ramping Down");
        if(bitfield[3])
            ret.append("|In Overcurrent");
        if(bitfield[4])
            ret.append("|In Overvoltage");
        if(bitfield[5])
            ret.append("|In Undervoltage");
        if(bitfield[6])
            ret.append("|In External Trip");
        if(bitfield[7])
            ret.append("|In Max V");
        if(bitfield[8])
            ret.append("|In External Disable");
        if(bitfield[9])
            ret.append("|In Internal Trip");
        if(bitfield[10])
            ret.append("|In Calibration Error");
        if(bitfield[11])
            ret.append("|Unplugged");
        if(bitfield[13])
            ret.append("|In OverVoltage Protection");
        if(bitfield[14])
            ret.append("|In Power Fail");
        if(bitfield[15])
            ret.append("|In Temperature Error");
        return ret;
    }else {
        _lastError = QString(CAENHV_GetError(handle));
        return ret;
    }
}

void PowerSupplyN1470::refresh()
{
    _isTurnOnCh0 = isTurnOn(CH0);
    _isTurnOnCh1 = isTurnOn(CH1);
    _isTurnOnCh2 = isTurnOn(CH2);
    _isTurnOnCh3 = isTurnOn(CH3);
    _monVoltCh0 = monVolt(CH0);
    _monVoltCh1 = monVolt(CH1);
    _monVoltCh2 = monVolt(CH2);
    _monVoltCh3 = monVolt(CH3);
    _statusCh0 = monStatus(CH0);
    _statusCh1 = monStatus(CH1);
    _statusCh2 = monStatus(CH2);
    _statusCh3 = monStatus(CH3);
}

void PowerSupplyN1470::setTurnCh0(const bool &turnOn)
{
    if(turnOn)
        setTurnOn(CH0);
    else
        setTurnOff(CH0);
}

void PowerSupplyN1470::setTurnCh1(const bool &turnOn)
{
    if(turnOn)
        setTurnOn(CH1);
    else
        setTurnOff(CH1);
}

void PowerSupplyN1470::setTurnCh2(const bool &turnOn)
{
    if(turnOn)
        setTurnOn(CH2);
    else
        setTurnOff(CH2);
}

void PowerSupplyN1470::setTurnCh3(const bool &turnOn)
{
    if(turnOn)
        setTurnOn(CH3);
    else
        setTurnOff(CH3);
}

void PowerSupplyN1470::setVoltCh0(const double &volt)
{
    if(setVolt((float)volt,CH0))
        _voltCh0 = volt;
}

void PowerSupplyN1470::setVoltCh1(const double &volt)
{
    if(setVolt((float)volt,CH1))
        _voltCh1 = volt;
}

void PowerSupplyN1470::setVoltCh2(const double &volt)
{
    if(setVolt((float)volt,CH2))
        _voltCh2 = volt;
}

void PowerSupplyN1470::setVoltCh3(const double &volt)
{
    if(setVolt((float)volt,CH3))
        _voltCh3 = volt;
}

bool PowerSupplyN1470::connect()
{
    strcpy(arg,QString(_port+"_"+_baudRate+"_8BIT_NONE_1_"+_lBusAddress).toLocal8Bit().data());
    strcpy(userName,"admin");
    strcpy(passwd,"admin");

    res = CAENHV_InitSystem(systemType,linkType,arg,userName,passwd,&handle);

    if(res == CAENHV_OK) {
        return true;
    }else{
        _lastError = QString(CAENHV_GetError(handle));
        return false;
    }
}

void PowerSupplyN1470::disconnect()
{
    res = CAENHV_DeinitSystem(handle);
    if(res != CAENHV_OK)
        _lastError = QString(CAENHV_GetError(handle));
}

bool PowerSupplyN1470::isConnect() const
{
    return _isConnect;
}

float PowerSupplyN1470::voltCh3() const
{
    return _voltCh3;
}

float PowerSupplyN1470::voltCh2() const
{
    return _voltCh2;
}

float PowerSupplyN1470::voltCh1() const
{
    return _voltCh1;
}

float PowerSupplyN1470::voltCh0() const
{
    return _voltCh0;
}

float PowerSupplyN1470::monVoltCh3() const
{
    return _monVoltCh3;
}

float PowerSupplyN1470::monVoltCh2() const
{
    return _monVoltCh2;
}

float PowerSupplyN1470::monVoltCh1() const
{
    return _monVoltCh1;
}

float PowerSupplyN1470::monVoltCh0() const
{
    return _monVoltCh0;
}

const QString &PowerSupplyN1470::statusCh3() const
{
    return _statusCh3;
}

const QString &PowerSupplyN1470::statusCh2() const
{
    return _statusCh2;
}

const QString &PowerSupplyN1470::statusCh1() const
{
    return _statusCh1;
}

const QString &PowerSupplyN1470::statusCh0() const
{
    return _statusCh0;
}

bool PowerSupplyN1470::isTurnOnCh3() const
{
    return _isTurnOnCh3;
}

bool PowerSupplyN1470::isTurnOnCh2() const
{
    return _isTurnOnCh2;
}

bool PowerSupplyN1470::isTurnOnCh1() const
{
    return _isTurnOnCh1;
}

bool PowerSupplyN1470::isTurnOnCh0() const
{
    return _isTurnOnCh0;
}
