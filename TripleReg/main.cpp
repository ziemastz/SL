#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "dialogsinginuser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "TripleReg_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    DialogSignInUser signIn;
    if(signIn.exec() != QDialog::Accepted) {
        return 0;
    }
    MainWindow w;
    w.show();
    return a.exec();
}
