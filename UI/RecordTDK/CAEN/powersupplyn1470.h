#ifndef POWERSUPPLYN1470_H
#define POWERSUPPLYN1470_H
#include <QObject>
#include <CAENHVWrapper/include/CAENHVWrapper.h>
#include <bitset>

class PowerSupplyN1470 : public QObject
{
    Q_OBJECT
public:
    enum CHANNEL {
        CH0 = 0,
        CH1 = 1,
        CH2 = 2,
        CH3 = 3
    };
    PowerSupplyN1470();
    ~PowerSupplyN1470();
    static void setPort(const QString &newPort);
    static void setBaudRate(const QString &newBaudRate);
    static void setLBusAddress(const QString &newLBusAddress);

    QString lastError();

    bool setTurnOff(const CHANNEL& ch);
    bool setTurnOn(const CHANNEL& ch);
    bool isTurnOn(const CHANNEL& ch);

    bool setVolt(float voltage, const CHANNEL& ch);
    float monVolt(const CHANNEL& ch);
    float getVolt(const CHANNEL& ch);

    QString monStatus(const CHANNEL& ch);

    bool isTurnOnCh0() const;

    bool isTurnOnCh1() const;

    bool isTurnOnCh2() const;

    bool isTurnOnCh3() const;

    const QString &statusCh0() const;

    const QString &statusCh1() const;

    const QString &statusCh2() const;

    const QString &statusCh3() const;

    float monVoltCh0() const;

    float monVoltCh1() const;

    float monVoltCh2() const;

    float monVoltCh3() const;

    float voltCh0() const;

    float voltCh1() const;

    float voltCh2() const;

    float voltCh3() const;

    bool isConnect() const;

public slots:
    void refresh();
    void setTurnCh0(const bool& turnOn);
    void setTurnCh1(const bool& turnOn);
    void setTurnCh2(const bool& turnOn);
    void setTurnCh3(const bool& turnOn);

    void setVoltCh0(const double& volt);
    void setVoltCh1(const double& volt);
    void setVoltCh2(const double& volt);
    void setVoltCh3(const double& volt);
private:
    static QString _port;
    static QString _baudRate;
    static QString _lBusAddress;

    bool connect();
    void disconnect();
    QString _lastError;
    bool _isConnect;

    CAENHVRESULT res;
    int handle;
    char arg[30], userName[20], passwd[20];

    const CAENHV_SYSTEM_TYPE_t systemType = N1470;
    const int linkType = LINKTYPE_USB_VCP;
    const unsigned short chList[4] = {0,1,2,3};

    float f[4];

    //status
    bool _isTurnOnCh0;
    bool _isTurnOnCh1;
    bool _isTurnOnCh2;
    bool _isTurnOnCh3;
    float _monVoltCh0;
    float _monVoltCh1;
    float _monVoltCh2;
    float _monVoltCh3;
    float _voltCh0;
    float _voltCh1;
    float _voltCh2;
    float _voltCh3;
    QString _statusCh0;
    QString _statusCh1;
    QString _statusCh2;
    QString _statusCh3;
};

#endif // POWERSUPPLYN1470_H
