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
    if(suffix == "tdk")
        format = ReportForma::TDK;
    if(suffix == "td")
        format = ReportForma::TD;
    if(suffix == "res")
        format = ReportForma::RES;

}

ReportGenerator::~ReportGenerator()
{
    _file.close();
    delete _textStream;
}

void ReportGenerator::setMeasurementRegister(const TripleRegMeasurementRegisterModel &reg)
{
    _reg = reg;
}

void ReportGenerator::setMeasurementProtocol(const TripleRegMeasurementProtocolModel &protocol)
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
    case ReportGenerator::TDK:
        generatorTDK();
        break;
    case ReportGenerator::TD:
        generatorTD();
        break;
    case ReportGenerator::RES:
        generatorRES();
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

void ReportGenerator::generatorTDK()
{
    appendText("TripleReg software (ver. "+QApplication::applicationVersion()+")");
    appendLine();
    Map list;

    list.insert("ID",_reg.measurementId);
    list.insert("Nuclide",_reg.nuclide);
    list.insert("Date",_reg.measurementDate);
    list.insert("Solution ID",_reg.solutionId);
    list.insert("Source ID",_reg.sourceId);
    list.insert("Protocol name",_protocol.name+" (Last modification "+_protocol.lastModification+")");
    list.insert("","");
    list.insert("Linked",_reg.linked);
    list.insert("Category",_reg.category);
    list.insert("Comments",_reg.comments);
    list.insert("","");
    DatabaseStarlingLab db;
    UserModel user;
    db.select(_reg.authorId,&user);
    list.insert("Author",user.caption());
    db.select(_reg.userId,&user);
    list.insert("Last modification",_reg.lastModification+" "+user.caption());
    if(_reg.acceptedId > 0) {
        db.select(_reg.acceptedId,&user);
        list.insert("Accepted",user.caption()+" "+_reg.acceptedDateTime);
    }else {
        list.insert("Accepted","");
    }
    appendList(list);
    appendLine();
    appendTable(_counts);
}

void ReportGenerator::generatorTD()
{
    appendText("TripleReg software (ver. "+QApplication::applicationVersion()+")");
    appendLine();
    Map list;

    list.insert("ID",_reg.measurementId);
    list.insert("Laboratory","POLATOM");
    list.insert("Counter","TDK");
    list.insert("Nuclide",_reg.nuclide);
    list.insert("Filename",_file.fileName());
    list.insert("Date",_reg.measurementDate);
    list.insert("Mode",_reg.category);
    list.insert("","");
    list.insert("Sources Series",_reg.sourceId);
    list.insert("Solution",_reg.solutionId);
    list.insert("Dilution","1");
    list.insert("Mother solution","");
    list.insert("Scintillator","");
    list.insert("Volume scin.","");
    list.insert("Vial type","");
    QStringList vialNo;
    QStringList vialMass;
    for(int i=1; i <= _reg.sourceNo; i++){
        vialNo << QString::number(i);
        vialMass << "1";
    }
    list.insert("Number vials",vialNo.join(" "));
    list.insert("Mass (mg)",vialMass.join(" "));
    list.insert("Prepared by","");
    list.insert("Prepared at","");
    list.insert("Last modification",_reg.lastModification);
    list.insert("","");
    list.insert("Parameters",_protocol.name);
    list.insert("HV Anode(V)",Utils::toString(_protocol.anodaVoltage).replace("|"," "));
    list.insert("HV First Dynode(V)","660");
    list.insert("HV Focusing Dynode(V)",Utils::toString(_protocol.focusingVoltage).replace("|"," "));
    list.insert("HV Gamma(V)","0");
    list.insert("R1(ns)",QString::number(_protocol.resolvingTime));
    list.insert("DT1(ns)",QString::number(_protocol.deadTime*1000));
    list.insert("R2(ns)","0");
    list.insert("DT2(ns)","0");
    list.insert("DLB(ns)","0");
    list.insert("Lower window gamma","0");
    list.insert("Upper window gamma","0");
    list.insert("Last modification",_protocol.lastModification);
    list.insert("","");
    list.insert("Blank time(s)",QString::number(_reg.blankTime));
    list.insert("Source time(s)",QString::number(_reg.sourceTime));
    list.insert("Reps",QString::number(_reg.repeat));
    list.insert("Comment",_reg.comments);
    DatabaseStarlingLab db;
    UserModel user;
    db.select(_reg.authorId,&user);
    list.insert("Made by",user.caption());
    appendList(list,"|");
    appendLine();
    QVector<QStringList> countsTD;
    countsTD << (QStringList() << "Hour" << "So." << "Point" << "Tag" << "Reps" << "A" << "B" << "C" << "S" << "AB" << "BC" << "AC" << "T" << "D" << "LT" << "MT");
    QString pointTag("");
    int pointNo = 0;
    int sourceNo = -1;
    for(int i=1;i<_counts.count();i++){
        if(sourceNo != _counts.at(i).at(1).toInt()) {
           pointNo = 0;
           pointTag.clear();
           sourceNo = _counts.at(i).at(1).toInt();
        }
        if(pointTag != _counts.at(i).at(2)) {
            pointTag = _counts.at(i).at(2);
            pointNo++;
        }
        QStringList record;
        record << _counts.at(i).at(0).split(" ").at(1)
               << _counts.at(i).at(1)
               << QString::number(pointNo)
               << pointTag.replace(" ","")
               << _counts.at(i).at(3) // Repeat
               << _counts.at(i).at(4) // A
               << _counts.at(i).at(5)
               << _counts.at(i).at(6)
               << _counts.at(i).at(7)
               << _counts.at(i).at(8)
               << _counts.at(i).at(9)
               << _counts.at(i).at(10)
               << _counts.at(i).at(11)
               << _counts.at(i).at(12)
               << QString::number(qRound(_counts.at(i).at(15).toDouble()*66666)) //66666 Hz
               << QString::number(qRound(_counts.at(i).at(16).toDouble()*66666)); //66666 Hz
        countsTD << record;
    }

    appendTable(countsTD,"\t");
}

