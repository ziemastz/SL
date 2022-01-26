#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
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
    //clear & load
    // first clear
    ui->nuclide_lineEdit->clear();
    ui->solutionID_lineEdit->clear();
    ui->sourceID_lineEdit->clear();
    ui->sourceNo_spinBox->setValue(1);
    ui->isBlank_checkBox->setChecked(true);




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

