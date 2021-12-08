#include "monitoringdialog.h"
#include "ui_monitoringdialog.h"

MonitoringDialog::MonitoringDialog(const int& loggedUser,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MonitoringDialog)
{  
    ui->setupUi(this);
    _userLoggedId = loggedUser;
    ui->radionuclide_lineEdit->setFocus();
    threadN1470 = nullptr;
    n1470 = nullptr;
    timer = nullptr;
}

MonitoringDialog::~MonitoringDialog()
{
    if(timer != nullptr) {
        timer->stop();
        if(threadN1470 != nullptr) {
            threadN1470->quit();
            if(n1470 != nullptr) {
                delete n1470;
            }
            delete threadN1470;
        }
        delete timer;
    }
    if(counter.isConnect()) {
        counter.stop();
        counter.reset();
    }

    delete ui;
}

bool MonitoringDialog::init()
{
    if(!counter.isConnect()) {
        QMessageBox::warning(this,tr("BÅ‚Ä…d"),tr("Brak poÅ‚aczenia z licznikiem MAC3.\n")+counter.lastError());
        return false;
    }

    //set online monitoring
    ui->online_pushButton->setChecked(true);
    _isOnlineMonitoring = true;
    counter.stop();
    counter.reset();
    runOnlineMonitoring();

    //check status N1470
    loadConnectionParam();
    threadN1470 = new QThread(this);
    n1470 = new PowerSupplyN1470();

    if(!n1470->isConnect()) {
        QMessageBox::warning(this,tr("BÅ‚Ä…d"),tr("Brak poÅ‚aczenia z zasilaczem N1470.\n")+n1470->lastError());
        return false;
    }

    n1470->moveToThread(threadN1470);
    threadN1470->start();
    // configure connection signals from/to N1470
    ui->channel0_radioButton->setChecked(n1470->isTurnOnCh0());
    ui->channel1_radioButton->setChecked(n1470->isTurnOnCh1());
    ui->channel2_radioButton->setChecked(n1470->isTurnOnCh2());
    ui->channel3_radioButton->setChecked(n1470->isTurnOnCh3());
    ui->setCh0_doubleSpinBox->setValue((double)n1470->voltCh0());
    ui->setCh1_doubleSpinBox->setValue((double)n1470->voltCh1());
    ui->setCh2_doubleSpinBox->setValue((double)n1470->voltCh2());
    ui->setCh3_doubleSpinBox->setValue((double)n1470->voltCh3());
    connect(ui->channel0_radioButton,SIGNAL(toggled(bool)),n1470,SLOT(setTurnCh0(bool)),Qt::QueuedConnection);
    connect(ui->channel1_radioButton,SIGNAL(toggled(bool)),n1470,SLOT(setTurnCh1(bool)),Qt::QueuedConnection);
    connect(ui->channel2_radioButton,SIGNAL(toggled(bool)),n1470,SLOT(setTurnCh2(bool)),Qt::QueuedConnection);
    connect(ui->channel3_radioButton,SIGNAL(toggled(bool)),n1470,SLOT(setTurnCh3(bool)),Qt::QueuedConnection);
    connect(ui->setCh0_doubleSpinBox,SIGNAL(valueChanged(double)),n1470,SLOT(setVoltCh0(double)),Qt::QueuedConnection);
    connect(ui->setCh1_doubleSpinBox,SIGNAL(valueChanged(double)),n1470,SLOT(setVoltCh1(double)),Qt::QueuedConnection);
    connect(ui->setCh2_doubleSpinBox,SIGNAL(valueChanged(double)),n1470,SLOT(setVoltCh2(double)),Qt::QueuedConnection);
    connect(ui->setCh3_doubleSpinBox,SIGNAL(valueChanged(double)),n1470,SLOT(setVoltCh3(double)),Qt::QueuedConnection);

    //update data from N1470 and Mac3Counter
    timer = new QTimer(0);
    connect(timer,SIGNAL(timeout()),n1470,SLOT(refresh()),Qt::QueuedConnection);
    connect(timer,SIGNAL(timeout()),this,SLOT(checkStatusN1470()),Qt::QueuedConnection);
    connect(timer,SIGNAL(timeout()),this,SLOT(runOnlineMonitoring()),Qt::QueuedConnection);
    timer->start(500);

    checkStatusN1470();
    return true;
}

void MonitoringDialog::on_voltageTable_pushButton_clicked()
{
    voltageTabDialog.exec();
}

void MonitoringDialog::runOnlineMonitoring()
{
    if(!counter.isConnect()) {
        QMessageBox::warning(this,tr("BÅ‚Ä…d"),tr("Brak poÅ‚aczenia z licznikiem MAC3.\n")+counter.lastError());
        timer->stop();
        return;
    }

    if(!_isOnlineMonitoring) {
        return;
    }

    counter.stop();
    counter.readData();
    counter.start();
    if(counter.realTime() > samplingTime) {
       // counter.stop();
       // counter.readData();
        counter.reset();
        counter.start();
    }

    updateRecord();

   // QTimer::singleShot(200,this,SLOT(runOnlineMonitoring()));
}

