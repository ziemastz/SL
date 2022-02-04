#include "dialogmeasurementreport.h"
#include "ui_dialogmeasurementreport.h"

DialogMeasurementReport::DialogMeasurementReport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMeasurementReport)
{
    ui->setupUi(this);
}

DialogMeasurementReport::~DialogMeasurementReport()
{
    delete ui;
}
