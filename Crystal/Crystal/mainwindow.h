#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>

#include "settings.h"
#include "dbcrystal.h"
#include "formnewmeasurement.h"
#include "counter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_exit_pushButton_clicked();

    void on_newMeasurement_pushButton_clicked();

    void on_cancelSettings_pushButton_clicked();

    void on_measurementRegister_pushButton_clicked();

    void on_saveSettings_pushButton_clicked();

    void on_settings_pushButton_clicked();

    void on_connectionTestNaICounter_pushButton_clicked();

    void on_saveProtocolo_pushButton_clicked();

    void on_saveProtocolo_pushButton_2_clicked();

    void on_saveProtocolo_pushButton_3_clicked();

    void on_saveProtocolo_pushButton_4_clicked();

    void on_saveSystem_pushButton_clicked();

    void on_passwordChange_pushButton_clicked();

    void on_saveUser_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void addFormSystem();
};
#endif // MAINWINDOW_H
