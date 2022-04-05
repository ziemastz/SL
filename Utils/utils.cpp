#include "utils.h"

QStringList Utils::availablePorts()
{
    QStringList ret;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
                ret << info.portName();
    }
    return ret;
}

QString Utils::currentDate()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd");
}

QString Utils::currentDateTime()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
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

QString Utils::toString(const QVector<int> &tab)
{
    QStringList ret;
    foreach(int val,tab)
        ret << QString::number(val);
    return ret.join("|");
}

QStringList Utils::toStringList(const QVariantList &values)
{
    QStringList ret;
    foreach(QVariant value, values) {
        ret << toString(value);
    }
    return ret;
}

void Utils::clearTableWidget(QTableWidget *table)
{
    int rows = table->rowCount();
    for(int i=0;i<rows;i++)
        table->removeRow(0);
}

void Utils::addItemTableWidget(QTableWidget *table, const QStringList &record)
{
    if(record.count() != table->columnCount())
        return;
    int rows = table->rowCount();
    int columns = table->columnCount();
    table->insertRow(rows);
    table->blockSignals(true);
    for(int j=0;j<columns;j++) {
        table->setItem(rows,j,new QTableWidgetItem(record.at(j)));
    }
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    table->blockSignals(false);
}

void Utils::updateLastItemTableWidget(QTableWidget *table, const QStringList &record)
{
    if(record.count() != table->columnCount())
        return;
    int rows = table->rowCount();
    int columns = table->columnCount();
    table->blockSignals(true);
    for(int j=0;j<columns;j++) {
        table->item(rows-1,j)->setText(record.at(j));
        //table->setItem(rows-1,j,new QTableWidgetItem(record.at(j)));
    }
    table->resizeColumnsToContents();
    table->blockSignals(false);
}

QVector<int> Utils::toVectorInt(const QString &str) {
    QVector<int> ret;
    QStringList list = str.split("|");
    foreach(QString val, list)
        ret << val.toInt();
    return ret;
}

QStringList Utils::toStringList(const QVector<int> &tab) {
    QStringList ret;
    foreach(int val,tab)
        ret << QString::number(val);
    return ret;
}

QString Utils::generatorMeasurementId(const int &systemId, const int &id)
{
    QString yy = QDateTime::currentDateTime().toString("yy");
    return QString("S%1-%2-%3").arg(systemId,2,10,QLatin1Char('0')).arg(yy).arg(id,3,10,QLatin1Char('0'));
}

QString Utils::generatorMeasurementId(const QString &systemId, const int &id)
{
    QString yy = QDateTime::currentDateTime().toString("yy");
    return QString("S%1-%2-%3").arg(systemId).arg(yy).arg(id,3,10,QLatin1Char('0'));
}

QString Utils::generatorTimeDHMSString(const int &leftTime)
{
    int minute = (int)((float)leftTime/60);
    int second = leftTime - (minute*60);
    int hour = (int)((float)minute/60);
    int day = (int)((float)hour/24);

    if(leftTime <= 60) {
        return QString("%1s").arg(leftTime);
    }else if(minute <= 60) {
        return QString("%1min %2s").arg(minute).arg(second);
    }else if(hour <= 24) {
        minute = minute - (hour*60);
        return QString("%1h %2min %3s").arg(hour).arg(minute).arg(second);
    }else {
        minute = minute - (hour*60);
        hour = hour - (day*24);
        return QString("%1d %2h %3min %4s").arg(day).arg(hour).arg(minute).arg(second);
    }
}

QString Utils::toString(const QVector<double> &tab)
{
    QStringList ret;
    foreach(double val,tab)
        ret << QString::number(val);
    return ret.join("|");
}
