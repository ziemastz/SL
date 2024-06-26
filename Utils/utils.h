#ifndef UTILS_H
#define UTILS_H
#include <QStringList>
#include <QVariantList>
#include <QDateTime>
#include <QSerialPortInfo>
#include <QTableWidget>

class Utils
{
public:
    static QStringList availablePorts();

    static QString currentDate();
    static QString currentDateTime();

    static QString toString(const QVariant& value);
    static QString toString(const QVector<int>& tab);
    static QString toString(const QVector<double>& tab);
    static QStringList toStringList(const QVariantList& values);
    static QVector<int> toVectorInt(const QString& str);
    static QStringList toStringList(const QVector<int>& tab);

    static QString generatorMeasurementId(const int &systemId, const int &id);
    static QString generatorMeasurementId(const QString &systemId, const int &id);
    static QString generatorTimeDHMSString(const int &leftTime);

    static void clearTableWidget(QTableWidget *table);
    static void addItemTableWidget(QTableWidget *table, const QStringList& record);
    static void updateLastItemTableWidget(QTableWidget *table, const QStringList& record);
};

#endif // UTILS_H
