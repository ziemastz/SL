#include "dialogvoltagetable.h"
#include "ui_dialogvoltagetable.h"

DialogVoltageTable::DialogVoltageTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogVoltageTable)
{
    ui->setupUi(this);
}

DialogVoltageTable::~DialogVoltageTable()
{
    delete ui;
}

void DialogVoltageTable::on_anodeFrom_spinBox_editingFinished()
{
    fillAnode();
}


void DialogVoltageTable::on_anodeTo_spinBox_editingFinished()
{
    fillAnode();
}


void DialogVoltageTable::on_anodeStep_spinBox_valueChanged(int arg1)
{
    fillAnode();
}

void DialogVoltageTable::fillAnode()
{
    if(ui->anodeFrom_spinBox->value() > ui->anodeTo_spinBox->value()) {
        return;
    }

    Utils::clearTableWidget(ui->anode_tableWidget);

    for(int i = ui->anodeFrom_spinBox->value(); i <= ui->anodeTo_spinBox->value(); i+=ui->anodeStep_spinBox->value())
        Utils::addItemTableWidget(ui->anode_tableWidget,QStringList() << QString::number(i));
}

void DialogVoltageTable::fillFocusing()
{
    if(ui->focusingFrom_spinBox->value() > ui->focusingTo_spinBox->value()) {
        return;
    }

    Utils::clearTableWidget(ui->focusing_tableWidget);

    for(int i = ui->focusingFrom_spinBox->value(); i <= ui->focusingTo_spinBox->value(); i+=ui->focusingStep_spinBox->value())
        Utils::addItemTableWidget(ui->focusing_tableWidget,QStringList() << QString::number(i));
}


void DialogVoltageTable::on_anode_tableWidget_cellChanged(int row, int column)
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


void DialogVoltageTable::on_clearAnode_pushButton_clicked()
{
    Utils::clearTableWidget(ui->anode_tableWidget);
    Utils::addItemTableWidget(ui->anode_tableWidget,QStringList() << QString("0"));
}


void DialogVoltageTable::on_focusingFrom_spinBox_editingFinished()
{
    fillFocusing();
}


void DialogVoltageTable::on_focusingTo_spinBox_editingFinished()
{
    fillFocusing();
}


void DialogVoltageTable::on_focusingStep_spinBox_valueChanged(int arg1)
{
    fillFocusing();
}


void DialogVoltageTable::on_focusing_tableWidget_cellChanged(int row, int column)
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


void DialogVoltageTable::on_clearFocusing_pushButton_clicked()
{
    Utils::clearTableWidget(ui->focusing_tableWidget);
    Utils::addItemTableWidget(ui->focusing_tableWidget,QStringList() << QString("0"));
}


void DialogVoltageTable::on_set_pushButton_clicked()
{
    anodeTab.clear();
    int rows = ui->anode_tableWidget->rowCount();
    for(int i=0;i<rows;i++){
        QTableWidgetItem *item = ui->anode_tableWidget->item(i,0);
        if(item != 0){
            if(!item->text().isEmpty()) {
                anodeTab << item->text().toInt();
            }
        }
    }

    focusingTab.clear();
    rows = ui->focusing_tableWidget->rowCount();
    for(int i=0;i<rows;i++) {
        QTableWidgetItem *item = ui->focusing_tableWidget->item(i,0);
        if(item != 0){
            if(!item->text().isEmpty()) {
                focusingTab << item->text().toInt();
            }
        }
    }

    this->accept();
}

const QVector<int> &DialogVoltageTable::getFocusingTab() const
{
    return focusingTab;
}

void DialogVoltageTable::setFocusingTab(const QVector<int> &newFocusingTab)
{
    focusingTab = newFocusingTab;
    Utils::clearTableWidget(ui->focusing_tableWidget);
    QStringList list = Utils::toStringList(focusingTab);
    foreach(QString value, list)
        Utils::addItemTableWidget(ui->focusing_tableWidget,QStringList()<<value);
}

const QVector<int> &DialogVoltageTable::getAnodeTab() const
{
    return anodeTab;
}

void DialogVoltageTable::setAnodeTab(const QVector<int> &newAnodeTab)
{
    anodeTab = newAnodeTab;
    Utils::clearTableWidget(ui->anode_tableWidget);
    QStringList list = Utils::toStringList(anodeTab);
    foreach(QString value, list)
        Utils::addItemTableWidget(ui->anode_tableWidget,QStringList()<<value);
}


void DialogVoltageTable::on_cancel_pushButton_clicked()
{
    close();
}

