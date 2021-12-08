#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(const int& userIdLogged, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    this->setFocus();
    ui->tabWidget->setCurrentIndex(0);

    loadGeneral();
    loadConnection();
    loadUser(userIdLogged);
    _userIdLogged = userIdLogged;

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::loadGeneral()
{
    StarlingLab::DBRecordTDK db;

    StarlingLab::SettingGeneralModel general = db.getSettingGeneral();
    if(general.id != 0) {
        _general = general;
        ui->blankTime_spinBox->setValue(general.blankTime);
        ui->sourceTime_spinBox->setValue(general.sourceTime);
        ui->repeated_spinBox->setValue(general.repeated);
        ui->delayedStart_spinBox->setValue(general.delayedStart);

        ui->voltageMax_spinBox->setValue(general.voltageMax);
        ui->amperMax_spinBox->setValue(general.amperMax);
        ui->voltageShiftA_spinBox->setValue(general.voltageShiftA);
        ui->voltageShiftB_spinBox->setValue(general.voltageShiftB);
        ui->voltageShiftC_spinBox->setValue(general.voltageShiftC);

        ui->resolvingTime_spinBox->setValue(general.resolvingTime);
        ui->deadTime_spinBox->setValue(general.deadTime);
        ui->thrA_doubleSpinBox->setValue(general.thrA);
        ui->thrB_doubleSpinBox->setValue(general.thrB);
        ui->thrC_doubleSpinBox->setValue(general.thrC);

        ui->lastModificationDateTimeGeneral_label->setText(general.timestamp+", "+db.getUser(general.userId).signatureShort());
    }
}

void SettingsDialog::loadConnection()
{
    ui->port_comboBox->clear();
    ui->port_comboBox->addItems(StarlingLab::Utils::availablePorts());

    StarlingLab::DBRecordTDK db;

    StarlingLab::SettingConnectionModel con = db.getSettingConnection();
    if(con.id != 0) {
        _connection = con;
        ui->port_comboBox->setCurrentText(con.port);
        ui->baudRate_comboBox->setCurrentText(con.braudRate);
        ui->lBusAddress_spinBox->setValue(con.lBusAddress);

        ui->deviceName_lineEdit->setText(con.deviceName);
        ui->extClk_checkBox->setChecked(con.isExtClk);

        ui->lastModificationDateTimeConnection_label->setText(con.timestamp+", "+db.getUser(con.userId).signatureShort());
    }
}

void SettingsDialog::loadUser(const StarlingLab::UserModel &user)
{
    StarlingLab::DBRecordTDK db;
    ui->users_comboBox->blockSignals(true);
    ui->users_comboBox->clear();
    ui->users_comboBox->addItems(db.getUsernames());
    ui->users_comboBox->blockSignals(false);

    if(user.id != 0) {
        _user.setRecord(user.record());
        ui->username_lineEdit->setText(user.username);
        ui->password_lineEdit->setText(user.password);

        ui->users_comboBox->blockSignals(true);
        ui->users_comboBox->setCurrentText(user.username);
        ui->users_comboBox->blockSignals(false);

        if(user.isActive){
            ui->deactivateUser_checkBox->setChecked(false);

        }else {
            ui->deactivateUser_checkBox->setChecked(true);
        }

        ui->firstName_lineEdit->setText(user.firstName);
        ui->secondName_lineEdit->setText(user.secondName);
        ui->lastName_lineEdit->setText(user.lastName);
        ui->lastModificationDateTimeUser_label->setText(user.timestamp+", "+db.getUser(user.userId).signatureShort());
    }
}

void SettingsDialog::loadUser(const int &userId)
{
    StarlingLab::DBRecordTDK db;
    loadUser(db.getUser(userId));
}

void SettingsDialog::on_saveGeneral_pushButton_clicked()
{
    StarlingLab::DBRecordTDK db;

    StarlingLab::SettingGeneralModel newGeneral;
    newGeneral.id = _general.id;
    newGeneral.blankTime = ui->blankTime_spinBox->value();
    newGeneral.sourceTime = ui->sourceTime_spinBox->value();
    newGeneral.repeated = ui->repeated_spinBox->value();
    newGeneral.delayedStart = ui->delayedStart_spinBox->value();
    newGeneral.voltageMax = ui->voltageMax_spinBox->value();
    newGeneral.amperMax = ui->voltageMax_spinBox->value();
    newGeneral.voltageShiftA = ui->voltageShiftA_spinBox->value();
    newGeneral.voltageShiftB = ui->voltageShiftB_spinBox->value();
    newGeneral.voltageShiftC = ui->voltageShiftC_spinBox->value();
    newGeneral.resolvingTime = ui->repeated_spinBox->value();
    newGeneral.deadTime = ui->deadTime_spinBox->value();
    newGeneral.thrA = ui->thrA_doubleSpinBox->value();
    newGeneral.thrB = ui->thrB_doubleSpinBox->value();
    newGeneral.thrC = ui->thrC_doubleSpinBox->value();
    newGeneral.timestamp = _general.timestamp;
    newGeneral.userId = _general.userId;

    if(newGeneral.record() != _general.record()) {
        if(db.update(&newGeneral)) {
            loadGeneral();
        }else {
            QMessageBox::warning(this,tr("Bład"),tr("Bład zapisu. Zmiany nie zostały zapisane."));
            return;
        }
    }
}

