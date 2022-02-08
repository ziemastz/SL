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
    reject();
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

    if(_reg.acceptedId > 0) {
        if(!db.select(_reg.acceptedId,&user)) {
            QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
            return;
        }
    }else {
        user.firstName = "";
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
    double hours = (double)(points * _reg.sourceTime * _reg.repeat * _reg.sourceNo) / 3600;
    if(hours<=1.0) {
        if(hours*60<=1.0){
            ui->sourcesTotalTime_doubleSpinBox->setSuffix(" s");
            ui->sourcesTotalTime_doubleSpinBox->setValue(hours*60*60);
        }else{
            ui->sourcesTotalTime_doubleSpinBox->setSuffix(" min");
            ui->sourcesTotalTime_doubleSpinBox->setValue(hours*60);
        }
    }else{
        ui->sourcesTotalTime_doubleSpinBox->setValue(hours);
    }

    //counts
    //1'Counts and 2'CPS
    TripleRegMeasurementRAWModel raw;
    Counter counter(new MAC3Counter);
    DatabaseResults results = db.select(&raw,"measurementId="+QString::number(_reg.id));
    for (int i=0; i<results.count(); i++) {
        raw.setRecord(results.at(i)->record());
        Counts counts;
        counts.A = raw.A;
        counts.B = raw.B;
        counts.C = raw.C;
        counts.S = raw.S;
        counts.AB = raw.AB;
        counts.BC = raw.BC;
        counts.AC = raw.AC;
        counts.T = raw.T;
        counts.D = raw.D;
        counts.LT = raw.LT;
        counts.CLK_IN = raw.CLK_IN;
        counter.setCounts(counts);
        QStringList record;
        record << raw.startMeasurementDateTime
               << QString::number(raw.sourceNo)
               << raw.pointTag
               << QString::number(raw.repeat)
               << QString::number(counter.cpsA(),'f',1)
               << QString::number(counter.cpsB(),'f',1)
               << QString::number(counter.cpsC(),'f',1)
               << QString::number(counter.cpsS(),'f',1)
               << QString::number(counter.cpsAB(),'f',1)
               << QString::number(counter.cpsBC(),'f',1)
               << QString::number(counter.cpsAC(),'f',1)
               << QString::number(counter.cpsT(),'f',1)
               << QString::number(counter.cpsD(),'f',1)
               << QString::number(counter.cpsT()/counter.cpsD(),'f',4)
               << QString::number((counter.deadTime()*100)/counter.realTime(),'f',1)
               << QString::number(counter.rel1())
               << QString::number(counter.rel2())
               << QString::number(raw.voltageCh0)
               << QString::number(raw.voltageCh1)
               << QString::number(raw.voltageCh2)
               << QString::number(raw.voltageCh3);
        Utils::addItemTableWidget(ui->csp_tableWidget,record);
        record.clear();
        record << raw.startMeasurementDateTime
               << QString::number(raw.sourceNo)
               << raw.pointTag
               << QString::number(raw.repeat)
               << QString::number(raw.A)
               << QString::number(raw.B)
               << QString::number(raw.C)
               << QString::number(raw.S)
               << QString::number(raw.AB)
               << QString::number(raw.BC)
               << QString::number(raw.AC)
               << QString::number(raw.T)
               << QString::number(raw.D)
               << QString::number(counter.cpsT()/counter.cpsD(),'f',4)
               << QString::number((counter.deadTime()*100)/counter.realTime(),'f',1)
               << QString::number(counter.rel1())
               << QString::number(counter.rel2())
               << QString::number(raw.voltageCh0)
               << QString::number(raw.voltageCh1)
               << QString::number(raw.voltageCh2)
               << QString::number(raw.voltageCh3);
        Utils::addItemTableWidget(ui->counts_tableWidget,record);
    }
}

void DialogMeasurementReport::on_cps_radioButton_toggled(bool checked)
{
    if(checked)
        ui->stackedWidget->setCurrentIndex(0);
    else
        ui->stackedWidget->setCurrentIndex(1);
}

void DialogMeasurementReport::on_modify_pushButton_toggled(bool checked)
{
    ui->save_pushButton->setEnabled(checked);

    ui->nuclide_lineEdit->setReadOnly(!checked);
    ui->nuclide_lineEdit->setFrame(checked);

    ui->solutionId_lineEdit->setReadOnly(!checked);
    ui->solutionId_lineEdit->setFrame(checked);

    ui->sourceId_lineEdit->setReadOnly(!checked);
    ui->sourceId_lineEdit->setFrame(checked);

    ui->linked_lineEdit->setReadOnly(!checked);
    ui->linked_lineEdit->setFrame(checked);

    ui->category_lineEdit->setReadOnly(!checked);
    ui->category_lineEdit->setFrame(checked);

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

