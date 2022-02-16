#include "dialognewmeasurement.h"
#include "ui_dialognewmeasurement.h"

DialogNewMeasurement::DialogNewMeasurement(const int &id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewMeasurement)
{
    _id = id;
    ui->setupUi(this);
    loadDefaultParameters();
}

DialogNewMeasurement::~DialogNewMeasurement()
{
    delete ui;
}

void DialogNewMeasurement::on_pointsTable_checkBox_toggled(bool checked)
{
    ui->pointsTable_pushButton->setEnabled(checked);
}


void DialogNewMeasurement::on_cancel_pushButton_clicked()
{
    close();
}


void DialogNewMeasurement::on_pointsTable_pushButton_clicked()
{
    //
    pointsTableDialog.exec();
}


void DialogNewMeasurement::on_start_pushButton_clicked()
{
    //check lineEdit


    //add measurement
    DBCrystal db;
    CrystalMeasurementProtocolModel protocol;
    protocol.anodeVoltage = ui->anodeVoltage_doubleSpinBox->value();
    protocol.thresholdVoltage = ui->thresholdVoltage_doubleSpinBox->value();
    protocol.extendableDeadTime = ui->extendableDeadTime_doubleSpinBox->value();
    protocol.notes = ui->notes_plainTextEdit->toPlainText();
    if(ui->pointsTable_checkBox->isChecked()) {
        protocol.typePoints = pointsTableDialog.typePoints();
        protocol.points = pointsTableDialog.points();
    }
    protocol.userId = Settings::loggedUserId();
    if(!db.insert(&protocol)) {
        QMessageBox::warning(this,tr("Inserting error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    CrystalMeasurementRegisterModel reg;
    reg.id = 0;
    reg.systemLabel = _systemLabel;
    CrystalMeasuringSystemModel system;
    if(!db.select(1,&system)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }

    QString systemNumber;
    switch (_id) {
    case 1:
        systemNumber = system.numberA;
        break;
    case 2:
        systemNumber = system.numberB;
        break;
    case 3:
        systemNumber = system.numberC;
        break;
    case 4:
        systemNumber = system.numberD;
        break;
    default:
        return;
    }
    int id = db.countsMeasurement(systemNumber,QDateTime::currentDateTime().date().year());
    if(id == -1){
        if(!db.addCountsMeasurement(systemNumber,QDateTime::currentDateTime().date().year())) {
            QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
            return;
        }
        id=0;
    }
    id++;
    reg.measurementId = Utils::generatorMeasurementId(systemNumber,id);
    reg.measurementDate = Utils::currentDate();
    reg.nuclide = ui->nuclide_lineEdit->text();
    reg.sourceId = ui->sourceID_lineEdit->text();
    reg.sourceNo = ui->sourceNo_spinBox->value();
    reg.geometry = ui->geometry_lineEdit->text();
    reg.protocolId = protocol.id;
    reg.blankTime = ui->blankTime_spinBox->value();
    reg.sourceTime = ui->sourceTime_spinBox->value();
    reg.repeat = ui->repeat_spinBox->value();
    reg.linked = ui->linked_lineEdit->text();
    reg.category = ui->category_comboBox->currentText();
    reg.comments = ui->comments_plainTextEdit->toPlainText();
    reg.authorId = Settings::loggedUserId();
    reg.acceptedId = 0;
    reg.acceptedDateTime = "";
    reg.userId = Settings::loggedUserId();
    if(!db.insert(&reg)) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        db.remove(&protocol);
        return;
    }
    if(!db.increaseCountsMeasurement(systemNumber,QDateTime::currentDateTime().date().year())) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        db.remove(&protocol);
        db.remove(&reg);
        return;
    }
    emit startNewMeasurement(reg.id);
    accept();

}

void DialogNewMeasurement::loadDefaultParameters()
{
    DBCrystal db;
    CrystalSettingModel settings;
    if(!db.select(1,&settings)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
    }else {
        ui->blankTime_spinBox->setValue(settings.blankTime);
        ui->sourceTime_spinBox->setValue(settings.sourceTime);
        ui->repeat_spinBox->setValue(settings.repeat);
    }
    //protocol
    CrystalProtocolModel protocol;

    if(!db.select(_id,&protocol)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
    }else {
        _systemLabel = protocol.systemLabel;
        ui->anodeVoltage_doubleSpinBox->setValue(protocol.anodeVoltage);
        ui->thresholdVoltage_doubleSpinBox->setValue(protocol.thresholdVoltage);
        ui->extendableDeadTime_doubleSpinBox->setValue(protocol.extendableDeadTime);
        ui->notes_plainTextEdit->setPlainText(protocol.notes);
    }
}

