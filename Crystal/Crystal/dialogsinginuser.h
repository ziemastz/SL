#ifndef DIALOGSINGINUSER_H
#define DIALOGSINGINUSER_H

#include <QDialog>
#include <QMessageBox>

#include "settings.h"
#include "dbcrystal.h"
#include "dialogcreateanaccount.h"

namespace Ui {
class DialogSingInUser;
}

class DialogSingInUser : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSingInUser(QWidget *parent = nullptr);
    ~DialogSingInUser();

private slots:
    void on_exit_pushButton_clicked();

    void on_forgotPassword_pushButton_clicked();

    void on_signUp_pushButton_clicked();

    void on_signIn_pushButton_clicked();

private:
    Ui::DialogSingInUser *ui;
};

#endif // DIALOGSINGINUSER_H
