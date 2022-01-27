#include "dialogprotocol.h"
#include "ui_dialogprotocol.h"

DialogProtocol::DialogProtocol(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProtocol)
{
    ui->setupUi(this);
}

DialogProtocol::~DialogProtocol()
{
    delete ui;
}
