#include "addmeasurementdialog.h"
#include "ui_addmeasurementdialog.h"

AddMeasurementDialog::AddMeasurementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMeasurementDialog)
{
    ui->setupUi(this);
}

AddMeasurementDialog::~AddMeasurementDialog()
{
    delete ui;
}

void AddMeasurementDialog::on_cancel_pushButton_clicked()
{
    close();
}


void AddMeasurementDialog::on_start_pushButton_clicked()
{
    StarlingLab::DBRecordTDK db;
    StarlingLab::TDKLogModel log;
    log.creationDateTime = QDate::currentDate().toString("yyyy-MM-dd");
    log.nuclide = ui->nuclide_lineEdit->text();
    log.solution = ui->solution_lineEdit->text();
    log.noSources = ui->noSources_spinBox->value();
    log.sourceId = ui->idSources_lineEdit->text();
    log.sourcePreparationDate = ui->sourcePreparation_dateEdit->date().toString("yyyy-MM-dd");
    log.description = ui->comments_textEdit->placeholderText();
    log.linked = ui->linked_lineEdit->text();
    log.category = ui->category_comboBox->currentIndex();

    // protocolId
}


void AddMeasurementDialog::on_addProtocol_pushButton_clicked()
{

}


void AddMeasurementDialog::on_editProtocol_pushButton_clicked()
{

}


void AddMeasurementDialog::on_searchProtocol_lineEdit_textChanged(const QString &arg1)
{

}

