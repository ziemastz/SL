#ifndef DIALOGPROTOCOL_H
#define DIALOGPROTOCOL_H

#include <QDialog>
#include <QMessageBox>

#include "settings.h"
#include "dialogvoltagetable.h"
#include "databasestarlinglab.h"

namespace Ui {
class DialogProtocol;
}

class DialogProtocol : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProtocol(const QString &protocolName, QWidget *parent = nullptr);
    ~DialogProtocol();

private slots:
    void on_setUpTableVoltage_checkBox_stateChanged(int arg1);

    void on_copy_pushButton_clicked();

    void on_cancel_pushButton_clicked();

    void on_save_pushButton_clicked();

    void on_table_pushButton_clicked();

private:
    Ui::DialogProtocol *ui;
    DialogVoltageTable voltageTable;
    TripleRegProtocolModel protocol;

    void readProtocolName();
    void setParameter();
    void load(const QString &protocolName);
    void copyParameter(const QString &protocolName);

};

#endif // DIALOGPROTOCOL_H
