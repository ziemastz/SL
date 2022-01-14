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
    delete mac3;
    delete ui;
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
        mac3->setEnable(false);
        mac3->setReset(true);
        mac3->setExtClk(connection.isExtClk);
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
