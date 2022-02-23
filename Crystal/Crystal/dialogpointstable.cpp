#include "dialogpointstable.h"
#include "ui_dialogpointstable.h"

DialogPointsTable::DialogPointsTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPointsTable)
{
    ui->setupUi(this);
}

DialogPointsTable::~DialogPointsTable()
{
    delete ui;
}

void DialogPointsTable::on_cancel_pushButton_clicked()
{
    close();
}


void DialogPointsTable::on_clear_pushButton_clicked()
{
    Utils::clearTableWidget(ui->points_tableWidget);
    Utils::addItemTableWidget(ui->points_tableWidget,QStringList() << QString("0"));
}


void DialogPointsTable::on_set_pushButton_clicked()
{
    _points.clear();
    int rows = ui->points_tableWidget->rowCount();
    for(int i=0;i<rows;i++){
        QTableWidgetItem *item = ui->points_tableWidget->item(i,0);
        if(item != 0){
            if(!item->text().isEmpty()) {
                _points << item->text();
            }
        }
    }
    _typePoints = ui->typePoints_comboBox->currentText();
    accept();
}


void DialogPointsTable::on_points_tableWidget_cellChanged(int row, int column)
{
    int rows = ui->points_tableWidget->rowCount();
    if(rows-1 == row) {
        if(!ui->points_tableWidget->item(row,column)->text().isEmpty()) {
            ui->points_tableWidget->insertRow(rows);
        }
        return;
    }
    if(ui->points_tableWidget->item(row,column)->text().isEmpty()) {
        ui->points_tableWidget->removeRow(row);
    }
}

void DialogPointsTable::setPoints(const QStringList &newPoints)
{
    _points = newPoints;
    Utils::clearTableWidget(ui->points_tableWidget);
    foreach(QString value, _points)
        Utils::addItemTableWidget(ui->points_tableWidget,QStringList()<<value);
}

void DialogPointsTable::setTypePoints(const QString &newTypePoints)
{
    _typePoints = newTypePoints;
    ui->typePoints_comboBox->setCurrentText(_typePoints);
}

QVector<double> DialogPointsTable::points() const
{
    QVector<double> ret;
    foreach(QString val, _points)
        ret << val.toDouble();
    return ret;
}

const QString &DialogPointsTable::typePoints() const
{
    return _typePoints;
}

