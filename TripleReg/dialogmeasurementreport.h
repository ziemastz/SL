#ifndef DIALOGMEASUREMENTREPORT_H
#define DIALOGMEASUREMENTREPORT_H

#include <QDialog>

namespace Ui {
class DialogMeasurementReport;
}

class DialogMeasurementReport : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMeasurementReport(QWidget *parent = nullptr);
    ~DialogMeasurementReport();

private:
    Ui::DialogMeasurementReport *ui;
};

#endif // DIALOGMEASUREMENTREPORT_H
