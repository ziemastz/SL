#ifndef STARLINGLAB_UTILS_H
#define STARLINGLAB_UTILS_H
#include <QStringList>
#include <QVariantList>
#include <QDateTime>
namespace StarlingLab {

class Utils
{
public:
    Utils();
    static QStringList toStringList(const QVariantList& values);
    static QString toString(const QVariant& value);
};

} // namespace StarlingLab

#endif // STARLINGLAB_UTILS_H
