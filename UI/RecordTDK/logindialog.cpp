#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    this->setFocus();
    ui->username_lineEdit->setFocus();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

QString LoginDialog::getUsername()
{
    return ui->username_lineEdit->text();
}

void LoginDialog::on_exit_pushButton_clicked()
{
    this->reject();
}


void LoginDialog::on_login_pushButton_clicked()
{
    StarlingLab::DBRecordTDK db;
    if(db.loginUser(ui->username_lineEdit->text(),ui->password_lineEdit->text())){
        this->accept();
    }else {
        QMessageBox::warning(this,tr("Błąd logowania"),tr("Brak dostępu!"));
    }
}

