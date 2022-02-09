#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H
#include <QObject>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "databasestarlinglab.h"
#include "map.h"

class ReportGenerator : public QObject
{
public:
    explicit ReportGenerator(const QString &fileName, QObject *parent = nullptr);
    ~ReportGenerator();

    void setMeasurementRegister(const TripleRegMeasurementRegisterModel &reg);
    void setMeasurementProtocol(const TripleRegMeasurementProtocolModel &protocol);
    void setCounts(const QVector<QStringList> &counts);
    void create();

    void appendLine(QChar fillChar = '=', int width = 80);
    void appendText(const QString &line);
    void appendText(const QStringList &lines);
    void appendList(const Map &list);
    void appendTable(const QVector<QStringList> &table);

signals:
private:
    QFile _file;
    QTextStream *_textStream;
    TripleRegMeasurementRegisterModel _reg;
    TripleRegMeasurementProtocolModel _protocol;
    QVector<QStringList> _counts;
};

#endif // REPORTGENERATOR_H
