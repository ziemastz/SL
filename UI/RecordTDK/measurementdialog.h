#ifndef MEASUREMENTDIALOG_H
#define MEASUREMENTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QTimer>
#include "dbrecordtdk.h"
#include "CAEN/powersupplyn1470.h"
#include "mac3counter.h"

namespace Ui {
class MeasurementDialog;
}

class MeasurementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MeasurementDialog(const StarlingLab::TDKLogModel& log, QWidget *parent = nullptr);
    ~MeasurementDialog();

private:
    Ui::MeasurementDialog *ui;
    StarlingLab::TDKLogModel _log;
    StarlingLab::ProtocolModel _protocol;

    PowerSupplyN1470 *n1470;
    MAC3Counter *mac3;
    QTimer *timer;

    void loadData();
    bool initConnection();
    void initMeasurement();
};

#endif // MEASUREMENTDIALOG_H
