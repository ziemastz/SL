#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "dialogsinginuser.h"
#include "databasestarlinglab.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
      QByteArray localMsg = msg.toLocal8Bit();
      const char *file = context.file ? context.file : "";
      const char *function = context.function ? context.function : "";
      QString txt;
      QDateTime date;

      QFile outFile(QDir::currentPath() + "/log.txt");
      if(outFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
      {
          QTextStream out(&outFile);
          switch (type) {
          case QtDebugMsg:
              txt.append(QString("Debug: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function));
              break;
          case QtInfoMsg:
              txt.append(QString("Info: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function));
              break;
          case QtWarningMsg:
              txt.append(QString("Warning: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function));
              break;
          case QtCriticalMsg:
              txt.append(QString("Critical: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function));
              break;
          case QtFatalMsg:
              txt.append(QString("Fatal: %1 (%2:%3, %4)").arg(localMsg.constData()).arg(file).arg(context.line).arg(function));
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
    //QCoreApplication::addLibraryPath(QDir::currentPath()+"/bin");
    QApplication a(argc, argv);
    QApplication::setApplicationName("TripleReg");
    QApplication::setApplicationVersion("1.0.0");
/*
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "TripleReg_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    */
    DatabaseStarlingLab db;
    db.createDatabase(":/db/sl.sql");

    DialogSingInUser signIn;
    if(signIn.exec() != QDialog::Accepted) {
        return 0;
    }
    qDebug() << "Logged user";
    MainWindow w;
    w.show();
    return a.exec();
}
