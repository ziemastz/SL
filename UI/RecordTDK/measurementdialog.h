#ifndef MEASUREMENTDIALOG_H
#define MEASUREMENTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QTimer>
#include "dbrecordtdk.h"
#include "CAEN/powersupplyn1470.h"
#include "counter.h"
#include "mac3counter.h"

namespace Ui {
class MeasurementDialog;
}

class MeasurementDialog : public QDialog
{
    Q_OBJECT

public:
    enum MEASUREMENT_PROCESS {
        Init = 0,
        InitBlank,
        MeasureBlank,
        NextRepeatBlank,
        NextPointBlank,
        InitSource,
        MeasureSource,
        NextRepeatSource,
        NextPointSource,
        NextSource,
        Finished
    }currentStatus = Init;

    explicit MeasurementDialog(const StarlingLab::TDKLogModel& log, QWidget *parent = nullptr);
    ~MeasurementDialog();

private slots:
    void runMeasurement();
    void process();

private:
    Ui::MeasurementDialog *ui;
    StarlingLab::TDKLogModel _log;
    StarlingLab::ProtocolModel _protocol;
    StarlingLab::SettingGeneralModel _general;

    PowerSupplyN1470 *n1470;
    Counter *counter;
    MAC3Counter *mac3;
    QTimer *timer;

    void loadData();
    bool initConnection();
    void initMeasurement();

    int currentAnodeVoltage;
    int currentFocusingVoltage;
    int currentSource;
    int currentRepeat;

    void setVoltage(const int &anode, const int &focusing);
    void delayedStart();
    void updateRecord();

};

#endif // MEASUREMENTDIALOG_H
