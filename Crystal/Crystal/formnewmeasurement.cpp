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

void FormNewMeasurement::setSystemLabel(const QString &newSystemLabel)
{
    _systemLabel = newSystemLabel;
    ui->system_groupBox->setTitle(tr("System ")+_systemLabel);
}
