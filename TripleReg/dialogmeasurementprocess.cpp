#include "dialogmeasurementprocess.h"
#include "ui_dialogmeasurementprocess.h"

DialogMeasurementProcess::DialogMeasurementProcess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMeasurementProcess)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->showMore1_checkBox->setChecked(false);

    connect(&powerSupplyProcessBox,SIGNAL(rejected()),this,SIGNAL(abortedPowerSupplyProcessBox()));
}

DialogMeasurementProcess::~DialogMeasurementProcess()
{
    delete ui;
}

void DialogMeasurementProcess::setMeasurementObject(const QString &nuclide, const QString &solutionId, const QString &sourceId)
{
    ui->nuclide_lineEdit->setText(nuclide);
    ui->solutionId_lineEdit->setText(solutionId);
    ui->sourceId_lineEdit->setText(sourceId);
}

void DialogMeasurementProcess::setParameter(const int &maxSourceNo, const int &maxPoint, const int &maxRepeat, const int &maxTime)
{
    ui->maxSource_label->setText(QString::number(maxSourceNo));
    ui->maxPoint_label->setText(QString::number(maxPoint));
    ui->maxRepeat_label->setText(QString::number(maxRepeat));
    ui->currTime_progressBar->setMaximum(maxTime);
    //clear current parameter
    ui->currSource_label->setText("0");
    ui->currPoint_label->setText("0");
    ui->currRepeat_label->setText("0");
    ui->currTime_progressBar->setValue(0);
    ui->timeLeft_label->setText(Utils::generatorTimeDHMSString(0));
    ui->endTime_label->setText(Utils::currentDateTime());
}

void DialogMeasurementProcess::setTimeLeft(const int &timeLeft)
{
    ui->timeLeft_label->setText(Utils::generatorTimeDHMSString(timeLeft));
}

void DialogMeasurementProcess::setEndTime(const QString &endTime)
{
    ui->endTime_label->setText(endTime);
}

void DialogMeasurementProcess::addRecord(const QStringList &record, const QStringList &fullRecord)
{
    Utils::addItemTableWidget(ui->short_tableWidget,record);
    Utils::addItemTableWidget(ui->full_tableWidget,fullRecord);
}

void DialogMeasurementProcess::updateLastRecord(const QStringList &record, const QStringList &fullRecord)
{
    Utils::updateLastItemTableWidget(ui->short_tableWidget,record);
    Utils::updateLastItemTableWidget(ui->full_tableWidget,fullRecord);
}

void DialogMeasurementProcess::showMessageBox(const QString &title, const QString &text)
{
    QMessageBox box;
    box.setWindowTitle(title);
    box.setText(text);
    box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    box.setDefaultButton(QMessageBox::Ok);
    if(box.exec() == QMessageBox::Ok) {
        emit acceptedMessageBox();
    }else {
        emit rejectedMessageBox();
    }
}

void DialogMeasurementProcess::showPowerSupplyProcessBox()
{
    powerSupplyProcessBox.show();
}

void DialogMeasurementProcess::hidePowerSupplyProcessBox()
{
    powerSupplyProcessBox.hide();
}

void DialogMeasurementProcess::setSetupHVPowerSupplyProcess(const int &maxVoltage)
{
    powerSupplyProcessBox.setSetupHV(maxVoltage);
}

void DialogMeasurementProcess::setStabilizationPowerSupplyProcess(const int &startDelay)
{
    powerSupplyProcessBox.setStabilization(startDelay);
}

void DialogMeasurementProcess::setCurrentStatusPowerSupplyProcess(const int &val)
{
    powerSupplyProcessBox.setCurrentState(val);
}

void DialogMeasurementProcess::on_showMore1_checkBox_stateChanged(int arg1)
{
    switch(arg1){
    case Qt::Unchecked:
        ui->stackedWidget->setCurrentIndex(0);
        break;
    case Qt::Checked:
        ui->stackedWidget->setCurrentIndex(1);
    }
}