void SettingsDialog::on_saveConnection_pushButton_clicked()
{
    StarlingLab::DBRecordTDK db;
    StarlingLab::SettingConnectionModel newConnection;
    newConnection.id = _connection.id;

    newConnection.port = ui->port_comboBox->currentText();
    newConnection.braudRate = ui->baudRate_comboBox->currentText();
    newConnection.lBusAddress = ui->lBusAddress_spinBox->value();

    newConnection.deviceName = ui->deviceName_lineEdit->text();
    newConnection.isExtClk = ui->extClk_checkBox->isChecked();

    newConnection.timestamp = _connection.timestamp;
    newConnection.userId = _connection.userId;

    if(newConnection.record() != _connection.record()) {
        if(db.update(&newConnection)) {
            loadConnection();
        }else {
            QMessageBox::warning(this,tr("Błąd"),tr("Błąd zapisu. Zmiany nie zostały zapisane."));
            return;
        }

    }
}

void SettingsDialog::on_saveUser_pushButton_clicked()
{
    StarlingLab::DBRecordTDK db;
    StarlingLab::UserModel newUser;

    if(ui->users_comboBox->currentText() != _user.username) {
        //create new user
        newUser.id = 0;
        newUser.username = ui->username_lineEdit->text();
        newUser.password = ui->password_lineEdit->text();
        newUser.isActive = !ui->deactivateUser_checkBox->isChecked();
        newUser.firstName = ui->firstName_lineEdit->text();
        newUser.secondName = ui->secondName_lineEdit->text();
        newUser.lastName = ui->lastName_lineEdit->text();

        if(db.insert(&newUser)) {
            loadUser(newUser);
            this->accept();
        }else {
            QMessageBox::warning(this,tr("Błąd bazy danych"),tr("Nie udana próba dodania użytkownika.\nBłąd bazy danych."));
        }

    }else {
        newUser.id = _user.id;
        newUser.username = ui->username_lineEdit->text();
        newUser.password = ui->password_lineEdit->text();
        newUser.isActive = !ui->deactivateUser_checkBox->isChecked();
        newUser.firstName = ui->firstName_lineEdit->text();
        newUser.secondName = ui->secondName_lineEdit->text();
        newUser.lastName = ui->lastName_lineEdit->text();
        newUser.timestamp = _user.timestamp;
        newUser.userId = _user.userId;

        if(newUser.record() != _user.record()) {
            if(db.update(&newUser)) {
                loadUser(newUser);
            }else {
                QMessageBox::warning(this,tr("Bład"),tr("Bład zapisu. Zmiany nie zostały zapisane."));
                return;
            }
        }

    }
}

void SettingsDialog::on_users_comboBox_currentIndexChanged(const QString &arg1)
{
    StarlingLab::DBRecordTDK db;
    StarlingLab::UserModel selectUser = db.getUser(arg1);
    loadUser(selectUser);
}


void SettingsDialog::on_username_lineEdit_editingFinished()
{
    if(ui->username_lineEdit->text().isEmpty()) {
        QMessageBox::warning(this,tr("Błąd"),tr("Podaj nazwe użytkownika"));
        ui->username_lineEdit->setFocus();
        return;
    }

    if(ui->username_lineEdit->text() != _user.username) {
        //check available username
        StarlingLab::DBRecordTDK db;
        if(db.getUsernames().contains(ui->username_lineEdit->text())){
            QMessageBox::warning(this,tr("Błąd"),tr("Nazwa użytkownika istnieje.\nPodaj inną nazwe użytkownika."));
            ui->username_lineEdit->setFocus();
            return;
        }
    }
}


void SettingsDialog::on_createUser_pushButton_clicked()
{
    QString newUsername = QInputDialog::getText(this,tr("Nowy użytkownik"),tr("Podaj nową nazwe użytkownika"));
    if(newUsername.isEmpty())
        return;

    StarlingLab::DBRecordTDK db;
    if(db.getUsernames().contains(newUsername)){
        QMessageBox::warning(this,tr("Błąd"),tr("Nazwa użytkownika istnieje.\nPodaj inną nazwe użytkownika."));
        return;
    }
    QMessageBox::information(this,tr("Dane użytkonika"),tr("Proszę podać hasło i dane użytkownika.\nNastępnie naciśnij przycisk Zapisz."));
    ui->username_lineEdit->blockSignals(true);
    ui->username_lineEdit->setText(newUsername);
    ui->username_lineEdit->blockSignals(false);
    ui->password_lineEdit->clear();
    ui->password_lineEdit->setFocus();
    ui->firstName_lineEdit->clear();
    ui->secondName_lineEdit->clear();
    ui->lastName_lineEdit->clear();
    ui->lastModificationDateTimeUser_label->clear();

    ui->users_comboBox->blockSignals(true);
    ui->users_comboBox->addItem(newUsername);
    ui->users_comboBox->setCurrentText(newUsername);
    ui->users_comboBox->blockSignals(false);
}


void SettingsDialog::on_cancel_pushButton_clicked()
{
    this->close();
}


void SettingsDialog::on_connectionTestMAC3Counter_pushButton_clicked()
{
    MAC3Counter counter;

    if(counter.connect())
        QMessageBox::information(this,tr("Test"),tr("Połączono z urządzenie!"));
    else
        QMessageBox::warning(this,tr("Test"),tr("Brak połączenia z urządzeniem!\nSprawdż kabel lub nazwe urządzenia"));
    counter.disconnect();
}

