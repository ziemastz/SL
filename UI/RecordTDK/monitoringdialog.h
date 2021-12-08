#ifndef MONITORINGDIALOG_H
#define MONITORINGDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QThread>
#include <QMessageBox>

#include "voltagetabledialog.h"
#include "counter.h"

#include "powersupplyn1470.h"

#include "dbrecordtdk.h"

namespace Ui {
class MonitoringDialog;
}

class MonitoringDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MonitoringDialog(const int& loggedUser, QWidget *parent = nullptr);
    ~MonitoringDialog();
    bool init();

private slots:
    void runOnlineMonitoring();
    void runMeasurement();

    void checkStatusN1470();

    void on_voltageTable_pushButton_clicked();
    void on_online_pushButton_toggled(bool checked);
    void on_start_pushButton_clicked();

    void on_channel0_radioButton_toggled(bool checked);

    void on_allChannel_radioButton_toggled(bool checked);

    void on_exit_pushButton_clicked();

    void on_clearData_pushButton_clicked();

    void on_saveData_pushButton_clicked();

    void on_channel1_radioButton_toggled(bool checked);

    void on_channel3_radioButton_toggled(bool checked);

    void on_channel2_radioButton_toggled(bool checked);

private:
    Ui::MonitoringDialog *ui;
    int _userLoggedId;
    VoltageTableDialog voltageTabDialog;

    PowerSupplyN1470 *n1470;
    QTimer *timer;
    QThread *threadN1470;

   // CounterLogModel log;
   // QVector<RAWModel> rawData;

    Counter counter;
    void updateRecord();
    void saveRecord();
    void addRecord();

    //onlineMonitoring
    const unsigned int samplingTime = 1; //second
    bool _isOnlineMonitoring;

    //measurement
    int _measurementTime;
    bool _isFinished;

    //power supply N1470
    void loadConnectionParam();
};

#endif // MONITORINGDIALOG_H
