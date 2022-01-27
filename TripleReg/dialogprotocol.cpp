#include "dialogprotocol.h"
#include "ui_dialogprotocol.h"

DialogProtocol::DialogProtocol(const QString &protocolName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProtocol)
{
    ui->setupUi(this);
    protocol.id = 0;
    protocol.name = protocolName;

}

DialogProtocol::~DialogProtocol()
{
    delete ui;
}

void DialogProtocol::load()
{
    DatabaseStarlingLab db;
    db.select(&protocol,"name='"+protocol.name);
}
