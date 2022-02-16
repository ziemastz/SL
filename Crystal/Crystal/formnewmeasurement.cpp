#include "formnewmeasurement.h"
#include "ui_formnewmeasurement.h"

FormNewMeasurement::FormNewMeasurement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormNewMeasurement)
{
    ui->setupUi(this);
    _id = 0;
}

FormNewMeasurement::~FormNewMeasurement()
{
    delete ui;
}

void FormNewMeasurement::setSystemLabel(const QString &newSystemLabel)
{
    _systemLabel = newSystemLabel;
    if(_systemLabel == "A")
        _id = 1;
    if(_systemLabel == "B")
        _id = 2;
    if(_systemLabel == "C")
        _id = 3;
    if(_systemLabel == "D")
        _id = 4;
    ui->system_groupBox->setTitle(tr("System ")+_systemLabel);
    ui->systemLabel_label->setText(_systemLabel);
}

void FormNewMeasurement::setNuclide(const QString &nuclide)
{
    ui->nuclide_lineEdit->setText(nuclide);
}

void FormNewMeasurement::setSourceId(const QString &sourceId)
{
    ui->sourceID_lineEdit->setText(sourceId);
}

void FormNewMeasurement::setGeometry(const QString &geometry)
{
    ui->geometry_lineEdit->setText(geometry);
}

void FormNewMeasurement::setProcess(const QString &process)
{
    ui->process_lineEdit->setText(process);
}

void FormNewMeasurement::setCurrentRepeat(const int &value)
{
    ui->repeat_progressBar->setValue(value);
}

void FormNewMeasurement::setRepeat(const int &value)
{
    ui->repeat_progressBar->setMaximum(value);
}

void FormNewMeasurement::setEndTime(const QString &endTime)
{
    ui->endTime_lineEdit->setText(endTime);
}

void FormNewMeasurement::setActivity(const double &value)
{
    ui->activity_doubleSpinBox->setValue(value);
}

void FormNewMeasurement::setCounts(const double &value)
{
    ui->counts_doubleSpinBox->setValue(value);
}

void FormNewMeasurement::setDeadTime(const double &value)
{
    ui->deadTime_doubleSpinBox->setValue(value);
}

void FormNewMeasurement::on_start_pushButton_clicked()
{
    DialogNewMeasurement newMeas(_id,this);
    connect(&newMeas,SIGNAL(startNewMeasurement(int)),this,SIGNAL(startNewMeasurement(int)));
    newMeas.exec();
}

