#include "dialogsinginuser.h"
#include "ui_dialogsinginuser.h"

DialogSingInUser::DialogSingInUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSingInUser)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    this->setFocus();
    ui->username_lineEdit->setFocus();
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
    DialogCreateAnAccount createAnAccount;
    if(createAnAccount.exec() == QDialog::Accepted) {
        QMessageBox::information(this,tr("Account"),tr("Congratulations, the new user has been successfully created.\nPlease sing in now with your username and password."));
    }
}


void DialogSingInUser::on_signIn_pushButton_clicked()
{
    DatabaseStarlingLab db;
    int _loggedUserId = db.signInUser(ui->username_lineEdit->text(),ui->password_lineEdit->text());
    if(_loggedUserId > 0) {
        Settings::setLoggedUserId(_loggedUserId);
        accept();
    }else {
        QMessageBox::warning(this,tr("Login error"),tr("The username or password is incorrect.\nPlease check and try again."));
    }
}
