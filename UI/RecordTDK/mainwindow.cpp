#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUserIdLogged(const QString &username)
{
    Database::DBRecordTDK db;
    _userIdLogged = db.getUser(username).id;
}

void MainWindow::on_settings_pushButton_clicked()
{
    SettingsDialog setting(_userIdLogged);
    setting.exec();
    this->show();
    this->setFocus();
}

void MainWindow::on_monitoring_pushButton_clicked()
{
    MonitoringDialog monitoring(_userIdLogged);
    if(monitoring.init())
        monitoring.exec();
}
