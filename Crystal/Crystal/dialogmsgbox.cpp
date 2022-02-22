#include "dialogmsgbox.h"
#include "ui_dialogmsgbox.h"

DialogMsgBox::DialogMsgBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMsgBox)
{
    ui->setupUi(this);
}

DialogMsgBox::~DialogMsgBox()
{
    delete ui;
}

void DialogMsgBox::setTitle(const QString &title)
{
    setWindowTitle(title);
}

void DialogMsgBox::setText(const QString &text)
{
    ui->text_label->setText(text);
}

void DialogMsgBox::setPortId(const int &portId)
{
    switch (portId) {
    case NaICounter::PORT_A:
        ui->portId_label->setText("A");
        break;
    case NaICounter::PORT_B:
        ui->portId_label->setText("B");
        break;
    case NaICounter::PORT_C:
        ui->portId_label->setText("C");
        break;
    case NaICounter::PORT_D:
        ui->portId_label->setText("D");
        break;
    default:
        ui->portId_label->clear();
        break;
    }
}

void DialogMsgBox::on_ok_pushButton_clicked()
{
    accept();
}


void DialogMsgBox::on_cancel_pushButton_clicked()
{
    reject();
}

