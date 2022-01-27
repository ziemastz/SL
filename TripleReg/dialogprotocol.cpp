#include "dialogprotocol.h"
#include "ui_dialogprotocol.h"

DialogProtocol::DialogProtocol(const QString &protocolName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProtocol)
{
    ui->setupUi(this);
    protocol.id = 0;
    protocol.name = protocolName;
    readProtocolName();
    load(protocolName);
}

DialogProtocol::~DialogProtocol()
{
    delete ui;
}

void DialogProtocol::readProtocolName()
{
    DatabaseStarlingLab db;
    TripleRegProtocolModel protocol;
    DatabaseResult result = db.select(&protocol);
    for(int i=0; i<result.count(); i++){
        protocol.setRecord(result.at(i).record());
        ui->protocolName_comboBox->addItem(protocol.name);
    }
}

void DialogProtocol::load(const QString &protocolName)
{
    DatabaseStarlingLab db;
    DatabaseResult result = db.select(&protocol,"name='"+protocolName+"'");
}
