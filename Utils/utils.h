#ifndef UTILS_H
#define UTILS_H
#include <QStringList>
#include <QVariantList>
#include <QDateTime>
#include <QSerialPortInfo>
class Utils
{
public:
    static QStringList availablePorts();
    static QString toString(const QVariant& value);
    static QStringList toStringList(const QVariantList& values);
};

#endif // UTILS_H
