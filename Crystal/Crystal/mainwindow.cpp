#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addFormSystem();
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
    DBCrystal db;
    //general
    CrystalSettingModel settings;
    if(!db.select(1,&settings)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    ui->blankTimeDefault_spinBox->setValue(settings.blankTime);
    ui->sourceTimeDefault_spinBox->setValue(settings.sourceTime);
    ui->repeatDefault_spinBox->setValue(settings.repeat);
    ui->deviceName_lineEdit->setText(settings.deviceName);

    //protocol
    CrystalProtocolModel protocol;
    if(!db.select(1,&protocol)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    ui->anodeVoltage_doubleSpinBox->setValue(protocol.anodeVoltage);
    ui->thresholdVoltage_doubleSpinBox->setValue(protocol.thresholdVoltage);
    ui->extendableDeadTime_doubleSpinBox->setValue(protocol.extendableDeadTime);
    ui->notes_plainTextEdit->setPlainText(protocol.notes);

    if(!db.select(2,&protocol)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    ui->anodeVoltage_doubleSpinBox_2->setValue(protocol.anodeVoltage);
    ui->thresholdVoltage_doubleSpinBox_2->setValue(protocol.thresholdVoltage);
    ui->extendableDeadTime_doubleSpinBox_2->setValue(protocol.extendableDeadTime);
    ui->notes_plainTextEdit_2->setPlainText(protocol.notes);

    if(!db.select(3,&protocol)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    ui->anodeVoltage_doubleSpinBox_3->setValue(protocol.anodeVoltage);
    ui->thresholdVoltage_doubleSpinBox_3->setValue(protocol.thresholdVoltage);
    ui->extendableDeadTime_doubleSpinBox_3->setValue(protocol.extendableDeadTime);
    ui->notes_plainTextEdit_3->setPlainText(protocol.notes);

    if(!db.select(4,&protocol)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    ui->anodeVoltage_doubleSpinBox_4->setValue(protocol.anodeVoltage);
    ui->thresholdVoltage_doubleSpinBox_4->setValue(protocol.thresholdVoltage);
    ui->extendableDeadTime_doubleSpinBox_4->setValue(protocol.extendableDeadTime);
    ui->notes_plainTextEdit_4->setPlainText(protocol.notes);

    //system info
    CrystalMeasuringSystemModel system;
    if(!db.select(1,&system)) {
        QMessageBox::warning(this,tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."));
        return;
    }
    ui->systemNumberA_lineEdit->setText(system.numberA);
    ui->systemNumberB_lineEdit->setText(system.numberB);
    ui->systemNumberC_lineEdit->setText(system.numberC);
    ui->systemNumberD_lineEdit->setText(system.numberD);

}

