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

    static QString toString(const QVariant& value);
    static QStringList toStringList(const QVariantList& values);
    static QVector<int> toVectorInt(const QString& str);
    static QStringList toStringList(const QVector<int>& tab);

    static QString generatorMeasurementId(const int &systemId, const int &id);

    static void clearTableWidget(QTableWidget *table);
    static void addItemTableWidget(QTableWidget *table, const QStringList& record);
    static void updateLastItemTableWidget(QTableWidget *table, const QStringList& record);
};

#endif // UTILS_H
