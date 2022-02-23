#ifndef WORKERMEASUREMENT_H
#define WORKERMEASUREMENT_H
#include <QObject>
#include <QTimer>
#include "dbcrystal.h"
#include "counter.h"
#include "dialogmsgbox.h"
#include "utils.h"
#include "settings.h"

class WorkerMeasurement : public QObject
{
    Q_OBJECT
public:
    explicit WorkerMeasurement(const NaICounter::PORT &port, Counter *counter, QObject *parent = nullptr);

signals:
    void msgBox(const QString &title, const QString &text, const int &portId);

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
    void finished();

public slots:
    void startNewMeasurement(int registerId);
    void acceptedMsgBox(const int &portId);
    void rejectedMsgBox(const int &portId);
    void abortMeasurement(const int &portId);

private slots:
    void process();

private:
    enum SM_PROCESS {
        Blank,
        NextSource,
        PlacingVial,
        SettingPoint,
        NextPoint,
        Start,
        Measurement,
        Stop,
        Finished
    }stateProcess;

    NaICounter::PORT _port;
    Counter *_counter;
    QTimer *timer;

    CrystalMeasurementRegisterModel reg;
    CrystalMeasurementProtocolModel protocol;

    bool isBlank;
    int maxSource;
    int maxPoint;
    int maxRepeat;
    int maxTime;
    int currSource;
    int currPoint;
    int currRepeat;
    int currTime;

    QString generatorEndTime();
    QString generatorPointTag();

};

#endif // WORKERMEASUREMENT_H
