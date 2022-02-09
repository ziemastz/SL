#ifndef DIALOGMEASUREMENTREPORT_H
#define DIALOGMEASUREMENTREPORT_H

#include <QDialog>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>

#include "utils.h"
#include "databasestarlinglab.h"
#include "counter.h"
#include "settings.h"
#include "reportgenerator.h"

namespace Ui {
class DialogMeasurementReport;
}

class DialogMeasurementReport : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMeasurementReport(const TripleRegMeasurementRegisterModel &measReg, QWidget *parent = nullptr);
    ~DialogMeasurementReport();
public slots:
    void load();

private slots:
    void on_cancel_pushButton_clicked();

    void on_cps_radioButton_toggled(bool checked);

    void on_modify_pushButton_toggled(bool checked);

    void on_save_pushButton_clicked();

    void on_approveMeasurement_pushButton_clicked();

    void on_remove_pushButton_clicked();

    void on_export_pushButton_clicked();

private:
    Ui::DialogMeasurementReport *ui;
    TripleRegMeasurementRegisterModel _reg;
    TripleRegMeasurementProtocolModel _protocol;
    QVector<QStringList> _counts;

};

#endif // DIALOGMEASUREMENTREPORT_H
