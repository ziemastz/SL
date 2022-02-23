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
    threadA->quit();
    threadB->quit();
    threadC->quit();
    threadD->quit();
    delete threadA;
    delete threadB;
    delete threadC;
    delete threadD;

    delete workerA;
    delete workerB;
    delete workerC;
    delete workerD;

    delete counter;
    delete ui;
}

void MainWindow::showMsgBox(const QString &title, const QString &text, const int &portId)
{
    DialogMsgBox box(this);
    box.setTitle(title);
    box.setText(text);
    box.setPortId(portId);
    if(box.exec() == QDialog::Accepted) {
        emit acceptedMsgBox(portId);
    }else {
        emit rejectedMsgBox(portId);
    }
}

void MainWindow::addFormSystem()
{
    ui->newA_widget->setSystemLabel("A");
    ui->newB_widget->setSystemLabel("B");
    ui->newC_widget->setSystemLabel("C");
    ui->newD_widget->setSystemLabel("D");

    counter = new Counter();
    workerA = new WorkerMeasurement(NaICounter::PORT_A,counter);
    workerB = new WorkerMeasurement(NaICounter::PORT_B,counter);
    workerC = new WorkerMeasurement(NaICounter::PORT_C,counter);
    workerD = new WorkerMeasurement(NaICounter::PORT_D,counter);

    threadA = new QThread();
    threadB = new QThread();
    threadC = new QThread();
    threadD = new QThread();

    workerA->moveToThread(threadA);
    workerB->moveToThread(threadB);
    workerC->moveToThread(threadC);
    workerD->moveToThread(threadD);

    connect(ui->newA_widget,SIGNAL(startNewMeasurement(int)),workerA,SLOT(startNewMeasurement(int)));
    connect(ui->newB_widget,SIGNAL(startNewMeasurement(int)),workerB,SLOT(startNewMeasurement(int)));
    connect(ui->newC_widget,SIGNAL(startNewMeasurement(int)),workerC,SLOT(startNewMeasurement(int)));
    connect(ui->newD_widget,SIGNAL(startNewMeasurement(int)),workerD,SLOT(startNewMeasurement(int)));

    connect(ui->newA_widget,SIGNAL(abortMeasurement(int)),workerA,SLOT(abortMeasurement(int)));
    connect(ui->newB_widget,SIGNAL(abortMeasurement(int)),workerB,SLOT(abortMeasurement(int)));
    connect(ui->newC_widget,SIGNAL(abortMeasurement(int)),workerC,SLOT(abortMeasurement(int)));
    connect(ui->newD_widget,SIGNAL(abortMeasurement(int)),workerD,SLOT(abortMeasurement(int)));

    connect(workerA,SIGNAL(finished()),ui->newA_widget,SLOT(finished()));
    connect(workerB,SIGNAL(finished()),ui->newB_widget,SLOT(finished()));
    connect(workerC,SIGNAL(finished()),ui->newC_widget,SLOT(finished()));
    connect(workerD,SIGNAL(finished()),ui->newD_widget,SLOT(finished()));

    connect(workerA,SIGNAL(msgBox(QString,QString,int)),this,SLOT(showMsgBox(QString,QString,int)));
    connect(workerB,SIGNAL(msgBox(QString,QString,int)),this,SLOT(showMsgBox(QString,QString,int)));
    connect(workerC,SIGNAL(msgBox(QString,QString,int)),this,SLOT(showMsgBox(QString,QString,int)));
    connect(workerD,SIGNAL(msgBox(QString,QString,int)),this,SLOT(showMsgBox(QString,QString,int)));

    connect(this,SIGNAL(acceptedMsgBox(int)),workerA,SLOT(acceptedMsgBox(int)));
    connect(this,SIGNAL(acceptedMsgBox(int)),workerB,SLOT(acceptedMsgBox(int)));
    connect(this,SIGNAL(acceptedMsgBox(int)),workerC,SLOT(acceptedMsgBox(int)));
    connect(this,SIGNAL(acceptedMsgBox(int)),workerD,SLOT(acceptedMsgBox(int)));

    connect(this,SIGNAL(rejectedMsgBox(int)),workerA,SLOT(rejectedMsgBox(int)));
    connect(this,SIGNAL(rejectedMsgBox(int)),workerB,SLOT(rejectedMsgBox(int)));
    connect(this,SIGNAL(rejectedMsgBox(int)),workerC,SLOT(rejectedMsgBox(int)));
    connect(this,SIGNAL(rejectedMsgBox(int)),workerD,SLOT(rejectedMsgBox(int)));

    connect(workerA,SIGNAL(setNuclide(QString)),ui->newA_widget,SLOT(setNuclide(QString)));
    connect(workerB,SIGNAL(setNuclide(QString)),ui->newB_widget,SLOT(setNuclide(QString)));
    connect(workerC,SIGNAL(setNuclide(QString)),ui->newC_widget,SLOT(setNuclide(QString)));
    connect(workerD,SIGNAL(setNuclide(QString)),ui->newD_widget,SLOT(setNuclide(QString)));

    connect(workerA,SIGNAL(setSourceId(QString)),ui->newA_widget,SLOT(setSourceId(QString)));
    connect(workerB,SIGNAL(setSourceId(QString)),ui->newB_widget,SLOT(setSourceId(QString)));
    connect(workerC,SIGNAL(setSourceId(QString)),ui->newC_widget,SLOT(setSourceId(QString)));
    connect(workerD,SIGNAL(setSourceId(QString)),ui->newD_widget,SLOT(setSourceId(QString)));

    connect(workerA,SIGNAL(setGeometry(QString)),ui->newA_widget,SLOT(setGeometry(QString)));
    connect(workerB,SIGNAL(setGeometry(QString)),ui->newB_widget,SLOT(setGeometry(QString)));
    connect(workerC,SIGNAL(setGeometry(QString)),ui->newC_widget,SLOT(setGeometry(QString)));
    connect(workerD,SIGNAL(setGeometry(QString)),ui->newD_widget,SLOT(setGeometry(QString)));

    connect(workerA,SIGNAL(setProcess(QString)),ui->newA_widget,SLOT(setProcess(QString)));
    connect(workerB,SIGNAL(setProcess(QString)),ui->newB_widget,SLOT(setProcess(QString)));
    connect(workerC,SIGNAL(setProcess(QString)),ui->newC_widget,SLOT(setProcess(QString)));
    connect(workerD,SIGNAL(setProcess(QString)),ui->newD_widget,SLOT(setProcess(QString)));

    connect(workerA,SIGNAL(setEndTime(QString)),ui->newA_widget,SLOT(setEndTime(QString)));
    connect(workerB,SIGNAL(setEndTime(QString)),ui->newB_widget,SLOT(setEndTime(QString)));
    connect(workerC,SIGNAL(setEndTime(QString)),ui->newC_widget,SLOT(setEndTime(QString)));
    connect(workerD,SIGNAL(setEndTime(QString)),ui->newD_widget,SLOT(setEndTime(QString)));

    connect(workerA,SIGNAL(setCurrentRepeat(int)),ui->newA_widget,SLOT(setCurrentRepeat(int)));
    connect(workerB,SIGNAL(setCurrentRepeat(int)),ui->newB_widget,SLOT(setCurrentRepeat(int)));
    connect(workerC,SIGNAL(setCurrentRepeat(int)),ui->newC_widget,SLOT(setCurrentRepeat(int)));
    connect(workerD,SIGNAL(setCurrentRepeat(int)),ui->newD_widget,SLOT(setCurrentRepeat(int)));

    connect(workerA,SIGNAL(setRepeat(int)),ui->newA_widget,SLOT(setRepeat(int)));
    connect(workerB,SIGNAL(setRepeat(int)),ui->newB_widget,SLOT(setRepeat(int)));
    connect(workerC,SIGNAL(setRepeat(int)),ui->newC_widget,SLOT(setRepeat(int)));
    connect(workerD,SIGNAL(setRepeat(int)),ui->newD_widget,SLOT(setRepeat(int)));

    connect(workerA,SIGNAL(setActivity(double)),ui->newA_widget,SLOT(setActivity(double)));
    connect(workerB,SIGNAL(setActivity(double)),ui->newB_widget,SLOT(setActivity(double)));
    connect(workerC,SIGNAL(setActivity(double)),ui->newC_widget,SLOT(setActivity(double)));
    connect(workerD,SIGNAL(setActivity(double)),ui->newD_widget,SLOT(setActivity(double)));

    connect(workerA,SIGNAL(setCounts(double)),ui->newA_widget,SLOT(setCounts(double)));
    connect(workerB,SIGNAL(setCounts(double)),ui->newB_widget,SLOT(setCounts(double)));
    connect(workerC,SIGNAL(setCounts(double)),ui->newC_widget,SLOT(setCounts(double)));
    connect(workerD,SIGNAL(setCounts(double)),ui->newD_widget,SLOT(setCounts(double)));

    connect(workerA,SIGNAL(setDeadTime(double)),ui->newA_widget,SLOT(setDeadTime(double)));
    connect(workerB,SIGNAL(setDeadTime(double)),ui->newB_widget,SLOT(setDeadTime(double)));
    connect(workerC,SIGNAL(setDeadTime(double)),ui->newC_widget,SLOT(setDeadTime(double)));
    connect(workerD,SIGNAL(setDeadTime(double)),ui->newD_widget,SLOT(setDeadTime(double)));

    threadA->start();
    threadB->start();
    threadC->start();
    threadD->start();
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

