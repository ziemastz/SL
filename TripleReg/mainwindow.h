#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>

#include "utils.h"
#include "settings.h"
#include "databasestarlinglab.h"

#include "powersupplyn1470.h"
#include "mac3counter.h"

#include "dialogprotocol.h"
#include "dialogmeasurementprocess.h"
#include "dialogmeasurementreport.h"
#include "dialogaddeven.h"

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

    void on_cancelNewMeasurement_pushButton_clicked();

    void on_settings_pushButton_clicked();

    void on_saveGeneralSettings_pushButton_clicked();

    void on_saveUserDatapushButton_clicked();

    void on_passwordChange_pushButton_clicked();

    void on_cancelSettings_pushButton_clicked();

    void on_connectionTestN1470_pushButton_clicked();

    void on_connectionTestMAC3Counter_pushButton_clicked();

    void on_addProtocol_pushButton_clicked();

    void on_removeProtocol_pushButton_clicked();

    void on_editProtocol_pushButton_clicked();

    void on_startNewMeasurement_pushButton_clicked();

    void on_saveSystemInfo_pushButton_clicked();

    void on_measReg_pushButton_clicked();

    void on_filterNuclide_comboBox_currentIndexChanged(const QString &arg1);

    void on_filterSolution_comboBox_currentIndexChanged(const QString &arg1);

    void on_measurementRegister_tableWidget_cellDoubleClicked(int row, int column);

    void on_logbook_pushButton_clicked();

    void on_addEventLogbook_pushButton_clicked();

    void on_rootFilter_comboBox_currentIndexChanged(const QString &arg1);

    void on_elementFilter_comboBox_currentIndexChanged(const QString &arg1);

    void on_sourceNo_spinBox_valueChanged(int arg1);

    void on_isBlank_checkBox_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    UserModel user;
};
#endif // MAINWINDOW_H
