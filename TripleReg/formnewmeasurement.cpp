#include "formnewmeasurement.h"
#include "ui_formnewmeasurement.h"

FormNewMeasurement::FormNewMeasurement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormNewMeasurement)
{
    ui->setupUi(this);
}

FormNewMeasurement::~FormNewMeasurement()
{
    delete ui;
}
