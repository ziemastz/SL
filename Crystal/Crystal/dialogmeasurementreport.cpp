#include "dialogmeasurementreport.h"
#include "ui_dialogmeasurementreport.h"

DialogMeasurementReport::DialogMeasurementReport(const QString &measId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMeasurementReport)
{
    ui->setupUi(this);
    _measId = measId;
}

DialogMeasurementReport::~DialogMeasurementReport()
{
    delete ui;
}

void DialogMeasurementReport::load()
{
    DBCrystal db;

    DatabaseResults result = db.select(&reg,"measurementId='"+_measId+"'");
    if(result.count() != 1) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        close();
    }
    reg.setRecord(result.at(0)->record());

    ui->measId_lineEdit->setText(reg.measurementId);
    ui->nuclide_lineEdit->setText(reg.nuclide);
    ui->measDate_lineEdit->setText(reg.measurementDate);

    ui->sourceId_lineEdit->setText(reg.sourceId);
    ui->geometry_lineEdit->setText(reg.geometry);

    ui->blank_spinBox->setValue(reg.blankTime);
    ui->source_spinBox->setValue(reg.sourceTime);
    ui->repeat_spinBox->setValue(reg.repeat);

    CrystalMeasurementProtocolModel protocol;
    if(!db.select(reg.protocolId,&protocol)) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        close();
    }
    ui->anode_lineEdit->setText(Utils::toString(protocol.anodeVoltage));
    ui->threshold_lineEdit->setText(Utils::toString(protocol.thresholdVoltage));
    ui->deadTime_doubleSpinBox->setValue(protocol.extendableDeadTime);
    ui->notesProtocol_plainTextEdit->setPlainText(protocol.notes);

    ui->linked_lineEdit->setText(reg.linked);
    ui->category_comboBox->setCurrentText(reg.category);
    ui->comments_plainTextEdit->setPlainText(reg.comments);

    UserModel user;
    if(!db.select(reg.authorId,&user)) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        close();
    }
    ui->author_lineEdit->setText(user.caption());
    ui->lastModification_label->setText(tr("Last modification ")+reg.lastModification);

    if(reg.acceptedId > 0) {
        if(!db.select(reg.acceptedId,&user)) {
            QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
            close();
        }
        ui->accepted_lineEdit->setText(user.captionShort()+" "+reg.acceptedDateTime);
    }else {
        ui->accepted_lineEdit->clear();
    }

    //raw
    CrystalMeasurementRAWModel raw;
    DatabaseResults results = db.select(&raw,"measurementId="+QString::number(reg.id));
    for(int i=0; i<results.count(); i++) {
        raw.setRecord(results.at(i)->record());
        QStringList rawCounts;
        rawCounts << raw.startMeasurementDateTime
                  << QString::number(raw.sourceNo)
                  << raw.pointTag
                  << QString::number(raw.repeat)
                  << QString::number(raw.counts)
                  << QString::number((double)raw.counts/((double)raw.liveTime/1000))
                  << QString::number((double)raw.liveTime/1000,'f',2)
                  << QString::number((double)raw.realTime/1000,'f',2)
                  << QString::number(100-((double)raw.liveTime*100/(double)raw.realTime),'f',1);
        Utils::addItemTableWidget(ui->raw_tableWidget,rawCounts);
    }
}
