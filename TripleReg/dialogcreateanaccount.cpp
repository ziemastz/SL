#include "dialogcreateanaccount.h"
#include "ui_dialogcreateanaccount.h"

DialogCreateAnAccount::DialogCreateAnAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCreateAnAccount)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    ui->username_lineEdit->setFocus();
}

DialogCreateAnAccount::~DialogCreateAnAccount()
{
    delete ui;
}

void DialogCreateAnAccount::on_username_lineEdit_editingFinished()
{
    //cheack avaible username
    /**
     * @brief db
     */
    DatabaseStarlingLab db;

    switch(db.isAvailableUsername(ui->username_lineEdit->text())) {
    case 1:
        ui->warnigUsername_label->clear();
        break;
    case 0:
        ui->warnigUsername_label->setText(tr("Ta nazwa użytkownika jest niedozwolona.\nSpróbuj inną?"));
        break;
    case -1:
        QMessageBox::warning(this,tr("Baza danych"),tr("Błąd odczytu z bazy danych!\nSkontaktuj się z administratorem."));
        break;
    }
}


void DialogCreateAnAccount::on_password_lineEdit_editingFinished()
{
    if(ui->password_lineEdit->text().size() < 3) {
        ui->warnigPassword_label->setText(tr("Minimum 3 znaki!"));
    }else {
        ui->warnigPassword_label->clear();
    }
}


void DialogCreateAnAccount::on_confirmPassword_lineEdit_editingFinished()
{
    if(ui->password_lineEdit->text() != ui->confirmPassword_lineEdit->text()) {
        ui->warnigConfirmPassword_label->setText(tr("Hasło musi być zgodne!"));
        ui->confirmPassword_lineEdit->setFocus();
    }else {
        ui->warnigConfirmPassword_label->clear();
    }
}


void DialogCreateAnAccount::on_singUp_pushButton_clicked()
{
    if(!ui->warnigConfirmPassword_label->text().isEmpty() || !ui->warnigPassword_label->text().isEmpty() || !ui->warnigUsername_label->text().isEmpty()) {
        QMessageBox::warning(this,tr("Bład"),tr("Błędne dane logowania.\nProszę sprawdzić i spróbować ponownie."));
        return;
    }

    if(ui->firstName_lineEdit->text().isEmpty() || ui->lastName_lineEdit->text().isEmpty()) {
        QMessageBox::warning(this,tr("Bład"),tr("Brak imienia i nazwiska.\nNależy podać imię i nazwisko."));
        return;
    }
    bool ok;

    QString password = QInputDialog::getText(this,tr("Autoryzacja"),tr("Wprowadź hasło administratora"),QLineEdit::Password,QString(),&ok);
    if(ok && !password.isEmpty()) {
        DatabaseStarlingLab db;
        int approvingUserId = db.signInUser("admin",password);
        if(approvingUserId > 0) {
            UserModel newUser;
            newUser.id = 0;
            newUser.username = ui->username_lineEdit->text();
            newUser.password = ui->password_lineEdit->text();
            newUser.degree = ui->degree_lineEdit->text();
            newUser.firstName = ui->firstName_lineEdit->text();
            newUser.secondName = ui->secondName_lineEdit->text();
            newUser.lastName = ui->lastName_lineEdit->text();
            newUser.isActive = 1;
            newUser.userId = approvingUserId;

            if(db.insert(&newUser)){
                accept();
            }else {
                QMessageBox::warning(this,tr("Baza danych"),tr("Błąd zapisu do bazy danych!\nSkontaktuj się z administratorem."));
                return;
            }
        }else {
            QMessageBox::warning(this,tr("Autoryzacja"),tr("Błąd autoryzacji!\nProszę spróbować ponownie?"));
            return;
        }

    }
}


void DialogCreateAnAccount::on_cancel_pushButton_clicked()
{
    close();
}

