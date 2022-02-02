#ifndef WORKERMEASUREMENTPROCESS_H
#define WORKERMEASUREMENTPROCESS_H

#include <QObject>
#include <QApplication>
#include <QMessageBox>
#include <QTimer>

#include "settings.h"
#include "databasestarlinglab.h"
#include "powersupplyn1470.h"
#include "counter.h"

class WorkerMeasurementProcess : public QObject
{
    Q_OBJECT
public:
    explicit WorkerMeasurementProcess(const TripleRegMeasurementRegisterModel &measurementRegister, QObject *parent = nullptr);
    ~WorkerMeasurementProcess();

signals:
    void finished();

    void setMeasurementObject(const QString &nuclide, const QString &solutionId, const QString &sourceId);
    void setParameter(const int &maxSourceNo, const int &maxPoint, const int &maxRepeat, const int &maxTime);

    void setTimeLeft(const int &timeLeft);
    void setEndTime(const QString &endTime);

    void setCurrentSource(const int &val);
    void setCurrentPoint(const int &val);
    void setCurrentRepeat(const int &val);
    void setCurrentTime(const int &val);

    void showPowerSupplyProcessBox();
    void hidePowerSupplyProcessBox();
    void setSetupHVPowerSupplyProcess(const int &maxVoltage);
    void setStabilizationPowerSupplyProcess(const int &startDelay);
    void setCurrentStatusPowerSupplyProcess(const int &val);

    void showMessageBox(const QString &title, const QString &text);

    void addRecord(const QStringList &record, const QStringList &fullRecord);
    void updateLastRecord(const QStringList &record, const QStringList &fullRecord);

public slots:
    void init();

    void acceptedMessageBox();
    void rejectedMessageBox();
    void abortedPowerSupplyProcessBox();

private slots:
    void process();

private:
    enum SM_PROCESS {
        Blank,
        NextSource,
        PlacingVial,
        SetupHV,
        Start,
        Measurement,
        Stop,
        Finished
    }stateProcess;

    PowerSupplyN1470 *n1470;
    Counter *counter;

    bool refreshN1470();
    bool refreshMAC3();
    bool turnOffPowerSupply();
    bool turnOnPowerSupply();
    bool stabilizationPowerSupply();

    TripleRegMeasurementRegisterModel _measurement;
    TripleRegMeasurementProtocolModel _protocol;
    QTimer *timer;

    bool isBlank;
    int maxSource;
    int maxPoint;
    int maxAnode;
    int maxFocusing;
    int maxRepeat;
    int maxTime;
    int currSource;
    int currPoint;
    int currAnode;
    int currFocusing;
    int currRepeat;
    int currTime;
    int startDelay;

    bool nextPoint();

    bool isAbort;

    QString generatorEndTime() const;
    int timeLeft() const;
    QString generatorPointTag() const;
    QStringList generatorRecord() const;
    QStringList generatorFullRecord() const;
    void setRAW(TripleRegMeasurementRAWModel *model);
};

#endif // WORKERMEASUREMENTPROCESS_H
