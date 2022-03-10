#include "dialogsinginuser.h"
#include "ui_dialogsinginuser.h"

DialogSingInUser::DialogSingInUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSingInUser)
{
    ui->setupUi(this);
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
    bool ok;
    QString password = QInputDialog::getText(this,tr("Autoryzacja"),tr("Wprowadź hasło administratora"),QLineEdit::Password,QString(),&ok);
    if(ok && !password.isEmpty()) {
        DatabaseStarlingLab db;
        int approvingUserId = db.signInUser("admin",password);
        if(approvingUserId > 0) {
            QString username = QInputDialog::getText(this,tr("Użytkownik"),tr("Wprowadź nazwe użytkownika"),QLineEdit::Normal,QString(),&ok);
            if(ok && !username.isEmpty()) {
                UserModel user;
                DatabaseResults result = db.select(&user,"username='"+username+"'");
                if(result.count() == 1){
                    user.setRecord(result.at(0)->record());
                    QString newPossword = QInputDialog::getText(this,tr("Nowe hasło"),tr("Podaj nowe hasło (min. 3 znaki"),QLineEdit::Password,QString(),&ok);
                    if(ok && !newPossword.isEmpty() && (newPossword.size() > 2)) {
                        QString confirmPassword = QInputDialog::getText(this,tr("Nowe hasło"),tr("Potwierdz nowe hasło"),QLineEdit::Password,QString(),&ok);
                        if(ok && !confirmPassword.isEmpty() && confirmPassword == newPossword) {

                        }else {
                            QMessageBox::warning(this,tr("Nowe hasło"),tr("Nieprawidłowe hasło!\nProszę spróbować ponownie?"));
                            return;
                        }
                    }
                }else {
                    QMessageBox::warning(this,tr("Użytkownik"),tr("Nieprawidłowa nazwa użytkonika!\nProszę spróbować ponownie?"));
                    return;
                }
            }
        }else {
            QMessageBox::warning(this,tr("Autoryzacja"),tr("Błąd autoryzacji!\nProszę spróbować ponownie?"));
            return;
        }

    }

    //QMessageBox::information(this,tr("Zapomiałeś hasło"),tr("Proszę skontaktuj się z administratorem programu TripleReg."));
}


void DialogSingInUser::on_signUp_pushButton_clicked()
{
    DialogCreateAnAccount createAnAccount;
    if(createAnAccount.exec() == QDialog::Accepted) {
        QMessageBox::information(this,tr("Nowe konto"),tr("Gratulacje, nowe konto zostało dodane..\nProsze zaloguj się uzywać nazwy użytkownika i hasła."));
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
        QMessageBox::warning(this,tr("Bład logowania"),tr("Nazwa użytkonika lub/i hasło podane jest nie prawidłowe.\nProsze sprawdź i spróbuj ponownie."));
    }
}
