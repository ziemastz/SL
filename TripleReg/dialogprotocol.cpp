#include "dialogprotocol.h"
#include "ui_dialogprotocol.h"

DialogProtocol::DialogProtocol(const QString &protocolName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProtocol)
{
    ui->setupUi(this);
    protocol.id = 0;
    protocol.name = protocolName;
    readProtocolName();
    load(protocolName);
}

DialogProtocol::~DialogProtocol()
{
    delete ui;
}

void DialogProtocol::readProtocolName()
{
    DatabaseStarlingLab db;
    TripleRegProtocolModel pro;
    DatabaseResults result = db.select(&pro);
    ui->protocolName_comboBox->clear();
    for(int i=0; i<result.count(); i++){
        pro.setRecord(result.at(i)->record());
        ui->protocolName_comboBox->addItem(pro.name);
    }
}

void DialogProtocol::setParameter()
{
    ui->protocolName_lineEdit->setText(protocol.name);

    ui->anode_spinBox->setValue(protocol.anodaVoltage.first());
    ui->focusing_spinBox->setValue(protocol.focusingVoltage.first());
    voltageTable.setAnodeTab(protocol.anodaVoltage);
    voltageTable.setFocusingTab(protocol.focusingVoltage);
    if(protocol.anodaVoltage.count() != 1 || protocol.focusingVoltage.count() != 1) {
        ui->setUpTableVoltage_checkBox->setChecked(true);
    }else {
        ui->setUpTableVoltage_checkBox->setChecked(false);
    }
    ui->shiftA_spinBox->setValue(protocol.voltageShiftA);
    ui->shiftB_spinBox->setValue(protocol.voltageShiftB);
    ui->shiftC_spinBox->setValue(protocol.voltageShiftC);

    ui->resolvingTime_spinBox->setValue(protocol.resolvingTime);
    ui->deadTime_spinBox->setValue(protocol.deadTime);

    ui->thrA_doubleSpinBox->setValue(protocol.thrA);
    ui->thrB_doubleSpinBox->setValue(protocol.thrB);
    ui->thrC_doubleSpinBox->setValue(protocol.thrC);

    ui->notes_plainTextEdit->setPlainText(protocol.notes);
}

void DialogProtocol::load(const QString &protocolName)
{
    DatabaseStarlingLab db;
    DatabaseResults result = db.select(&protocol,"name='"+protocolName+"'");
    if(result.count() == 0) {
        //new & copy default parameter
        if(!db.select(1, &protocol)) {
            return;
        }
        protocol.id = 0;
        protocol.name = protocolName;
    }else {
        protocol.setRecord(result.at(0)->record());
    }
    setParameter();
}

void DialogProtocol::on_setUpTableVoltage_checkBox_stateChanged(int arg1)
{
    switch (arg1) {
    case Qt::Unchecked:
        ui->table_pushButton->setEnabled(false);
        break;
    case Qt::Checked:
        ui->table_pushButton->setEnabled(true);
        break;
    }
}


void DialogProtocol::on_copy_pushButton_clicked()
{
    DatabaseStarlingLab db;
    DatabaseResults result = db.select(&protocol,"name='"+ui->protocolName_comboBox->currentText()+"'");
    if(result.count() == 1) {
        int id = protocol.id;
        QString name = protocol.name;
        protocol.setRecord(result.at(0)->record());
        protocol.id = id;
        protocol.name = name;
        setParameter();
    }
}


void DialogProtocol::on_cancel_pushButton_clicked()
{
    close();
}

void DialogProtocol::on_save_pushButton_clicked()
{
    //read parameter
    if(ui->setUpTableVoltage_checkBox->isChecked()){
        protocol.anodaVoltage = voltageTable.getAnodeTab();
        protocol.focusingVoltage = voltageTable.getFocusingTab();
    }else {
        protocol.anodaVoltage.clear();
        protocol.focusingVoltage.clear();
        protocol.anodaVoltage << ui->anode_spinBox->value();
        protocol.focusingVoltage << ui->focusing_spinBox->value();
    }

    protocol.voltageShiftA = ui->shiftA_spinBox->value();
    protocol.voltageShiftA = ui->shiftA_spinBox->value();
    protocol.voltageShiftA = ui->shiftA_spinBox->value();

    protocol.resolvingTime = ui->resolvingTime_spinBox->value();
    protocol.deadTime = ui->deadTime_spinBox->value();

    protocol.thrA = ui->thrA_doubleSpinBox->value();
    protocol.thrB = ui->thrB_doubleSpinBox->value();
    protocol.thrC = ui->thrC_doubleSpinBox->value();

    protocol.notes = ui->notes_plainTextEdit->toPlainText();

    protocol.userId = Settings::loggedUserId();

    DatabaseStarlingLab db;
    if(protocol.id == 0) {
        if(!db.insert(&protocol)) {
            QMessageBox::warning(this,tr("Database"),tr("Inserting error from database!\nPlease contact the administrator."));
            return;
        }
        QMessageBox::information(this,tr("New protocol"),tr("Success, new protocol added!"));
        accept();
    }else {
        if(!db.update(&protocol)) {
            QMessageBox::warning(this,tr("Database"),tr("Updating error from database!\nPlease contact the administrator."));
            return;
        }
        accept();
    }
}


void DialogProtocol::on_table_pushButton_clicked()
{
    voltageTable.setAnodeTab(protocol.anodaVoltage);
    voltageTable.setFocusingTab(protocol.focusingVoltage);
    voltageTable.exec();
}

