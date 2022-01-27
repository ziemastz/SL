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

    static QString toString(const QVariant& value);
    static QStringList toStringList(const QVariantList& values);

    static void clearTableWidget(QTableWidget *table);
    static void addItemTableWidget(QTableWidget *table, const QStringList& record);
};

#endif // UTILS_H
