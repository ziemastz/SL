#include "dialogmeasurementreport.h"
#include "ui_dialogmeasurementreport.h"

DialogMeasurementReport::DialogMeasurementReport(const TripleRegMeasurementRegisterModel &measReg, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMeasurementReport)
{
    _reg = measReg;
    ui->setupUi(this);
    load();
}

DialogMeasurementReport::~DialogMeasurementReport()
{
    delete ui;
}

void DialogMeasurementReport::on_cancel_pushButton_clicked()
{
    close();
}

void DialogMeasurementReport::load()
{
    ui->measurementId_lineEdit->setText(_reg.measurementId);
    ui->nuclide_lineEdit->setText(_reg.nuclide);
    ui->measurementDate_lineEdit->setText(_reg.measurementDate);
    ui->solutionId_lineEdit->setText(_reg.solutionId);
    ui->sourceId_lineEdit->setText(_reg.sourceId);
    ui->blankTime_spinBox->setValue(_reg.blankTime);
    ui->blankRepeat_spinBox->setValue(_reg.repeat);
    ui->sourceRepeat_spinBox->setValue(_reg.repeat);
    ui->sourceTime_spinBox->setValue(_reg.sourceTime);
    ui->sourceNo_spinBox->setValue(_reg.sourceNo);
    ui->linked_lineEdit->setText(_reg.linked);
    ui->category_lineEdit->setText(_reg.category);
    ui->comments_plainTextEdit->setPlainText(_reg.comments);
    DatabaseStarlingLab db;
    UserModel user;
    if(!db.select(_reg.authorId,&user)) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }
    ui->author_lineEdit->setText(user.captionShort());
    if(!db.select(_reg.userId,&user)) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }
    ui->lastModification_label->setText(_reg.lastModification+" "+user.captionShort());

    if(!db.select(_reg.acceptedId,&user)) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }
    ui->accepted_lineEdit->setText(user.captionShort());
    ui->acceptedDateTime_label->setText(_reg.acceptedDateTime);

    //protocol
    TripleRegMeasurementProtocolModel protocol;
    if(!db.select(_reg.protocolId,&protocol)) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }
    ui->protocolName_lineEdit->setText(protocol.name);
    ui->voltageAnode_lineEdit->setText(Utils::toString(protocol.anodaVoltage));
    ui->voltageFocusing_lineEdit->setText(Utils::toString(protocol.focusingVoltage));
    ui->shiftA_spinBox->setValue(protocol.voltageShiftA);
    ui->shiftB_spinBox->setValue(protocol.voltageShiftB);
    ui->shiftC_spinBox->setValue(protocol.voltageShiftC);
    ui->thrA_doubleSpinBox->setValue(protocol.thrA);
    ui->thrB_doubleSpinBox->setValue(protocol.thrB);
    ui->thrC_doubleSpinBox->setValue(protocol.thrC);
    ui->resolvingTime_spinBox->setValue(protocol.resolvingTime);
    ui->deadTime_spinBox->setValue(protocol.deadTime);
    ui->notesProtocol_plainTextEdit->setPlainText(protocol.notes);
    int points = protocol.anodaVoltage.count() * protocol.focusingVoltage.count();
    ui->blankPoint_spinBox->setValue(points);
    ui->sourcePoint_spinBox->setValue(points);
    ui->blankSumTime_spinBox->setValue(points * _reg.blankTime * _reg.repeat);
    ui->sourceSumTime_spinBox->setValue(points * _reg.sourceTime * _reg.repeat);
    ui->sourcesTotalTime_doubleSpinBox->setValue((points * _reg.sourceTime * _reg.repeat * _reg.sourceNo) / 3600);

}


void DialogMeasurementReport::on_modify_pushButton_clicked()
{
    ui->modify_pushButton->setChecked(true);
    ui->save_pushButton->setEnabled(true);

    ui->nuclide_lineEdit->setReadOnly(false);
    ui->nuclide_lineEdit->setFrame(true);

    ui->sourceId_lineEdit->setReadOnly(false);
    ui->solutionId_lineEdit->setFrame(true);

    ui->sourceId_lineEdit->setReadOnly(false);
    ui->sourceId_lineEdit->setFrame(true);

    ui->linked_lineEdit->setReadOnly(false);
    ui->linked_lineEdit->setFrame(true);

    ui->category_lineEdit->setReadOnly(false);
    ui->category_lineEdit->setFrame(true);

    ui->comments_plainTextEdit->setReadOnly(false);
    ui->comments_plainTextEdit->setFrameShape(QFrame::StyledPanel);

    ui->notesProtocol_plainTextEdit->setReadOnly(false);
    ui->notesProtocol_plainTextEdit->setFrameShape(QFrame::StyledPanel);
}

