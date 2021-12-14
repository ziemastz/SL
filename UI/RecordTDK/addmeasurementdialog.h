#ifndef ADDMEASUREMENTDIALOG_H
#define ADDMEASUREMENTDIALOG_H
#include "dbrecordtdk.h"
#include <QDialog>

namespace Ui {
class AddMeasurementDialog;
}

class AddMeasurementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddMeasurementDialog(QWidget *parent = nullptr);
    ~AddMeasurementDialog();

private slots:
    void on_cancel_pushButton_clicked();

    void on_start_pushButton_clicked();

    void on_addProtocol_pushButton_clicked();

    void on_editProtocol_pushButton_clicked();

    void on_searchProtocol_lineEdit_textChanged(const QString &arg1);

private:
    Ui::AddMeasurementDialog *ui;
};

#endif // ADDMEASUREMENTDIALOG_H
