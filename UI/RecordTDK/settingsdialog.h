#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>

#include "dbrecordtdk.h"
#include "utils.h"

#include "mac3counter.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(const int& userIdLogged, QWidget *parent = nullptr);
    ~SettingsDialog();

private slots:
    void on_saveGeneral_pushButton_clicked();

    void on_saveConnection_pushButton_clicked();

    void on_saveUser_pushButton_clicked();

    void on_users_comboBox_currentIndexChanged(const QString &arg1);

    void on_username_lineEdit_editingFinished();

    void on_createUser_pushButton_clicked();

    void on_cancel_pushButton_clicked();

    void on_connectionTestMAC3Counter_pushButton_clicked();

private:
    Ui::SettingsDialog *ui;

    StarlingLab::SettingGeneralModel _general;
    StarlingLab::SettingConnectionModel _connection;
    StarlingLab::UserModel _user;
    int _userIdLogged;

    void loadGeneral();
    void loadConnection();
    void loadUser(const StarlingLab::UserModel &user);
    void loadUser(const int &userId);
};

#endif // SETTINGSDIALOG_H
