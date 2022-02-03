#include "dialogpowersupplyprocess.h"
#include "ui_dialogpowersupplyprocess.h"

DialogPowerSupplyProcess::DialogPowerSupplyProcess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPowerSupplyProcess)
{
    ui->setupUi(this);
}

DialogPowerSupplyProcess::~DialogPowerSupplyProcess()
{
    delete ui;
}

void DialogPowerSupplyProcess::setSetupHV(const int &maxVoltage)
{
    ui->text_label->setText(tr("High voltage setup in progress ..."));
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(maxVoltage);
}

void DialogPowerSupplyProcess::setStabilization(const int &startDelay)
{
    ui->text_label->setText(tr("High voltage stabilization in progress ..."));
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(startDelay);
}

void DialogPowerSupplyProcess::setCurrentState(const int &val)
{
    ui->progressBar->setValue(val);
}

void DialogPowerSupplyProcess::on_abort_pushButton_clicked()
{
    emit abortPowerSupplyProcess();
}

