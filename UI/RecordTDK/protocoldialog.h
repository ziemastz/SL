#ifndef PROTOCOLDIALOG_H
#define PROTOCOLDIALOG_H

#include <QDialog>
#include "voltagetabledialog.h"
#include "dbrecordtdk.h"

namespace Ui {
class ProtocolDialog;
}

class ProtocolDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProtocolDialog(QWidget *parent = nullptr);
    ~ProtocolDialog();
    void setName(const QString& name);
    StarlingLab::ProtocolModel getData();

    void setData(const StarlingLab::ProtocolModel &newData);

private slots:
    void on_cancel_pushButton_clicked();

    void on_save_pushButton_clicked();

    void on_tabVoltage_checkBox_stateChanged(int arg1);

    void on_tabVoltage_pushButton_clicked();

private:
    Ui::ProtocolDialog *ui;
    VoltageTableDialog tableDialog;
    StarlingLab::ProtocolModel data;
};

#endif // PROTOCOLDIALOG_H
