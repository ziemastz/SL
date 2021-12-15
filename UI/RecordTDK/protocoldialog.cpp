#include "protocoldialog.h"
#include "ui_protocoldialog.h"

ProtocolDialog::ProtocolDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProtocolDialog)
{
    ui->setupUi(this);
}

ProtocolDialog::~ProtocolDialog()
{
    delete ui;
}

void ProtocolDialog::setName(const QString &name)
{
    ui->name_lineEdit->setText(name);
    ui->anodeVoltage_spinBox->setFocus();
}

StarlingLab::ProtocolModel ProtocolDialog::getData()
{
    data.name = ui->name_lineEdit->text();
    if(ui->tabVoltage_checkBox->isChecked()) {
        data.anodaVoltage = tableDialog.getAnodeTab();
        data.focusingVoltage = tableDialog.getFocusingTab();
    }else {
        data.anodaVoltage << ui->anodeVoltage_spinBox->value();
        data.focusingVoltage << ui->focusingVoltage_spinBox->value();

    }
    data.voltageShiftA = ui->voltageShiftA_spinBox->value();
    data.voltageShiftB = ui->voltageShiftB_spinBox->value();
    data.voltageShiftC = ui->voltageShiftC_spinBox->value();
    data.resolvingTime = ui->resolvingTime_spinBox->value();
    data.deadTime = ui->deadTime_spinBox->value();
    data.thrA = ui->thrA_doubleSpinBox->value();
    data.thrB = ui->thrB_doubleSpinBox->value();
    data.thrC = ui->thrC_doubleSpinBox->value();
    data.description = ui->description_lineEdit->text();
    return data;
}

void ProtocolDialog::on_cancel_pushButton_clicked()
{
    reject();
}


void ProtocolDialog::on_save_pushButton_clicked()
{
    accept();
}

void ProtocolDialog::setData(const StarlingLab::ProtocolModel &newData)
{
    data = newData;
    ui->name_lineEdit->setText(data.name);
    if(data.anodaVoltage.count() > 1 || data.focusingVoltage.count() > 1){
        ui->tabVoltage_checkBox->setChecked(true);
        tableDialog.setAnodeTab(data.anodaVoltage);
        tableDialog.setFocusingTab(data.focusingVoltage);
    }else {
        ui->tabVoltage_checkBox->setChecked(false);
    }
    ui->anodeVoltage_spinBox->setValue(data.anodaVoltage.at(0));
    ui->focusingVoltage_spinBox->setValue(data.focusingVoltage.at(0));
}


void ProtocolDialog::on_tabVoltage_checkBox_stateChanged(int arg1)
{
    if(arg1) {
        ui->anodeVoltage_spinBox->setEnabled(false);
        ui->focusingVoltage_spinBox->setEnabled(false);
        ui->tabVoltage_pushButton->setEnabled(true);
    }else {
        ui->anodeVoltage_spinBox->setEnabled(true);
        ui->focusingVoltage_spinBox->setEnabled(true);
        ui->tabVoltage_pushButton->setEnabled(false);
    }
}


void ProtocolDialog::on_tabVoltage_pushButton_clicked()
{
    tableDialog.exec();
}

