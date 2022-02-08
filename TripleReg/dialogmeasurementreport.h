#ifndef DIALOGMEASUREMENTREPORT_H
#define DIALOGMEASUREMENTREPORT_H

#include <QDialog>
#include <QMessageBox>

#include "utils.h"
#include "databasestarlinglab.h"
#include "counter.h"

namespace Ui {
class DialogMeasurementReport;
}

class DialogMeasurementReport : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMeasurementReport(const TripleRegMeasurementRegisterModel &measReg, QWidget *parent = nullptr);
    ~DialogMeasurementReport();

private slots:
    void on_cancel_pushButton_clicked();

    void on_cps_radioButton_toggled(bool checked);

    void on_modify_pushButton_toggled(bool checked);

private:
    Ui::DialogMeasurementReport *ui;
    TripleRegMeasurementRegisterModel _reg;

    void load();
};

#endif // DIALOGMEASUREMENTREPORT_H
