#ifndef DIALOGCREATEANACCOUNT_H
#define DIALOGCREATEANACCOUNT_H

#include <QDialog>
#include <QMessageBox>
#include <QInputDialog>

#include "dbcrystal.h"

namespace Ui {
class DialogCreateAnAccount;
}

class DialogCreateAnAccount : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCreateAnAccount(QWidget *parent = nullptr);
    ~DialogCreateAnAccount();

private slots:
    void on_username_lineEdit_editingFinished();

    void on_password_lineEdit_editingFinished();

    void on_confirmPassword_lineEdit_editingFinished();

    void on_singUp_pushButton_clicked();

    void on_cancel_pushButton_clicked();

private:
    Ui::DialogCreateAnAccount *ui;
};

#endif // DIALOGCREATEANACCOUNT_H
