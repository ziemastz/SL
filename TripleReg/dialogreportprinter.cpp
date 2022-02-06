#include "dialogreportprinter.h"
#include "ui_dialogreportprinter.h"

DialogReportPrinter::DialogReportPrinter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogReportPrinter)
{
    ui->setupUi(this);
}

DialogReportPrinter::~DialogReportPrinter()
{
    delete ui;
}
