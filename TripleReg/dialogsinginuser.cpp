#include "dialogsinginuser.h"
#include "ui_dialogsinginuser.h"

DialogSingInUser::DialogSingInUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSingInUser)
{
    ui->setupUi(this);
}

DialogSingInUser::~DialogSingInUser()
{
    delete ui;
}

void DialogSingInUser::on_exit_pushButton_clicked()
{
    close();
}


void DialogSingInUser::on_forgotPassword_pushButton_clicked()
{
    //TODO in future: open dialog with form to send email
    QMessageBox::information(this,tr("Forgot password"),tr("Please contact the TripleReg administrator."));
}


void DialogSingInUser::on_signUp_pushButton_clicked()
{
    QMessageBox::information(this,tr("Forgot password"),tr("Please contact the TripleReg administrator."));
}


void DialogSingInUser::on_signIn_pushButton_clicked()
{
    DatabaseStarlingLab db;
    int _loggedUserId = db.singInUser(ui->username_lineEdit->text(),ui->password_lineEdit);
    if(_loggedUserId > 0) {
        Setting::setLoggeduserId(_loggedUserId);
        accept();
    }else {
        QMessageBox::warning(this,tr("Login error"),tr("The username or password is incorrect.\nPlease check and try again."));
    }
}

int DialogSingInUser::loggedUserId() const
{
    return _loggedUserId;
}

