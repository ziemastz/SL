#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H
#include <QObject>
#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>

#include "databasestarlinglab.h"
#include "map.h"
#include "utils.h"

class ReportGenerator : public QObject
{
public:
    enum ReportForma {
        TDK = 0,
        TD = 1,
        RES = 2
    }format;
    explicit ReportGenerator(const QString &fileName, QObject *parent = nullptr);
    ~ReportGenerator();

    void setMeasurementRegister(const TripleRegMeasurementRegisterModel &reg);
    void setMeasurementProtocol(const TripleRegMeasurementProtocolModel &protocol);
    void setCounts(const QVector<QStringList> &counts);
    void create();

    void appendLine(QChar fillChar = '=', int width = 80);
    void appendText(const QString &line);
    void appendText(const QStringList &lines);
    void appendList(const Map &list, QString sep = " | ");
    void appendTable(const QVector<QStringList> &table, QString sep = "");

signals:
private:
    QFile _file;
    QTextStream *_textStream;
    TripleRegMeasurementRegisterModel _reg;
    TripleRegMeasurementProtocolModel _protocol;
    QVector<QStringList> _counts;

    void generatorTDK();
    void generatorTD();
    void generatorRES();
};

#endif // REPORTGENERATOR_H