void ReportGenerator::generatorRES()
{
    appendText(QString("%1 %2").arg(_reg.measurementId+".res",_reg.measurementDate));
    appendText(QString("Nuklid:%1").arg(_reg.nuclide));
    appendText(QString("Komentarz: %1 %2 %3").arg(_reg.solutionId,_reg.sourceId,_reg.comments));
    appendText(QString("Scyntylator : %1").arg("UG"));
    appendText("Polokres rozpadu : 0y 0d 0h 0m");
    appendText("Niedokladnosc : 0.00000000000000E+0");
    appendText(QString::number(_protocol.anodaVoltage.count()*_protocol.focusingVoltage.count()));
    QStringList pointList;
    for (int i=0;i<_protocol.anodaVoltage.count()*_protocol.focusingVoltage.count() ;i++) {
        pointList << QString::number(i+1);
    }
    appendText(" "+pointList.join(" "));
    if(_reg.isBlank) {
        appendText(QString("  0.00      %1       %2").arg(QString::number(_reg.blankTime),QString::number(_reg.repeat)));
    }
    QVector<QStringList> countsRES;
    int sourceNo = 0;
    for(int i=1;i<_counts.count();i++){
        if(sourceNo != _counts.at(i).at(1).toInt()) {
           sourceNo = _counts.at(i).at(1).toInt();
           appendTable(countsRES);
           countsRES.clear();
           appendText(QString("  1.00      %1       %2").arg(QString::number(_reg.sourceTime),QString::number(_reg.repeat)));
        }
        QStringList record;
        record << QString::number(qRound((double)(QTime::fromString(_counts.at(i).at(0).split(" ").at(1),"hh:mm:ss").msecsSinceStartOfDay())/1000))
               << _counts.at(i).at(8)
               << _counts.at(i).at(9)
               << _counts.at(i).at(10)
               << _counts.at(i).at(11)
               << _counts.at(i).at(12)
               << QString::number(qRound(_counts.at(i).at(15).toDouble()*1000)) //1 kHz
               << QString::number(qRound(_counts.at(i).at(16).toDouble()*100)); //100 Hz
        countsRES << record;

    }
    appendTable(countsRES);
}
