#ifndef DIALOGMEASUREMENTREPORT_H
#define DIALOGMEASUREMENTREPORT_H

#include <QDialog>
#include <QMessageBox>
#include <QMap>
#include <QDir>
#include <QFileDialog>

#include "dbcrystal.h"
#include "utils.h"
#include "statistics.h"
#include "settings.h"
#include "reportgenerator.h"

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

private slots:
    void on_modify_pushButton_toggled(bool checked);

    void on_save_pushButton_clicked();

    void on_accept_pushButton_clicked();

    void on_remove_pushButton_clicked();

    void on_cancel_pushButton_clicked();

    void on_export_pushButton_clicked();

private:
    Ui::DialogMeasurementReport *ui;
    QString _measId;
    CrystalMeasurementRegisterModel reg;
    CrystalMeasurementProtocolModel protocol;
    QVector<QStringList> _counts;
};

#endif // DIALOGMEASUREMENTREPORT_H
