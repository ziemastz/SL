#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "dialogsinginuser.h"
#include "databasestarlinglab.h"

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("/bin");
    QApplication a(argc, argv);
    QApplication::setApplicationName("TripleReg");
    QApplication::setApplicationVersion("1.0.0");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "TripleReg_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    DatabaseStarlingLab db;
    db.createDatabase(":/db/sl.sql");

    DialogSingInUser signIn;
    if(signIn.exec() != QDialog::Accepted) {
        return 0;
    }
    MainWindow w;
    w.show();
    return a.exec();
}
