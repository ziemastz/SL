#include "reportgenerator.h"

ReportGenerator::ReportGenerator(const QString &fileName, QObject *parent) : QObject(parent)
{
    _file.setFileName(fileName);
    if(QFile::exists(fileName))
        QFile::remove(fileName);
    if(!_file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        qWarning() << tr("File write error! ")+_file.errorString();
    _textStream = new QTextStream(&_file);
    QFileInfo info(_file);
    QString suffix = info.suffix();
    if(suffix == "nai")
        format = ReportForma::NAI;

}

ReportGenerator::~ReportGenerator()
{
    delete _textStream;
    _file.close();
}

void ReportGenerator::setMeasurementRegister(const CrystalMeasurementRegisterModel &reg)
{
    _reg = reg;
}

void ReportGenerator::setMeasurementProtocol(const CrystalMeasurementProtocolModel &protocol)
{
    _protocol = protocol;
}

void ReportGenerator::setCounts(const QVector<QStringList> &counts)
{
    _counts = counts;
}

void ReportGenerator::create()
{
    switch (format) {
    case ReportGenerator::NAI:
        generatorNaI();
        break;
    }
}

void ReportGenerator::appendLine(QChar fillChar, int width)
{
    QString line;
    for(int i=0; i<width;i++)
        line.append(fillChar);
    appendText(line);
}

void ReportGenerator::appendText(const QString &line)
{
   *_textStream << line << "\n";
}

void ReportGenerator::appendText(const QStringList &lines)
{
    foreach(QString line, lines)
        appendText(line);
}

void ReportGenerator::appendList(const Map &list, QString sep)
{
    int maxWidth = 0;
    QList<QString> keys = list.keys();
    QList<QString> values = list.values();

    foreach(QString key,keys){
        if(key.size() > maxWidth)
            maxWidth = key.size();
    }
    maxWidth += 2; //size border :)

    for(int i=0;i<keys.count();i++){
       appendText(QString("%1%2%3").arg(keys.at(i),maxWidth).arg(sep).arg(values.at(i)));
    }
}

void ReportGenerator::appendTable(const QVector<QStringList> &table, QString sep)
{
    int rows = table.count();
    int columns = table.first().count();
    if(sep.isEmpty()) {
        QVector<int> headersMaxWidth;
        for(int i=0; i<columns;i++){
            headersMaxWidth << 0;
            for(int j=0; j<rows;j++){
                if(headersMaxWidth.at(i) < table.at(j).at(i).size())
                    headersMaxWidth[i] = table.at(j).at(i).size();
            }
        }
        for(int i=0; i<rows; i++) {
            QString line;
            for(int j=0; j< columns; j++) {
                line.append(QString("%1").arg(table.at(i).at(j),headersMaxWidth.at(j)+2));
            }
            appendText(line);
        }
    }else {
        for(int i=0; i<rows; i++) {
            appendText(table.at(i).join(sep));
        }
    }
}



void ReportGenerator::generatorNaI()
{
    appendText("Crystal software (ver. "+QApplication::applicationVersion()+")");
    appendLine();
    Map list;

    list.insert("ID",_reg.measurementId);
    list.insert("Laboratory","POLATOM");
    list.insert("System",_reg.systemLabel);
    list.insert("Nuclide",_reg.nuclide);
    list.insert("Filename",_file.fileName());
    list.insert("Date",_reg.measurementDate);
    list.insert("Mode",_reg.category);
    list.insert("","");
    list.insert("Source ID",_reg.sourceId);
    list.insert("Geometry",_reg.geometry);
    list.insert("Source No",QString::number(_reg.sourceNo));
    list.insert("Last modification",_reg.lastModification);
    list.insert("","");
    list.insert("Parameters","");
    list.insert("HV Anode(V)",Utils::toString(_protocol.anodeVoltage).replace("|"," "));
    list.insert("Voltage threshold (V)",Utils::toString(_protocol.thresholdVoltage).replace("|"," "));
    list.insert("Dead-time(ns)",QString::number(_protocol.extendableDeadTime*1000));
    list.insert("Notes",_protocol.notes);
    list.insert("Last modification",_protocol.lastModification);
    list.insert("","");
    list.insert("Blank time(s)",QString::number(_reg.blankTime));
    list.insert("Source time(s)",QString::number(_reg.sourceTime));
    list.insert("Reps",QString::number(_reg.repeat));
    list.insert("Comment",_reg.comments);
    DBCrystal db;
    UserModel user;
    db.select(_reg.authorId,&user);
    list.insert("Made by",user.caption());
    db.select(_reg.acceptedId,&user);
    list.insert("Accepted by",user.caption()+" "+_reg.acceptedDateTime);
    appendList(list,"|");
    appendLine();

    appendTable(_counts);
}
