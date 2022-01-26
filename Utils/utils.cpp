#include "utils.h"

QStringList Utils::availablePorts()
{
    QStringList ret;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
                ret << info.portName();
    }
    return ret;
}

QString Utils::toString(const QVariant &value)
{
    QString ret;
    switch (value.userType()) {
    case QMetaType::QDateTime:
        ret = "'"+value.toDateTime().toString("yyyy-MM-dd hh:mm:ss")+"'";
        break;
    case QMetaType::QDate:
        ret = "'"+value.toDate().toString("yyyy-MM-dd")+"'";
        break;
    case QMetaType::Bool:
        ret = QString::number(value.toInt());
        break;
    case QMetaType::QStringList:
        ret = "'"+value.toStringList().join("|")+"'";
        break;
    case QMetaType::Int:
        ret = QString::number(value.toInt());
        break;
    case QMetaType::Double:
        ret = QString::number(value.toDouble());
        break;
    default:
        ret = "'"+value.toString()+"'";
        break;
    }
    if(ret == "'CURRENT_TIMESTAMP'") {
        ret = ret.remove("'");
    }
    return ret;
}

QStringList Utils::toStringList(const QVariantList &values)
{
    QStringList ret;
    foreach(QVariant value, values) {
        ret << toString(value);
    }
    return ret;
}
