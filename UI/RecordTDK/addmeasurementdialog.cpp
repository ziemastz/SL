#include "addmeasurementdialog.h"
#include "ui_addmeasurementdialog.h"

AddMeasurementDialog::AddMeasurementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMeasurementDialog)
{
    ui->setupUi(this);
    StarlingLab::DBRecordTDK db;
    ui->protocols_listWidget->addItems(db.getProtocolNames());
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
    log.creationDateTime = QDate::currentDate().toString("yyyy-MM-dd");
    log.nuclide = ui->nuclide_lineEdit->text();
    log.solution = ui->solution_lineEdit->text();
    log.noSources = ui->noSources_spinBox->value();
    log.sourceId = ui->idSources_lineEdit->text();
    log.sourcePreparationDate = ui->sourcePreparation_dateEdit->date().toString("yyyy-MM-dd");
    log.description = ui->comments_textEdit->placeholderText();
    log.linked = ui->linked_lineEdit->text();
    log.status = StarlingLab::DBRecordTDK::Insert;
    log.category = ui->category_comboBox->currentIndex();
    log.measurementProtocolId = db.getProtocol(ui->protocols_listWidget->currentItem()->text()).id;
    if(log.measurementProtocolId == 0) {
        QMessageBox::warning(this,tr("Błąd"),tr("Brak protokołu pomiarowe!\nZaznacz protokoł lub dodaj nowy."));
        return;
    }
    log.time.blank = ui->blankTime_spinBox->value();
    log.time.source = ui->sourceTime_spinBox->value();
    log.time.repeating = ui->repeating_spinBox->value();
    accept();
}


void AddMeasurementDialog::on_addProtocol_pushButton_clicked()
{
    QString protocolName = QInputDialog::getText(this,tr("Nowy protokół"),tr("Podaj nową nazwe protokołu"));
    if(protocolName.isEmpty())
        return;

    StarlingLab::DBRecordTDK db;
    if(db.getProtocol(protocolName).id != 0){
        QMessageBox::warning(this,tr("Błąd"),tr("Nazwa protokołu istnieje.\nPodaj inną nazwe protokołu."));
        return;
    }

    ProtocolDialog protocolDialog;
    protocolDialog.setName(protocolName);
    if(protocolDialog.exec() == QDialog::Accepted) {
        StarlingLab::ProtocolModel model;
        model.id = 0;
        model = protocolDialog.getData();
        if(db.getProtocol(model.name).id != 0){
            QMessageBox::warning(this,tr("Błąd"),tr("Nazwa protokołu istnieje.\nPodaj inną nazwe protokołu."));
            return;
        }
        if(db.insert(&model)) {
            QListWidgetItem *item = new QListWidgetItem(model.name);
            ui->protocols_listWidget->addItem(item);
            ui->protocols_listWidget->setCurrentItem(item);
        }
    }
}


void AddMeasurementDialog::on_editProtocol_pushButton_clicked()
{
    QString name = ui->protocols_listWidget->currentItem()->text();
    StarlingLab::DBRecordTDK db;
    StarlingLab::ProtocolModel model;
    model = db.getProtocol(name);
    if(model.id != 0) {
        ProtocolDialog protocolDialog;
        protocolDialog.setData(model);
        if(protocolDialog.exec() == QDialog::Accepted) {
            model = protocolDialog.getData();
            db.update(&model);
        }
    }
}

void AddMeasurementDialog::on_searchProtocol_lineEdit_textChanged(const QString &arg1)
{
    QList<QListWidgetItem*> out = ui->protocols_listWidget->findItems(arg1,Qt::MatchContains);
    if(out.count() > 0) {
        ui->protocols_listWidget->setCurrentItem(out.first());
    }
}

const StarlingLab::TDKLogModel &AddMeasurementDialog::getLog() const
{
    return log;
}

void AddMeasurementDialog::setLog(const StarlingLab::TDKLogModel &newLog)
{
    log = newLog;
}

