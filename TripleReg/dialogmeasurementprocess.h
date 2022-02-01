#ifndef DIALOGMEASUREMENTPROCESS_H
#define DIALOGMEASUREMENTPROCESS_H

#include <QDialog>
#include <QMessageBox>

#include "databasestarlinglab.h"

#include "dialogpowersupplyprocess.h"
#include "utils.h"

namespace Ui {
class DialogMeasurementProcess;
}

class DialogMeasurementProcess : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMeasurementProcess(const TripleRegMeasurementRegisterModel &measurementRegister, QWidget *parent = nullptr);
    ~DialogMeasurementProcess();
signals:
    void acceptedMessageBox();
    void rejectedMessageBox();
    void abortedPowerSupplyProcessBox();

public slots:
    void setMeasurementObject(const QString &nuclide, const QString &solutionId, const QString &sourceId);
    void setParameter(const int &maxSourceNo, const int &maxPoint, const int &maxRepeat, const int &maxTime);

    void setTimeLeft(const int &timeLeft);
    void setEndTime(const QString &endTime);

    void setCurrentSource(const int &val);
    void setCurrentPoint(const int &val);
    void setCurrentRepeat(const int &val);
    void setCurrentTime(const int &val);

    void addRecord(const QStringList &record, const QStringList &fullRecord);
    void updateLastRecord(const QStringList &record, const QStringList &fullRecord);

    void showMessageBox(const QString &title, const QString &text);

    void showPowerSupplyProcessBox();
    void hidePowerSupplyProcessBox();
    void setSetupHVPowerSupplyProcess(const int &maxVoltage);
    void setStabilizationPowerSupplyProcess(const int &startDelay);
    void setCurrentStatusPowerSupplyProcess(const int &val);

private slots:
    void on_showMore1_checkBox_stateChanged(int arg1);

private:
    Ui::DialogMeasurementProcess *ui;
    DialogPowerSupplyProcess powerSupplyProcessBox;


};

#endif // DIALOGMEASUREMENTPROCESS_H
