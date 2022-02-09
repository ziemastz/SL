#include "reportgenerator.h"

ReportGenerator::ReportGenerator(const QString &fileName, QObject *parent) : QObject(parent)
{
    _file.setFileName(fileName);
    if(QFile::exists(fileName))
        QFile::remove(fileName);
    if(!_file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        qWarning() << tr("File write error! ")+_file.errorString();
    _textStream = new QTextStream(&_file);

}

ReportGenerator::~ReportGenerator()
{
    delete _textStream;
    _file.close();
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

void ReportGenerator::appendList(const Map &list)
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
       appendText(QString("%1 | %2").arg(keys.at(i),maxWidth).arg(values.at(i)));
    }
}

void ReportGenerator::appendTable(const QVector<QStringList> &table)
{
    QVector<int> headersMaxWidth;

    int rows = table.count();
    int columns = table.first().count();
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
}