void MonitoringDialog::runMeasurement()
{
    if(!counter.isConnect()) {
        QMessageBox::warning(this,tr("BÅ‚Ä…d"),tr("Brak poÅ‚aczenia z licznikiem MAC3.\n")+counter.lastError());
        _isFinished = true;
        return;
    }

    if(_isFinished) {
        ui->online_pushButton->setChecked(true);
        ui->start_pushButton->setEnabled(true);
        ui->stop_pushButton->setEnabled(false);
        return;
    }

    counter.start();
    counter.readData();

    if(counter.realTime() > _measurementTime) {
        _isFinished = true;
        counter.stop();
        counter.readData();
        saveRecord();
    }
    ui->time_progressBar->setValue((int)counter.realTime());
    updateRecord();

    if(_isFinished)
        addRecord();

    QTimer::singleShot(200,this,SLOT(runMeasurement()));

}


void MonitoringDialog::on_online_pushButton_toggled(bool checked)
{
    _isOnlineMonitoring = checked;

    runOnlineMonitoring();
}


void MonitoringDialog::on_start_pushButton_clicked()
{
    _measurementTime = ui->time_spinBox->value();
    if(_measurementTime == 0)
        return;

    ui->time_progressBar->setMaximum(_measurementTime);
    ui->time_progressBar->setMinimum(0);
    ui->time_progressBar->setValue(0);

    ui->online_pushButton->setChecked(false);
    ui->start_pushButton->setEnabled(false);
    ui->stop_pushButton->setEnabled(true);

    _isFinished = false;
    counter.stop();
    counter.reset();
    runMeasurement();
}

void MonitoringDialog::updateRecord()
{
    QStringList record;
    record << QString::number(counter.cpsA(),'f',1)
           << QString::number(counter.cpsB(),'f',1)
           << QString::number(counter.cpsC(),'f',1)
           << QString::number(counter.cpsS(),'f',1)
           << QString::number(counter.cpsAB(),'f',1)
           << QString::number(counter.cpsBC(),'f',1)
           << QString::number(counter.cpsAC(),'f',1)
           << QString::number(counter.cpsT(),'f',1)
           << QString::number(counter.cpsD(),'f',1)
           << QString::number(counter.cpsT()/counter.cpsD(),'f',4)
           << QString::number(counter.deadTime()*100 / counter.realTime(),'f',2)
           << QString::number(counter.rel1(),'f',0)
           << QString::number(counter.rel2(),'f',0);

    Utils::lastItemTableWidget(ui->counts_tableWidget,record);
}

void MonitoringDialog::saveRecord()
{
    RAWModel newData;
    newData.id = 0;
    newData.startMeasurementDateTime = counter.startDateTime().toString(FORMAT_TIMESTAMP);
    newData.sampleNumber = 1;
    newData.tag = ui->tag_tableWidget->item(ui->tag_tableWidget->rowCount()-1,0)->text();
    newData.repeatNumber = 1;
    newData.A = counter.getCounts().A;
    newData.B = counter.getCounts().B;
    newData.C = counter.getCounts().C;
    newData.S = counter.getCounts().S;
    newData.AB = counter.getCounts().AB;
    newData.BC = counter.getCounts().BC;
    newData.AC = counter.getCounts().AC;
    newData.T = counter.getCounts().T;
    newData.D = counter.getCounts().D;
    newData.LT = counter.getCounts().LT;
    newData.CLK_IN = counter.getCounts().CLK_IN;
    newData.ch0 = ui->monCh0_lineEdit->text().toDouble();
    newData.ch1 = ui->monCh1_lineEdit->text().toDouble();
    newData.ch2 = ui->monCh2_lineEdit->text().toDouble();
    newData.ch3 = ui->monCh3_lineEdit->text().toDouble();

    rawData << newData;
}

void MonitoringDialog::addRecord()
{
    ui->counts_tableWidget->insertRow(ui->counts_tableWidget->rowCount());

    QString tag = ui->tag_tableWidget->item(ui->tag_tableWidget->rowCount()-1,0)->text();
    ui->tag_tableWidget->insertRow(ui->tag_tableWidget->rowCount());

    bool isNumber;
    tag.toInt(&isNumber,10);
    if(isNumber)
        ui->tag_tableWidget->setItem(ui->tag_tableWidget->rowCount()-1,0,new QTableWidgetItem(QString::number(tag.toInt()+1)));
    else
        ui->tag_tableWidget->setItem(ui->tag_tableWidget->rowCount()-1,0,new QTableWidgetItem(tag));
}

