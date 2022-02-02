#include "dialogmeasurementprocess.h"
#include "ui_dialogmeasurementprocess.h"

DialogMeasurementProcess::DialogMeasurementProcess(const TripleRegMeasurementRegisterModel &measurementRegister, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMeasurementProcess)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->showMore1_checkBox->setChecked(false);

    connect(&powerSupplyProcessBox,SIGNAL(rejected()),this,SIGNAL(abortedPowerSupplyProcessBox()));
    //configure process
    QThread *thread = new QThread();
    WorkerMeasurementProcess *workerProcess = new WorkerMeasurementProcess(measurementRegister);

    workerProcess->moveToThread(thread);
    //init
    connect(thread, SIGNAL(started()), workerProcess, SLOT(init()));
    connect(workerProcess, SIGNAL(finished), thread, SLOT(quit()));

    //connection worker with dialog
    connect(workerProcess, SIGNAL(setMeasurementObject(QString,QString,QString)), this, SLOT(setMeasurementObject(QString,QString,QString)));
    connect(workerProcess, SIGNAL(setParameter(int,int,int,int)), this, SLOT(setParameter(int,int,int,int)));

    connect(workerProcess, SIGNAL(setEndTime(QString)), this, SLOT(setEndTime(QString)));
    connect(workerProcess, SIGNAL(setTimeLeft(int)), this, SLOT(setTimeLeft(int)));

    connect(workerProcess, SIGNAL(setCurrentSource(int)), this, SLOT(setCurrentSource(int)));
    connect(workerProcess, SIGNAL(setCurrentPoint(int)), this, SLOT(setCurrentPoint(int)));
    connect(workerProcess, SIGNAL(setCurrentRepeat(int)), this, SLOT(setCurrentRepeat(int)));
    connect(workerProcess, SIGNAL(setCurrentTime(int)), this, SLOT(setCurrentTime(int)));

    connect(workerProcess, SIGNAL(showPowerSupplyProcessBox()), this, SLOT(showPowerSupplyProcessBox()));
    connect(workerProcess, SIGNAL(hidePowerSupplyProcessBox()), this, SLOT(hidePowerSupplyProcessBox()));
    connect(workerProcess, SIGNAL(setSetupHVPowerSupplyProcess(int)), this, SLOT(setSetupHVPowerSupplyProcess(int)));
    connect(workerProcess, SIGNAL(setStabilizationPowerSupplyProcess(int)), this, SLOT(setStabilizationPowerSupplyProcess(int)));
    connect(workerProcess, SIGNAL(setCurrentStatusPowerSupplyProcess(int)), this, SLOT(setCurrentStatusPowerSupplyProcess(int)));

    connect(workerProcess, SIGNAL(showMessageBox(QString,QString)), this, SLOT(showMessageBox(QString,QString)));

    connect(workerProcess, SIGNAL(addRecord(QStringList,QStringList)), this, SLOT(addRecord(QStringList,QStringList)));
    connect(workerProcess, SIGNAL(updateLastRecord(QStringList,QStringList)), this, SLOT(updateLastRecord(QStringList,QStringList)));

    //delete
    connect(workerProcess, SIGNAL(finished()), workerProcess, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
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

void DialogMeasurementProcess::setCurrentSource(const int &val)
{
    ui->currSource_label->setText(QString::number(val));
}

void DialogMeasurementProcess::setCurrentPoint(const int &val)
{
    ui->currPoint_label->setText(QString::number(val));
}

void DialogMeasurementProcess::setCurrentRepeat(const int &val)
{
    ui->currRepeat_label->setText(QString::number(val));
}

void DialogMeasurementProcess::setCurrentTime(const int &val)
{
    ui->currTime_progressBar->setValue(val);
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

