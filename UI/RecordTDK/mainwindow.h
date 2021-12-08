#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include "logindialog.h"
#include "settingsdialog.h"
// #include "monitoringdialog.h"
#include "Model/usermodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   void setUserIdLogged(const QString& username);

private slots:
    void on_settings_pushButton_clicked();

    void on_monitoring_pushButton_clicked();

    void on_add_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    int _userIdLogged;
};
#endif // MAINWINDOW_H
