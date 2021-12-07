#include "mainwindow.h"
#include "logindialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int ret = 0;
    LoginDialog login;
    if(login.exec() == QDialog::Accepted){

        MainWindow w;
        w.setUserIdLogged(login.getUsername());
        w.show();
        ret = a.exec();
    }
    return ret;
}
