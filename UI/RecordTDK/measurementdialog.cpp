#include "measurementdialog.h"
#include "ui_measurementdialog.h"

MeasurementDialog::MeasurementDialog(const StarlingLab::TDKLogModel& log, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeasurementDialog)
{
    ui->setupUi(this);
    _log = log;
    StarlingLab::DBRecordTDK db;
    _protocol = db.getProtocol(_log.measurementProtocolId);
    _general = db.getSettingGeneral();

    loadData();
    if(!initConnection()) {
        QMessageBox::warning(this,tr("Błąd połaczenia"),tr("Błąd połaczenia z urzędzeniami.\nSprawdz czy urzędzenia są podłączone i przetestuj połaczenia w Ustawieniach."));
    }else {
        initMeasurement();
    }
}

MeasurementDialog::~MeasurementDialog()
{
    n1470->setTurnOff(PowerSupplyN1470::CH0);
    n1470->setTurnOff(PowerSupplyN1470::CH1);
    n1470->setTurnOff(PowerSupplyN1470::CH2);
    n1470->setTurnOff(PowerSupplyN1470::CH3);
    mac3->disconnect();

    delete n1470;
    delete counter;
    delete mac3;
    delete ui;
}

void MeasurementDialog::runMeasurement()
{
    timer->stop();
    switch (statusMeasurement) {
    case MeasurementDialog::Init:
        currentAnodeVoltage = 0;
        currentFocusingVoltage = 0;
        currentSource = 0;
        currentRepeat = 0;
        if(_log.time.blank > 0) {
            statusMeasurement = RunBlank;
        }else {
            statusMeasurement = RunSource;
        }
        break;
    case MeasurementDialog::RunBlank:
        if(QMessageBox::Ok == QMessageBox::information(this,tr("Pomiar tła"),tr("Proszę umieszcz tło w komerze, a następnie wciśnij OK"))) {
            setVoltage(_protocol.anodaVoltage.at(currentAnodeVoltage), _protocol.focusingVoltage.at(currentFocusingVoltage));
            delayedStart();
            statusMeasurement = BlankNextRepeat;
        }else {
            statusMeasurement = Finished;
        }
        break;
    case MeasurementDialog::BlankNextPoint:
        break;
    case MeasurementDialog::BlankNextRepeat:
        counter->readData();
        updateRecord();
        if((int)counter->realTime() > _log.time.blank) {
            counter->stop();
            counter->readData();
        }
        break;
    case MeasurementDialog::RunSource:
        break;
    case MeasurementDialog::NextSource:
        break;
    case MeasurementDialog::NextPoint:
        break;
    case MeasurementDialog::NextRepeat:

        break;
    case MeasurementDialog::Finished:
        break;
    }
    timer->start(500);
}

void MeasurementDialog::process()
{
    switch (currentStatus) {
    case MeasurementDialog::Init:
        currentAnodeVoltage = 0;
        currentFocusingVoltage = 0;
        currentSource = 0;
        currentRepeat = 0;
        if(_log.time.blank > 0) {
            currentStatus = InitBlank;
        }else {
            currentStatus = InitSource;
        }
        break;
    case MeasurementDialog::InitBlank:
        //message
        break;
    case MeasurementDialog::MeasureBlank:
        break;
    case MeasurementDialog::NextRepeatBlank:
        break;
    case MeasurementDialog::NextPointBlank:
        break;
    case MeasurementDialog::InitSource:
        break;
    case MeasurementDialog::MeasureSource:
        break;
    case MeasurementDialog::NextRepeatSource:
        break;
    case MeasurementDialog::NextPointSource:
        break;
    case MeasurementDialog::NextSource:
        break;
    case MeasurementDialog::Finished:
        break;

    }
}

void MeasurementDialog::loadData()
{
    ui->nuclide_lineEdit->setText(_log.nuclide);
    ui->measurementObject_lineEdit->setText(_log.measurementObject());

    ui->sources_progressBar->setMinimum(0);
    ui->sources_progressBar->setMaximum(_log.noSources);
    ui->sources_progressBar->setValue(0);

    ui->points_progressBar->setMinimum(1);
    ui->points_progressBar->setMaximum(_protocol.anodaVoltage.count()*_protocol.focusingVoltage.count());
    ui->points_progressBar->setValue(1);

    ui->repeating_progressBar->setMinimum(1);
    ui->repeating_progressBar->setMaximum(_log.time.repeating);
    ui->repeating_progressBar->setValue(1);

    ui->time_progressBar->setMinimum(0);
    ui->time_progressBar->setMaximum(_log.time.blank);
    ui->time_progressBar->setValue(0);
}

bool MeasurementDialog::initConnection()
{
    StarlingLab::DBRecordTDK db;
    StarlingLab::SettingConnectionModel connection = db.getSettingConnection();

    PowerSupplyN1470::setPort(connection.port);
    PowerSupplyN1470::setBaudRate(connection.braudRate);
    PowerSupplyN1470::setLBusAddress(QString::number(connection.lBusAddress));
    n1470 = new PowerSupplyN1470();
    if(n1470->isConnect()) {
        n1470->setVolt(0,PowerSupplyN1470::CH0);
        n1470->setVolt(0,PowerSupplyN1470::CH1);
        n1470->setVolt(0,PowerSupplyN1470::CH2);
        n1470->setVolt(0,PowerSupplyN1470::CH3);

        n1470->setTurnOn(PowerSupplyN1470::CH0);
        n1470->setTurnOn(PowerSupplyN1470::CH1);
        n1470->setTurnOn(PowerSupplyN1470::CH2);
        n1470->setTurnOn(PowerSupplyN1470::CH3);
    }else {
        return false;
    }
    mac3 = new MAC3Counter();
    mac3->setDeviceName(connection.deviceName.toStdString());
    if(mac3->connect()) {
        mac3->setExtClk(connection.isExtClk);
        counter = new Counter(mac3);
        counter->reset();
    }else {
        return false;
    }

    return true;
}

void MeasurementDialog::initMeasurement()
{
    timer = new QTimer(0);
    connect(timer,SIGNAL(timeout()),this,SLOT(runMeasurement()),Qt::QueuedConnection);
    timer->start(500);

}

void MeasurementDialog::setVoltage(const int &anode, const int &focusing)
{
    n1470->setVoltCh0(anode+_protocol.voltageShiftA);
    n1470->setVoltCh1(anode+_protocol.voltageShiftB);
    n1470->setVoltCh2(anode+_protocol.voltageShiftC);
    n1470->setVoltCh3(focusing);
    QMessageBox *wait = new QMessageBox(this);
    wait->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    wait->setFocus();
    wait->setStandardButtons(QMessageBox::NoButton);
    wait->setText(tr("Ustawianie napięcia wysokiego. Czekaj..."));
    wait->show();
    while(1) {
        n1470->refresh();
        if((int)n1470->voltCh0() == (int)n1470->monVoltCh0() &&
           (int)n1470->voltCh1() == (int)n1470->monVoltCh1() &&
           (int)n1470->voltCh2() == (int)n1470->monVoltCh2() &&
           (int)n1470->voltCh3() == (int)n1470->monVoltCh3()) {
          break;
        }

    }
    wait->close();
    delete wait;
}

void MeasurementDialog::delayedStart()
{
    QTimer::singleShot(_general.delayedStart*1000,this,SLOT(runMeasurement()));
}

void MeasurementDialog::updateRecord()
{
    QStringList record;
    record << counter->startDateTime().toString("yyyy-MM-dd hh:mm:ss")
           <<
}
