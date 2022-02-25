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

void DialogMeasurementReport::on_modify_pushButton_toggled(bool checked)
{
    ui->save_pushButton->setEnabled(checked);

    ui->nuclide_lineEdit->setReadOnly(!checked);
    ui->nuclide_lineEdit->setFrame(checked);

    ui->sourceId_lineEdit->setReadOnly(!checked);
    ui->sourceId_lineEdit->setFrame(checked);

    ui->geometry_lineEdit->setReadOnly(!checked);
    ui->geometry_lineEdit->setFrame(checked);

    ui->linked_lineEdit->setReadOnly(!checked);
    ui->linked_lineEdit->setFrame(checked);

    ui->category_comboBox->setEnabled(checked);
    ui->category_comboBox->setFrame(checked);

    ui->comments_plainTextEdit->setReadOnly(!checked);
    if(checked)
        ui->comments_plainTextEdit->setFrameShape(QFrame::StyledPanel);
    else
        ui->comments_plainTextEdit->setFrameShape(QFrame::NoFrame);

    ui->notesProtocol_plainTextEdit->setReadOnly(!checked);
    if(checked)
        ui->notesProtocol_plainTextEdit->setFrameShape(QFrame::StyledPanel);
    else
        ui->notesProtocol_plainTextEdit->setFrameShape(QFrame::NoFrame);
}


void DialogMeasurementReport::on_save_pushButton_clicked()
{
    DBCrystal db;
    CrystalMeasurementRegisterModel modified;
    modified.setRecord(reg.record());
    modified.nuclide = ui->nuclide_lineEdit->text();
    modified.geometry = ui->geometry_lineEdit->text();
    modified.sourceId = ui->sourceId_lineEdit->text();
    modified.linked = ui->linked_lineEdit->text();
    modified.category = ui->category_comboBox->currentText();
    modified.comments = ui->comments_plainTextEdit->toPlainText();
    if(!(modified == reg)) {
           modified.userId = Settings::loggedUserId();

           modified.acceptedDateTime.clear();
           modified.acceptedId = 0;
           if(!db.update(&modified)){
               QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
               return;
           }
           if(reg.acceptedId > 0)
               QMessageBox::information(this,tr("Accepted"),tr("Please, re-accept of the measurement is required."));
           db.select(reg.id,&reg);
       }

    if(!db.select(reg.protocolId,&protocol)) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }

    if(protocol.notes != ui->notesProtocol_plainTextEdit->toPlainText()) {
        protocol.notes = ui->notesProtocol_plainTextEdit->toPlainText();
        protocol.userId = Settings::loggedUserId();

        if(!db.update(&protocol)){
            QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
            return;
        }
        db.select(protocol.id,&protocol);
        if(reg.acceptedId > 0) {
            QMessageBox::information(this,tr("Accepted"),tr("Please, re-accept of the measurement is required."));
            reg.acceptedDateTime.clear();
            reg.acceptedId = 0;
            db.update(&reg);
            db.select(reg.id,&reg);
        }
    }
    ui->modify_pushButton->setChecked(false);
    load();
}


void DialogMeasurementReport::on_accept_pushButton_clicked()
{
    if(ui->save_pushButton->isEnabled()) {
       QMessageBox::warning(this,tr("Modification"),tr("Please save your changes!"));
       return;
    }
    if(reg.acceptedId > 0) {
       QMessageBox::information(this,tr("Accepted"),tr("The measurement has already been accepted."));
       return;
    }
    if(QMessageBox::question(this,tr("Accept"),tr("Do you really want to accept this measurement?"))==QMessageBox::Yes) {
        reg.acceptedDateTime = Utils::currentDateTime();
        reg.acceptedId = Settings::loggedUserId();
        reg.userId = Settings::loggedUserId();
        DBCrystal db;
        if(!db.update(&reg)){
            QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
            return;
        }
        db.select(reg.id,&reg);
        load();
    }
}


void DialogMeasurementReport::on_remove_pushButton_clicked()
{
    if(QMessageBox::question(this,tr("Remove"),tr("Do you really want to remove this measurement?"))==QMessageBox::Yes) {
        DBCrystal db;
        if(!db.remove(&reg,Settings::loggedUserId())) {
            QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
            return;
        }else {
            db.SLDatabase::remove(&protocol);
            db.SLDatabase::remove(new CrystalMeasurementRAWModel,"measurementId="+QString::number(reg.id));
            reject();
        }
    }
}


void DialogMeasurementReport::on_cancel_pushButton_clicked()
{
    reject();
}

