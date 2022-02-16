#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addFormSystem();
    ui->stackedWidget->setCurrentIndex(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addFormSystem()
{
    ui->newA_widget->setSystemLabel("A");
    ui->newB_widget->setSystemLabel("B");
    ui->newC_widget->setSystemLabel("C");
    ui->newD_widget->setSystemLabel("D");
}

void MainWindow::on_exit_pushButton_clicked()
{
    //messageboc are you sure and finished measurement
    close();
}

void MainWindow::on_newMeasurement_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_cancelSettings_pushButton_clicked()
{
    on_measurementRegister_pushButton_clicked();
}

void MainWindow::on_measurementRegister_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_saveSettings_pushButton_clicked()
{
    DBCrystal db;
    CrystalSettingModel settings;
    if(!db.select(1,&settings)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    settings.blankTime = ui->blankTimeDefault_spinBox->value();
    settings.sourceTime = ui->sourceTimeDefault_spinBox->value();
    settings.repeat = ui->repeatDefault_spinBox->value();
    settings.deviceName = ui->deviceName_lineEdit->text();
    settings.userId = Settings::loggedUserId();

    if(!db.update(&settings)) {
        QMessageBox::warning(this,tr("Update error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    QMessageBox::information(this,tr("Settings"),tr("Changes have been saved."));
}



void MainWindow::on_settings_pushButton_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(1);
    DBCrystal db;
    //general
    CrystalSettingModel settings;
    if(!db.select(1,&settings)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
    }else {
        ui->blankTimeDefault_spinBox->setValue(settings.blankTime);
        ui->sourceTimeDefault_spinBox->setValue(settings.sourceTime);
        ui->repeatDefault_spinBox->setValue(settings.repeat);
        ui->deviceName_lineEdit->setText(settings.deviceName);
    }

    //protocol
    CrystalProtocolModel protocol;
    if(!db.select(1,&protocol)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
    }else {
        ui->anodeVoltage_doubleSpinBox->setValue(protocol.anodeVoltage);
        ui->thresholdVoltage_doubleSpinBox->setValue(protocol.thresholdVoltage);
        ui->extendableDeadTime_doubleSpinBox->setValue(protocol.extendableDeadTime);
        ui->notes_plainTextEdit->setPlainText(protocol.notes);
    }

    if(!db.select(2,&protocol)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
    }else {
        ui->anodeVoltage_doubleSpinBox_2->setValue(protocol.anodeVoltage);
        ui->thresholdVoltage_doubleSpinBox_2->setValue(protocol.thresholdVoltage);
        ui->extendableDeadTime_doubleSpinBox_2->setValue(protocol.extendableDeadTime);
        ui->notes_plainTextEdit_2->setPlainText(protocol.notes);
    }

    if(!db.select(3,&protocol)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
    }else {
        ui->anodeVoltage_doubleSpinBox_3->setValue(protocol.anodeVoltage);
        ui->thresholdVoltage_doubleSpinBox_3->setValue(protocol.thresholdVoltage);
        ui->extendableDeadTime_doubleSpinBox_3->setValue(protocol.extendableDeadTime);
        ui->notes_plainTextEdit_3->setPlainText(protocol.notes);
    }

    if(!db.select(4,&protocol)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
    }else {
        ui->anodeVoltage_doubleSpinBox_4->setValue(protocol.anodeVoltage);
        ui->thresholdVoltage_doubleSpinBox_4->setValue(protocol.thresholdVoltage);
        ui->extendableDeadTime_doubleSpinBox_4->setValue(protocol.extendableDeadTime);
        ui->notes_plainTextEdit_4->setPlainText(protocol.notes);
    }

    //system info
    CrystalMeasuringSystemModel system;
    if(!db.select(1,&system)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
    }else {
        ui->systemNumberA_lineEdit->setText(system.numberA);
        ui->systemNumberB_lineEdit->setText(system.numberB);
        ui->systemNumberC_lineEdit->setText(system.numberC);
        ui->systemNumberD_lineEdit->setText(system.numberD);
        ui->systemName_lineEdit->setText(system.name);
        ui->systemFullName_plainTextEdit->setPlainText(system.fullName);
        ui->systemMeasrProcedureName_plainTextEdit->setPlainText(system.measuremntProcedureName);
        ui->systemLocation_lineEdit->setText(system.location);
        ui->systemNotes_plainTextEdit->setPlainText(system.notes);
    }

    //user
    UserModel user;
    if(!db.select(Settings::loggedUserId(),&user)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
    }else {
        ui->username_lineEdit->setText(user.username);
        ui->degree_lineEdit->setText(user.degree);
        ui->firstName_lineEdit->setText(user.firstName);
        ui->secondName_lineEdit->setText(user.secondName);
        ui->lastName_lineEdit->setText(user.lastName);

    }

}

void MainWindow::on_connectionTestNaICounter_pushButton_clicked()
{
    Counter counter;
    counter.setDeviceName(ui->deviceName_lineEdit->text());
    if(counter.isConnect()) {
        QMessageBox::information(this,tr("Connection test"),tr("Successful connection to the device!"));
    }else {
        QMessageBox::warning(this,tr("Connetion test"),tr("Connection failed! Check device name and the USB cable."));
    }
}

void MainWindow::on_saveProtocolo_pushButton_clicked()
{
    DBCrystal db;
    CrystalProtocolModel protocol;
    if(!db.select(1,&protocol)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    protocol.anodeVoltage = ui->anodeVoltage_doubleSpinBox->value();
    protocol.thresholdVoltage = ui->thresholdVoltage_doubleSpinBox->value();
    protocol.extendableDeadTime = ui->extendableDeadTime_doubleSpinBox->value();
    protocol.notes = ui->notes_plainTextEdit->toPlainText();
    protocol.userId = Settings::loggedUserId();

    if(!db.update(&protocol)) {
        QMessageBox::warning(this,tr("Update error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    QMessageBox::information(this,tr("Settings"),tr("Changes have been saved."));
}


void MainWindow::on_saveProtocolo_pushButton_2_clicked()
{
    DBCrystal db;
    CrystalProtocolModel protocol;
    if(!db.select(2,&protocol)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    protocol.anodeVoltage = ui->anodeVoltage_doubleSpinBox_2->value();
    protocol.thresholdVoltage = ui->thresholdVoltage_doubleSpinBox_2->value();
    protocol.extendableDeadTime = ui->extendableDeadTime_doubleSpinBox_2->value();
    protocol.notes = ui->notes_plainTextEdit_2->toPlainText();
    protocol.userId = Settings::loggedUserId();

    if(!db.update(&protocol)) {
        QMessageBox::warning(this,tr("Update error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    QMessageBox::information(this,tr("Settings"),tr("Changes have been saved."));
}


void MainWindow::on_saveProtocolo_pushButton_3_clicked()
{
    DBCrystal db;
    CrystalProtocolModel protocol;
    if(!db.select(3,&protocol)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    protocol.anodeVoltage = ui->anodeVoltage_doubleSpinBox_3->value();
    protocol.thresholdVoltage = ui->thresholdVoltage_doubleSpinBox_3->value();
    protocol.extendableDeadTime = ui->extendableDeadTime_doubleSpinBox_3->value();
    protocol.notes = ui->notes_plainTextEdit_3->toPlainText();
    protocol.userId = Settings::loggedUserId();

    if(!db.update(&protocol)) {
        QMessageBox::warning(this,tr("Update error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    QMessageBox::information(this,tr("Settings"),tr("Changes have been saved."));
}


void MainWindow::on_saveProtocolo_pushButton_4_clicked()
{
    DBCrystal db;
    CrystalProtocolModel protocol;
    if(!db.select(4,&protocol)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    protocol.anodeVoltage = ui->anodeVoltage_doubleSpinBox_4->value();
    protocol.thresholdVoltage = ui->thresholdVoltage_doubleSpinBox_4->value();
    protocol.extendableDeadTime = ui->extendableDeadTime_doubleSpinBox_4->value();
    protocol.notes = ui->notes_plainTextEdit_4->toPlainText();
    protocol.userId = Settings::loggedUserId();

    if(!db.update(&protocol)) {
        QMessageBox::warning(this,tr("Update error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    QMessageBox::information(this,tr("Settings"),tr("Changes have been saved."));
}


void MainWindow::on_saveSystem_pushButton_clicked()
{
    DBCrystal db;
    CrystalMeasuringSystemModel system;
    if(!db.select(1,&system)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    system.numberA = ui->systemNumberA_lineEdit->text();
    system.numberB = ui->systemNumberB_lineEdit->text();
    system.numberC = ui->systemNumberC_lineEdit->text();
    system.numberD = ui->systemNumberD_lineEdit->text();
    system.name = ui->systemName_lineEdit->text();
    system.fullName = ui->systemFullName_plainTextEdit->toPlainText();
    system.measuremntProcedureName = ui->systemMeasrProcedureName_plainTextEdit->toPlainText();
    system.notes = ui->systemNotes_plainTextEdit->toPlainText();
    system.userId = Settings::loggedUserId();

    if(!db.update(&system)) {
        QMessageBox::warning(this,tr("Update error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    QMessageBox::information(this,tr("Settings"),tr("Changes have been saved."));
}


void MainWindow::on_passwordChange_pushButton_clicked()
{
    DBCrystal db;
    UserModel user;
    if(!db.select(Settings::loggedUserId(),&user)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
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
            if(newPassword.size() < 3) {
                QMessageBox::warning(this,tr("New password"),tr("Password too short!\nEnter at least 3 characters."));
                return;
            }

            QString confirmNewPassword = QInputDialog::getText(this,tr("Password change"),
                                                            tr("Confirm new password"), QLineEdit::Password,
                                                            QString(),&ok);
            if (ok && !confirmNewPassword.isEmpty()) {
                if(newPassword != confirmNewPassword) {
                    QMessageBox::warning(this,tr("Database"),tr("Wrong password!\nPlease try again."));
                    return;
                }
                user.password = newPassword;
                if(!db.update(&user)) {
                    QMessageBox::warning(this,tr("Database"),tr("Updating error from database!\nPlease contact the administrator."));
                }else {
                    QMessageBox::information(this,tr("Password change"),tr("Your password has been successfully changed."));
                }
            }
        }
    }
}


void MainWindow::on_saveUser_pushButton_clicked()
{
    DBCrystal db;
    UserModel user;
    if(!db.select(Settings::loggedUserId(),&user)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    user.degree = ui->degree_lineEdit->text();
    user.firstName = ui->firstName_lineEdit->text();
    user.secondName = ui->secondName_lineEdit->text();
    user.lastName = ui->lastName_lineEdit->text();
    user.userId = Settings::loggedUserId();

    if(!db.update(&user)) {
        QMessageBox::warning(this,tr("Update error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    QMessageBox::information(this,tr("Settings"),tr("Changes have been saved."));
}

