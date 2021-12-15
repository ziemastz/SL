#ifndef ADDMEASUREMENTDIALOG_H
#define ADDMEASUREMENTDIALOG_H
#include <QDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QListWidget>
#include "protocoldialog.h"

#include "dbrecordtdk.h"

namespace Ui {
class AddMeasurementDialog;
}

class AddMeasurementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddMeasurementDialog(QWidget *parent = nullptr);
    ~AddMeasurementDialog();


    const StarlingLab::TDKLogModel &getLog() const;
    void setLog(const StarlingLab::TDKLogModel &newLog);

private slots:
    void on_cancel_pushButton_clicked();

    void on_start_pushButton_clicked();

    void on_addProtocol_pushButton_clicked();

    void on_editProtocol_pushButton_clicked();

    void on_searchProtocol_lineEdit_textChanged(const QString &arg1);

private:
    Ui::AddMeasurementDialog *ui;
    StarlingLab::TDKLogModel log;
};

#endif // ADDMEASUREMENTDIALOG_H
