#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "dialogsinginuser.h"
#include "databasestarlinglab.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
      QByteArray localMsg = msg.toLocal8Bit();
      QString txt;
      QDateTime date;

      QFile outFile(QDir::currentPath() + "/log.txt");
      if(outFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
      {
          QTextStream out(&outFile);
          switch (type) {
          case QtDebugMsg:
              txt.append(QString("Debug: %1").arg(localMsg.constData()));
              break;
          case QtInfoMsg:
              txt.append(QString("Info: %1").arg(localMsg.constData()));
              break;
          case QtWarningMsg:
              txt.append(QString("Warning: %1").arg(localMsg.constData()));
              break;
          case QtCriticalMsg:
              txt.append(QString("Critical: %1").arg(localMsg.constData()));
              break;
          case QtFatalMsg:
              txt.append(QString("Fatal: %1").arg(localMsg.constData()));
              abort();
          }
          txt.prepend(" - ");
          txt.prepend(date.currentDateTime().toString("dd-MM-yyyy hh:mm:ss.zzz"));
          txt.append("\n");
          out << txt;
          outFile.close();
      }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
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
