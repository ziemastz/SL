#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    loadProtocolName();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exit_pushButton_clicked()
{
    close();
}

void MainWindow::on_newMeasurement_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    DatabaseStarlingLab db;
    //clear & load
    // first clear
    ui->nuclide_lineEdit->clear();
    ui->solutionID_lineEdit->clear();
    ui->sourceID_lineEdit->clear();
    ui->sourceNo_spinBox->setValue(1);
    ui->isBlank_checkBox->setChecked(true);

    TripleRegSettingsModel settings;
    db.select(1,&settings);
    ui->blankTime_spinBox->setValue(settings.blankTime);
    ui->sourceTime_spinBox->setValue(settings.sourceTime);
    ui->repeat_spinBox->setValue(settings.repeat);

    TripleRegProtocolModel protocol;
    DatabaseResults result = db.select(&protocol);
    ui->protocol_comboBox->clear();
    for(int i=0; i<result.count(); i++){
        protocol.setRecord(result.at(i)->record());
        ui->protocol_comboBox->addItem(protocol.name);
    }

    ui->linked_lineEdit->clear();
    ui->category_comboBox->setCurrentIndex(0);
    ui->comment_plainTextEdit->clear();

}

void MainWindow::on_cancelNewMeasurement_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_settings_pushButton_clicked()
{
    //load parameter
    DatabaseStarlingLab db;
    TripleRegSettingsModel settings;
    if(!db.select(1,&settings)) {
        QMessageBox::warning(this,tr("Database"),tr("Reading error from database!\nPlease contact the administrator."));
        return;
    }
    ui->blankTimeDefault_spinBox->setValue(settings.blankTime);
    ui->sourceTimeDefault_spinBox->setValue(settings.sourceTime);
    ui->repeatDefault_spinBox->setValue(settings.repeat);

    ui->startDelay_spinBox->setValue(settings.startDelay);
    ui->maxVoltage_spinBox->setValue(settings.voltageMax);

    ui->port_comboBox->clear();
    ui->port_comboBox->addItems(Utils::availablePorts());
    ui->port_comboBox->setCurrentText(settings.port);
    ui->baudRate_comboBox->setCurrentText(settings.braudRate);
    ui->lBusAddress_spinBox->setValue(settings.lBusAddress);

    ui->deviceName_lineEdit->setText(settings.deviceName);
    ui->extClk_checkBox->setChecked(settings.isExtClk);

    //load user;
    if(!db.select(Settings::loggedUserId(),&user)) {
        QMessageBox::warning(this,tr("Database"),tr("Reading error from database!\nPlease contact the administrator."));
        return;
    }
    ui->username_lineEdit->setText(user.username);
    ui->degree_lineEdit->setText(user.degree);
    ui->firstName_lineEdit->setText(user.firstName);
    ui->secondName_lineEdit->setText(user.secondName);
    ui->lastName_lineEdit->setText(user.lastName);

    ui->stackedWidget->setCurrentIndex(5);
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_saveGeneralSettings_pushButton_clicked()
{
    TripleRegSettingsModel settings;
    settings.id = 1;
    settings.blankTime = ui->blankTimeDefault_spinBox->value();
    settings.sourceTime = ui->sourceTimeDefault_spinBox->value();
    settings.repeat = ui->repeatDefault_spinBox->value();
    settings.startDelay = ui->startDelay_spinBox->value();
    settings.voltageMax = ui->maxVoltage_spinBox->value();
    settings.port = ui->port_comboBox->currentText();
    settings.braudRate = ui->baudRate_comboBox->currentText();
    settings.lBusAddress = ui->lBusAddress_spinBox->value();
    settings.deviceName = ui->deviceName_lineEdit->text();
    settings.isExtClk = ui->extClk_checkBox->isChecked();
    settings.userId = Settings::loggedUserId();

    DatabaseStarlingLab db;
    if(!db.update(&settings)) {
        QMessageBox::warning(this,tr("Database"),tr("Updating error from database!\nPlease contact the administrator."));
        return;
    }
    QMessageBox::information(this,tr("User data"),tr("Changes have been saved."));
}

void MainWindow::on_saveUserDatapushButton_clicked()
{
    user.degree = ui->degree_lineEdit->text();
    user.firstName = ui->firstName_lineEdit->text();
    user.secondName = ui->secondName_lineEdit->text();
    user.lastName = ui->lastName_lineEdit->text();

    DatabaseStarlingLab db;
    if(!db.update(&user)) {
        QMessageBox::warning(this,tr("Database"),tr("Updating error from database!\nPlease contact the administrator."));
        return;
    }
    QMessageBox::information(this,tr("User data"),tr("Changes have been saved."));
}

void MainWindow::on_passwordChange_pushButton_clicked()
{
    bool ok;
    QString currentPassword = QInputDialog::getText(this,tr("Password change"),
                                                    tr("Current password"), QLineEdit::Password,
                                                    QString(),&ok);
    if (ok && !currentPassword.isEmpty()) {
        if(currentPassword != user.password) {
            QMessageBox::warning(this,tr("Database"),tr("Wrong password!\nPlease try again."));
            return;
        }
        QString newPassword = QInputDialog::getText(this,tr("Password change"),
                                                        tr("New password"), QLineEdit::Password,
                                                        QString(),&ok);
        if (ok && !newPassword.isEmpty()) {
            QString confirmNewPassword = QInputDialog::getText(this,tr("Password change"),
                                                            tr("Confirm new password"), QLineEdit::Password,
                                                            QString(),&ok);
            if (ok && !confirmNewPassword.isEmpty()) {
                if(newPassword != confirmNewPassword) {
                    QMessageBox::warning(this,tr("Database"),tr("Wrong password!\nPlease try again."));
                    return;
                }
                user.password = newPassword;
                DatabaseStarlingLab db;
                if(!db.update(&user)) {
                    QMessageBox::warning(this,tr("Database"),tr("Updating error from database!\nPlease contact the administrator."));
                }else {
                    QMessageBox::information(this,tr("Password change"),tr("Your password has been successfully changed."));
                }
            }
        }
    }
}

void MainWindow::on_cancelSettings_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_connectionTestN1470_pushButton_clicked()
{
    PowerSupplyN1470::setPort(ui->port_comboBox->currentText());
    PowerSupplyN1470::setBaudRate(ui->baudRate_comboBox->currentText());
    PowerSupplyN1470::setLBusAddress(QString::number(ui->lBusAddress_spinBox->value()));

    PowerSupplyN1470 hv;
    if(hv.isConnect()) {
       QMessageBox::information(this,tr("Connection test"),tr("Connected properly to the CAEN N1470 power supply."));
    }else{
       QMessageBox::warning(this,tr("Connection test"),tr("Communication error with the CAEN N1470 power supply.\nPlease check the connectivity parameters."));
    }
}

void MainWindow::on_connectionTestMAC3Counter_pushButton_clicked()
{
    MAC3Counter mac3;
    mac3.setDeviceName(ui->deviceName_lineEdit->text().toStdString());
    if(mac3.connect()) {
        mac3.disconnect();
        QMessageBox::information(this,tr("Connection test"),tr("Connected properly to the MAC3 counter."));
    }else {
        QMessageBox::warning(this,tr("Connection test"),tr("Communication error with the MAC3 counter.\nPlease check the connectivity parameters."));
    }
}

void MainWindow::on_addProtocol_pushButton_clicked()
{
    bool ok;
    QString protocolName = QInputDialog::getText(this,tr("New protocol"),tr("New protocol name"),QLineEdit::Normal,QString(),&ok);
    if(ok && !protocolName.isEmpty()) {
        DatabaseStarlingLab db;
        if(!db.isAvailableProtocolName(protocolName)) {
            QMessageBox::warning(this,tr("New protocol"),tr("Nor available the new protocol name.\nPlease try again?"));
            return;
        }
        DialogProtocol protocolDialog(protocolName);
        if(protocolDialog.exec() == QDialog::Accepted) {
            ui->protocol_comboBox->addItem(protocolName);
            ui->protocol_comboBox->setCurrentText(protocolName);
        }

    }
}

void MainWindow::on_removeProtocol_pushButton_clicked()
{
    if(QMessageBox::question(this,tr("Remove protocol"),tr("Are you sure to delete the protocol permanently?")) == QMessageBox::Yes) {
        DatabaseStarlingLab db;
        TripleRegProtocolModel protocol;
        DatabaseResults results = db.select(&protocol,"name='"+ui->protocol_comboBox->currentText()+"'");
        if(results.count() != 1) {
            QMessageBox::warning(this,tr("Database"),tr("Reading error from database!\nPlease contact the administrator."));
            QMessageBox::warning(this,tr("Remove protocol"),tr("The protocol has not been deleted."));
            return;
        }
        protocol.setRecord(results.at(0)->record());
        protocol.userId = Settings::loggedUserId();
        if(!db.update(&protocol)) {
            QMessageBox::warning(this,tr("Database"),tr("Updating error from database!\nPlease contact the administrator."));
            QMessageBox::warning(this,tr("Remove protocol"),tr("The protocol has not been deleted."));
            return;
        }
        if(!db.remove(&protocol)) {
            QMessageBox::warning(this,tr("Database"),tr("Removing error from database!\nPlease contact the administrator."));
            QMessageBox::warning(this,tr("Remove protocol"),tr("The protocol has not been deleted."));
            return;
        }
        QMessageBox::information(this,tr("Remove protocol"),tr("The protocol was successfully deleted."));
        ui->protocol_comboBox->removeItem(ui->protocol_comboBox->findText(protocol.name));
    }
}

void MainWindow::on_editProtocol_pushButton_clicked()
{
    DialogProtocol protocolDialog(ui->protocol_comboBox->currentText());
    protocolDialog.exec();
}

void MainWindow::loadProtocolName()
{
    DatabaseStarlingLab db;
    TripleRegProtocolModel protocol;
    DatabaseResults result = db.select(&protocol);
    for(int i=0; i<result.count(); i++){
        protocol.setRecord(result.at(i)->record());
        ui->protocol_comboBox->addItem(protocol.name);
    }
}


void MainWindow::on_startNewMeasurement_pushButton_clicked()
{
    //check data
    if(ui->nuclide_lineEdit->text().isEmpty() ||
       ui->sourceID_lineEdit->text().isEmpty()) {
        QMessageBox::warning(this,tr("New measurement"),tr("Please provide nuclide and source ID."));
        return;
    }
    if(ui->sourceNo_spinBox->value() == 0 ||
       !ui->isBlank_checkBox->isChecked()) {
        QMessageBox::warning(this,tr("New measurement"),tr("There are no measurement objects.\nEnter the measurement objects (e.g. blank, source)."));
        return;
    }
    TripleRegMeasurementRegisterModel reg;
    TripleRegMeasurementProtocolModel protocol;
    TripleRegMeasuringSystemModel system;
    DatabaseStarlingLab db;
    int id = db.countMeasurementFrom(QDateTime::currentDateTime().toString("yyyy")+"-01-01");
    if(id == -1){
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }
    id++;
    DatabaseResults result = db.select(&system,"isDefault=1");
    if(result.count() !=1 ) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }
    system.setRecord(result.at(0)->record());
    reg.id = 0;
    reg.measurementId = Utils::generatorMeasurementId(system.number,id);
    reg.measurementDate = Utils::currentDate();
    reg.nuclide = ui->nuclide_lineEdit->text();
    reg.solutionId = ui->solutionID_lineEdit->text();
    reg.sourceId = ui->sourceID_lineEdit->text();
    reg.sourceNo = ui->sourceNo_spinBox->value();
    reg.isBlank = ui->isBlank_checkBox->isChecked();
    reg.blankTime = ui->blankTime_spinBox->value();
    reg.sourceTime = ui->sourceTime_spinBox->value();
    reg.repeat = ui->repeat_spinBox->value();
    //copy protocol
    DatabaseResults result2 = db.select(new TripleRegProtocolModel,"name='"+ui->protocol_comboBox->currentText()+"'");
    if(result2.count() != 1) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }
    protocol.setRecord(result2.at(0)->record());
    protocol.id = 0;
    protocol.userId = Settings::loggedUserId();
    if(!db.insert(&protocol)) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }//end copy
    reg.protocolId = protocol.id;
    reg.linked = ui->linked_lineEdit->text();
    reg.category = ui->category_comboBox->currentText();
    reg.comments = ui->comment_plainTextEdit->toPlainText();
    reg.userId = Settings::loggedUserId();
    if(!db.insert(&reg)) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }
    QMessageBox::information(this,tr("New measurement"),tr("Succes!"));
    DialogMeasurementProcess dialogMeasurementProcess(reg);
    this->hide();
    dialogMeasurementProcess.exec();
    this->show();
    this->setFocus();

}

