#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H
#include <QObject>
#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>

#include "dbcrystal.h"
#include "map.h"
#include "utils.h"

class ReportGenerator : public QObject
{
public:
    enum ReportForma {
        NAI = 0,

    }format;
    explicit ReportGenerator(const QString &fileName, QObject *parent = nullptr);
    ~ReportGenerator();

    void setMeasurementRegister(const CrystalMeasurementRegisterModel &reg);
    void setMeasurementProtocol(const CrystalMeasurementProtocolModel &protocol);
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
    CrystalMeasurementRegisterModel _reg;
    CrystalMeasurementProtocolModel _protocol;
    QVector<QStringList> _counts;

    void generatorNaI();

};

#endif // REPORTGENERATOR_H
