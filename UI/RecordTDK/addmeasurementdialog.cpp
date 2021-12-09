#include "addmeasurementdialog.h"
#include "ui_addmeasurementdialog.h"

AddMeasurementDialog::AddMeasurementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMeasurementDialog)
{
    ui->setupUi(this);
}

AddMeasurementDialog::~AddMeasurementDialog()
{
    delete ui;
}

void AddMeasurementDialog::on_cancel_pushButton_clicked()
{
    close();
}


void AddMeasurementDialog::on_start_pushButton_clicked()
{

}


void AddMeasurementDialog::on_addProtocol_pushButton_clicked()
{

}


void AddMeasurementDialog::on_editProtocol_pushButton_clicked()
{

}


void AddMeasurementDialog::on_searchProtocol_lineEdit_textChanged(const QString &arg1)
{

}

