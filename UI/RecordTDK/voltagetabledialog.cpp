#include "voltagetabledialog.h"
#include "ui_voltagetabledialog.h"

VoltageTableDialog::VoltageTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VoltageTableDialog)
{
    ui->setupUi(this);
}

VoltageTableDialog::~VoltageTableDialog()
{
    delete ui;
}

void VoltageTableDialog::on_fillAnode_pushButton_clicked()
{
    if(ui->fromAnode_spinBox->value() > ui->toAnode_spinBox->value()) {
        QMessageBox::warning(this,tr("Zakres"),tr("Niepowazny czy co?\nPopraw zakres!"));
        return;
    }

    //clear table
    StarlingLab::Utils::clearTableWidget(ui->anode_tableWidget);

    //create list
    for(int i = ui->fromAnode_spinBox->value(); i <= ui->toAnode_spinBox->value(); i+=ui->stepAnode_spinBox->value())
        StarlingLab::Utils::addItemTableWidget(ui->anode_tableWidget,QStringList() << QString::number(i));
}


void VoltageTableDialog::on_fillFocusing_pushButton_clicked()
{
    if(ui->fromFocusing_spinBox->value() > ui->toFocusing_spinBox->value()) {
        QMessageBox::warning(this,tr("Zakres"),tr("Niepowazny czy co?\nPopraw zakres!"));
        return;
    }

    //clear table
    StarlingLab::Utils::clearTableWidget(ui->focusing_tableWidget);

    //create list
    for(int i = ui->fromFocusing_spinBox->value(); i <= ui->toFocusing_spinBox->value(); i+=ui->stepFocusing_spinBox->value())
        StarlingLab::Utils::addItemTableWidget(ui->focusing_tableWidget, QStringList() << QString::number(i));

}

void VoltageTableDialog::on_cancel_pushButton_clicked()
{
    this->reject();
}


void VoltageTableDialog::on_clear_pushButton_clicked()
{
    //clear table
    StarlingLab::Utils::clearTableWidget(ui->focusing_tableWidget);
    StarlingLab::Utils::clearTableWidget(ui->anode_tableWidget);

    //add empty item
    StarlingLab::Utils::addItemTableWidget(ui->focusing_tableWidget,QStringList() << QString(""));
    StarlingLab::Utils::addItemTableWidget(ui->anode_tableWidget,QStringList() << QString(""));

}


void VoltageTableDialog::on_set_pushButton_clicked()
{
    anodeTab.clear();
    int rows = ui->anode_tableWidget->rowCount();
    for(int i=0;i<rows;i++)
        anodeTab << ui->anode_tableWidget->item(i,0)->text().toDouble();

    focusingTab.clear();
    rows = ui->focusing_tableWidget->rowCount();
    for(int i=0;i<rows;i++)
        focusingTab << ui->focusing_tableWidget->item(i,0)->text().toDouble();

    this->accept();
}


void VoltageTableDialog::on_anode_tableWidget_cellChanged(int row, int column)
{
    int rows = ui->anode_tableWidget->rowCount();
    if(rows-1 == row) {
        if(!ui->anode_tableWidget->item(row,column)->text().isEmpty()) {
            ui->anode_tableWidget->insertRow(rows);
        }
        return;
    }
    if(ui->anode_tableWidget->item(row,column)->text().isEmpty()) {
        ui->anode_tableWidget->removeRow(row);
    }
}


void VoltageTableDialog::on_focusing_tableWidget_cellChanged(int row, int column)
{
    int rows = ui->focusing_tableWidget->rowCount();
    if(rows-1 == row) {
        if(!ui->focusing_tableWidget->item(row,column)->text().isEmpty()) {
            ui->focusing_tableWidget->insertRow(rows);
        }
        return;
    }
    if(ui->focusing_tableWidget->item(row,column)->text().isEmpty()) {
        ui->focusing_tableWidget->removeRow(row);
    }
}


void VoltageTableDialog::on_clearAnode_pushButton_clicked()
{
    StarlingLab::Utils::clearTableWidget(ui->anode_tableWidget);
    StarlingLab::Utils::addItemTableWidget(ui->anode_tableWidget,QStringList() << QString(""));
}


void VoltageTableDialog::on_clearFocusing_pushButton_clicked()
{
    StarlingLab::Utils::clearTableWidget(ui->focusing_tableWidget);
    StarlingLab::Utils::addItemTableWidget(ui->focusing_tableWidget,QStringList() << QString(""));
}

void VoltageTableDialog::setFocusingTab(const QVector<int> &newFocusingTab)
{
    focusingTab = newFocusingTab;
    //clear table
    StarlingLab::Utils::clearTableWidget(ui->focusing_tableWidget);

    //create list
    foreach(double value, focusingTab)
        StarlingLab::Utils::addItemTableWidget(ui->focusing_tableWidget, QStringList() << QString::number(value));
}

void VoltageTableDialog::setAnodeTab(const QVector<int> &newAnodeTab)
{
    anodeTab = newAnodeTab;
    //clear table
    StarlingLab::Utils::clearTableWidget(ui->anode_tableWidget);

    //create list
    foreach(double value, anodeTab)
        StarlingLab::Utils::addItemTableWidget(ui->anode_tableWidget, QStringList() << QString::number(value));
}

const QVector<int> &VoltageTableDialog::getFocusingTab() const
{
    return focusingTab;
}

const QVector<int> &VoltageTableDialog::getAnodeTab() const
{
    return anodeTab;
}

