#include "utils.h"

namespace StarlingLab {

Utils::Utils()
{
}

QStringList Utils::toStringList(const QVariantList &values)
{
    QStringList ret;
    foreach(QVariant value, values) {
        ret << toString(value);
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

QStringList Utils::availablePorts()
{
    QStringList ret;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
                ret << info.portName();
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
    table->blockSignals(false);
}

void Utils::lastItemTableWidget(QTableWidget *table, const QStringList &record)
{
    if(record.count() != table->columnCount())
        return;
    int rows = table->rowCount();
    int columns = table->columnCount();
    table->blockSignals(true);
    for(int j=0;j<columns;j++) {
        table->setItem(rows-1,j,new QTableWidgetItem(record.at(j)));
    }
    table->resizeColumnsToContents();
    table->blockSignals(false);
}

QStringList Utils::getLastItemTableWidget(QTableWidget *table)
{
    int row = table->rowCount()-1;
    int columns = table->columnCount();
    QStringList ret;
    for (int j=0; j<columns; j++) {
        ret << table->item(row,j)->text();
    }
    return ret;
}

QString Utils::formatNuclide(const QString &nuclide, const NuclideFormat &format)
{
    QString ret;
    switch (format) {
    case FirstAtom:
        if(nuclide.contains("-")) {
            QStringList elements = nuclide.split("-");
            if(elements.count()==2){
                ret = elements.at(1)+elements.at(0);
            }else {
                ret = nuclide;
            }
        }else {
           ret = nuclide;
        }
        break;
    case FirstSymbol:
        if(nuclide.contains("-")) {
            ret = nuclide;
        }else {
            QStringList elemets = QStringList() << QString() << QString();
            for(int i=0; i<nuclide.size(); i++) {
                bool check;
                QString(nuclide.at(i)).toInt(&check,10);
                if(check) {
                    elemets[0].append(nuclide.at(i));
                }else{
                    elemets[1].append(nuclide.at(i));
                }

            }
            ret = elemets.at(1)+"-"+elemets.at(0);
        }
        break;

    }
    return ret;
}

} // namespace StarlingLab