void MonitoringDialog::loadConnectionParam()
{
    Database::DBRecordTDK db;
    SettingConnectionModel connection = db.getSettingConnection();

    PowerSupplyN1470::setPort(connection.port);
    PowerSupplyN1470::setBaudRate(connection.braudRate);
    PowerSupplyN1470::setLBusAddress(QString::number(connection.lBusAddress));

    //TODO: MAC3Counter param: deviceName i extClk set
}

void MonitoringDialog::checkStatusN1470()
{
    QString lastError = n1470->lastError();
    if(!lastError.isEmpty()) {
        QMessageBox::warning(this,tr("BÅ‚Ä…d"),tr("Brak komunikacji z zasilaczem N1470.\n")+n1470->lastError());
        timer->stop();
    }
    ui->monCh0_lineEdit->setText(QString::number(n1470->monVoltCh0(),'f',1));
    ui->monCh1_lineEdit->setText(QString::number(n1470->monVoltCh1(),'f',1));
    ui->monCh2_lineEdit->setText(QString::number(n1470->monVoltCh2(),'f',1));
    ui->monCh3_lineEdit->setText(QString::number(n1470->monVoltCh3(),'f',1));

    ui->statusCh0_lineEdit->setText(n1470->statusCh0());
    ui->statusCh1_lineEdit->setText(n1470->statusCh1());
    ui->statusCh2_lineEdit->setText(n1470->statusCh2());
    ui->statusCh3_lineEdit->setText(n1470->statusCh3());
}

void MonitoringDialog::on_channel0_radioButton_toggled(bool checked)
{
    if(checked)
        n1470->setTurnOn(PowerSupplyN1470::CH0);
    else
        n1470->setTurnOff(PowerSupplyN1470::CH0);
}


void MonitoringDialog::on_allChannel_radioButton_toggled(bool checked)
{
    if(checked) {
        ui->channel0_radioButton->setChecked(true);
        ui->channel1_radioButton->setChecked(true);
        ui->channel2_radioButton->setChecked(true);
        ui->channel3_radioButton->setChecked(true);
    }else {
        ui->channel0_radioButton->setChecked(false);
        ui->channel1_radioButton->setChecked(false);
        ui->channel2_radioButton->setChecked(false);
        ui->channel3_radioButton->setChecked(false);
    }
}


void MonitoringDialog::on_exit_pushButton_clicked()
{
    close();
}


void MonitoringDialog::on_clearData_pushButton_clicked()
{
    StarlingLab::Utils::clearTableWidget(ui->tag_tableWidget);
    StarlingLab::Utils::clearTableWidget(ui->counts_tableWidget);
    ui->tag_tableWidget->insertRow(0);
    ui->tag_tableWidget->setItem(0,0,new QTableWidgetItem(QString("1")));
    ui->counts_tableWidget->insertRow(0);
    rawData.clear();

}


void MonitoringDialog::on_saveData_pushButton_clicked()
{
    StarlingLab::TDKLogModel log;
    log.id = 0;
    log.nuclide = ui->radionuclide_lineEdit->text();
    log.tag = Database::DBRecordTDK::Monitoring;
    log.creationDateTime = QDate::currentDate().toString("yyyy-MM-dd");
    log.solution = ui->solution_lineEdit->text();
    log.measurementObject = ui->measObject_lineEdit->text();
    log.desciption = ui->comment_textEdit->toPlainText();
    log.linked = ui->linked_lineEdit->text();
    log.madeByUserId = _userLoggedId;
    log.status = StarlingLab::DBRecordTDK::Finished;

    Database::DBRecordTDK db;
    if(!db.insert(log)) {
        QMessageBox::warning(this,tr("B³¹d"),tr("B³¹d zapisy do bazy danych!"));
        db.remove(&log);
        return;
    }

    foreach(RAWModel model, rawData) {
        model.counterLogId = log.id;
        if(!db.insert(model)) {
            //TODO: messageBox
            QMessageBox::warning(this,tr("B³¹d"),tr("B³¹d zapisy do bazy danych!"));
            return;
        }
    }
    QMessageBox::information(this,tr("Zapisano"),tr("Pomiar zosta³ pomyœnie zapisany"));
}

void MonitoringDialog::on_channel1_radioButton_toggled(bool checked)
{
    if(checked)
        n1470->setTurnOn(PowerSupplyN1470::CH1);
    else
        n1470->setTurnOff(PowerSupplyN1470::CH1);
}


void MonitoringDialog::on_channel3_radioButton_toggled(bool checked)
{
    if(checked)
        n1470->setTurnOn(PowerSupplyN1470::CH3);
    else
        n1470->setTurnOff(PowerSupplyN1470::CH3);
}


void MonitoringDialog::on_channel2_radioButton_toggled(bool checked)
{
    if(checked)
        n1470->setTurnOn(PowerSupplyN1470::CH2);
    else
        n1470->setTurnOff(PowerSupplyN1470::CH2);
}

