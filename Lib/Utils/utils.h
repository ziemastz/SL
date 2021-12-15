#ifndef STARLINGLAB_UTILS_H
#define STARLINGLAB_UTILS_H
#include <QStringList>
#include <QVariantList>
#include <QDateTime>
#include <QSerialPortInfo>
#include <QTableWidget>
namespace StarlingLab {

class Utils
{
public:
    enum NuclideFormat {
        FirstAtom = 0,
        FirstSymbol =1
    };
    Utils();
    static QStringList toStringList(const QVariantList& values);

    static QString toString(const QVariant& value);
    static QStringList availablePorts();
    //widget
    static void clearTableWidget(QTableWidget *table);
    static void addItemTableWidget(QTableWidget *table, const QStringList& record);
    static void lastItemTableWidget(QTableWidget *table, const QStringList& record);
    static QStringList getLastItemTableWidget(QTableWidget *table);

    static QString formatNuclide(const QString& nuclide, const NuclideFormat& format = NuclideFormat::FirstAtom);

};

} // namespace StarlingLab

#endif // STARLINGLAB_UTILS_H
