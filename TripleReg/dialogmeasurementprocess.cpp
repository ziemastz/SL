#include "dialogmeasurementprocess.h"
#include "ui_dialogmeasurementprocess.h"

DialogMeasurementProcess::DialogMeasurementProcess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMeasurementProcess)
{
    ui->setupUi(this);
}

DialogMeasurementProcess::~DialogMeasurementProcess()
{
    delete ui;
}
