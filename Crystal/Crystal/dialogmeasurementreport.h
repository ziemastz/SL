#ifndef DIALOGMEASUREMENTREPORT_H
#define DIALOGMEASUREMENTREPORT_H

#include <QDialog>
#include <QMessageBox>
#include <QMap>

#include "dbcrystal.h"
#include "utils.h"
#include "statistics.h"

namespace Ui {
class DialogMeasurementReport;
}

class DialogMeasurementReport : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMeasurementReport(const QString &measId, QWidget *parent = nullptr);
    ~DialogMeasurementReport();
public slots:
    void load();

private:
    Ui::DialogMeasurementReport *ui;
    QString _measId;
    CrystalMeasurementRegisterModel reg;
};

#endif // DIALOGMEASUREMENTREPORT_H
