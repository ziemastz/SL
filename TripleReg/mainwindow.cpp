#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->version_label->setText(tr("Version ")+QApplication::applicationVersion());
    on_measReg_pushButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exit_pushButton_clicked()
{
    close();
}

void MainWindow::on_newMeasurement_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    DatabaseStarlingLab db;
    //clear & load
    // first clear
    ui->nuclide_lineEdit->clear();
    ui->solutionID_lineEdit->clear();
    ui->sourceID_lineEdit->clear();
    ui->sourceNo_spinBox->setValue(1);
    ui->isBlank_checkBox->setChecked(true);

    TripleRegSettingsModel settings;
    db.select(1,&settings);
    ui->blankTime_spinBox->setValue(settings.blankTime);
    ui->sourceTime_spinBox->setValue(settings.sourceTime);
    ui->repeat_spinBox->setValue(settings.repeat);

    TripleRegProtocolModel protocol;
    DatabaseResults result = db.select(&protocol);
    ui->protocol_comboBox->clear();
    for(int i=0; i<result.count(); i++){
        protocol.setRecord(result.at(i)->record());
        ui->protocol_comboBox->addItem(protocol.name);
    }

    ui->linked_lineEdit->clear();
    ui->category_comboBox->setCurrentIndex(0);
    ui->comment_plainTextEdit->clear();

}

void MainWindow::on_cancelNewMeasurement_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_settings_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->tabWidget->setCurrentIndex(0);
    //load parameter
    DatabaseStarlingLab db;
    TripleRegSettingsModel settings;
    if(!db.select(1,&settings)) {
        QMessageBox::warning(this,tr("Database"),tr("Reading error from database!\nPlease contact the administrator."));
        return;
    }
    ui->blankTimeDefault_spinBox->setValue(settings.blankTime);
    ui->sourceTimeDefault_spinBox->setValue(settings.sourceTime);
    ui->repeatDefault_spinBox->setValue(settings.repeat);

    ui->startDelay_spinBox->setValue(settings.startDelay);
    ui->maxVoltage_spinBox->setValue(settings.voltageMax);

    ui->port_comboBox->clear();
    ui->port_comboBox->addItems(Utils::availablePorts());
    ui->port_comboBox->setCurrentText(settings.port);
    ui->baudRate_comboBox->setCurrentText(settings.braudRate);
    ui->lBusAddress_spinBox->setValue(settings.lBusAddress);

    ui->deviceName_lineEdit->setText(settings.deviceName);
    ui->extClk_checkBox->setChecked(settings.isExtClk);

    //load user;
    if(!db.select(Settings::loggedUserId(),&user)) {
        QMessageBox::warning(this,tr("Database"),tr("Reading error from database!\nPlease contact the administrator."));
        return;
    }
    ui->username_lineEdit->setText(user.username);
    ui->degree_lineEdit->setText(user.degree);
    ui->firstName_lineEdit->setText(user.firstName);
    ui->secondName_lineEdit->setText(user.secondName);
    ui->lastName_lineEdit->setText(user.lastName);


    //system info
    TripleRegMeasuringSystemModel system;
    if(!db.select(1,&system)) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }
    ui->number_spinBox->setValue(system.number);
    ui->name_lineEdit->setText(system.name);
    ui->fullName_plainTextEdit->setPlainText(system.fullName);
    ui->measurementProcedureName_plainTextEdit->setPlainText(system.measuremntProcedureName);
    ui->location_lineEdit->setText(system.location);
    ui->notes_plainTextEdit->setPlainText(system.notes);

    //load lab infi
    LabInfoModel lab;
    if(!db.select(1,&lab)) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }
    ui->institute_lineEdit->setText(lab.institute);
    ui->department_lineEdit->setText(lab.deparment);
    ui->lab_lineEdit->setText(lab.lab);
    ui->addressLine1_lineEdit->setText(lab.addressLine1);
    ui->addressLine2_lineEdit->setText(lab.addressLine2);
    ui->zip_lineEdit->setText(lab.zip);
    ui->city_lineEdit->setText(lab.city);
    ui->country_lineEdit->setText(lab.country);
    ui->phone_lineEdit->setText(lab.phone);
    ui->email_lineEdit->setText(lab.email);
}

void MainWindow::on_saveGeneralSettings_pushButton_clicked()
{
    TripleRegSettingsModel settings;
    settings.id = 1;
    settings.blankTime = ui->blankTimeDefault_spinBox->value();
    settings.sourceTime = ui->sourceTimeDefault_spinBox->value();
    settings.repeat = ui->repeatDefault_spinBox->value();
    settings.startDelay = ui->startDelay_spinBox->value();
    settings.voltageMax = ui->maxVoltage_spinBox->value();
    settings.port = ui->port_comboBox->currentText();
    settings.braudRate = ui->baudRate_comboBox->currentText();
    settings.lBusAddress = ui->lBusAddress_spinBox->value();
    settings.deviceName = ui->deviceName_lineEdit->text();
    settings.isExtClk = ui->extClk_checkBox->isChecked();
    settings.userId = Settings::loggedUserId();

    DatabaseStarlingLab db;
    if(!db.update(&settings)) {
        QMessageBox::warning(this,tr("Database"),tr("Updating error from database!\nPlease contact the administrator."));
        return;
    }
    QMessageBox::information(this,tr("User data"),tr("Changes have been saved."));
}

void MainWindow::on_saveUserDatapushButton_clicked()
{
    user.degree = ui->degree_lineEdit->text();
    user.firstName = ui->firstName_lineEdit->text();
    user.secondName = ui->secondName_lineEdit->text();
    user.lastName = ui->lastName_lineEdit->text();
    user.userId = Settings::loggedUserId();

    DatabaseStarlingLab db;
    if(!db.update(&user)) {
        QMessageBox::warning(this,tr("Database"),tr("Updating error from database!\nPlease contact the administrator."));
        return;
    }
    QMessageBox::information(this,tr("User data"),tr("Changes have been saved."));
}

void MainWindow::on_passwordChange_pushButton_clicked()
{
    bool ok;
    QString currentPassword = QInputDialog::getText(this,tr("Password change"),
                                                    tr("Current password"), QLineEdit::Password,
                                                    QString(),&ok);
    if (ok && !currentPassword.isEmpty()) {
        if(currentPassword != user.password) {
            QMessageBox::warning(this,tr("Database"),tr("Wrong password!\nPlease try again."));
            return;
        }
        QString newPassword = QInputDialog::getText(this,tr("Password change"),
                                                        tr("New password"), QLineEdit::Password,
                                                        QString(),&ok);
        if (ok && !newPassword.isEmpty()) {
            if(newPassword.size() < 3) {
                QMessageBox::warning(this,tr("New password"),tr("Password too short!\nEnter at least 3 characters."));
                return;
            }

            QString confirmNewPassword = QInputDialog::getText(this,tr("Password change"),
                                                            tr("Confirm new password"), QLineEdit::Password,
                                                            QString(),&ok);
            if (ok && !confirmNewPassword.isEmpty()) {
                if(newPassword != confirmNewPassword) {
                    QMessageBox::warning(this,tr("Database"),tr("Wrong password!\nPlease try again."));
                    return;
                }
                user.password = newPassword;
                DatabaseStarlingLab db;
                if(!db.update(&user)) {
                    QMessageBox::warning(this,tr("Database"),tr("Updating error from database!\nPlease contact the administrator."));
                }else {
                    QMessageBox::information(this,tr("Password change"),tr("Your password has been successfully changed."));
                }
            }
        }
    }
}

void MainWindow::on_cancelSettings_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_connectionTestN1470_pushButton_clicked()
{
    PowerSupplyN1470::setPort(ui->port_comboBox->currentText());
    PowerSupplyN1470::setBaudRate(ui->baudRate_comboBox->currentText());
    PowerSupplyN1470::setLBusAddress(QString::number(ui->lBusAddress_spinBox->value()));

    PowerSupplyN1470 hv;
    if(hv.isConnect()) {
       QMessageBox::information(this,tr("Connection test"),tr("Connected properly to the CAEN N1470 power supply."));
    }else{
       QMessageBox::warning(this,tr("Connection test"),tr("Communication error with the CAEN N1470 power supply.\nPlease check the connectivity parameters."));
    }
}

void MainWindow::on_connectionTestMAC3Counter_pushButton_clicked()
{
    MAC3Counter mac3;
    mac3.setDeviceName(ui->deviceName_lineEdit->text().toStdString());
    if(mac3.connect()) {
        mac3.disconnect();
        QMessageBox::information(this,tr("Connection test"),tr("Connected properly to the MAC3 counter."));
    }else {
        QMessageBox::warning(this,tr("Connection test"),tr("Communication error with the MAC3 counter.\nPlease check the connectivity parameters."));
    }
}

void MainWindow::on_addProtocol_pushButton_clicked()
{
    bool ok;
    QString protocolName = QInputDialog::getText(this,tr("New protocol"),tr("New protocol name"),QLineEdit::Normal,QString(),&ok);
    if(ok && !protocolName.isEmpty()) {
        DatabaseStarlingLab db;
        if(!db.isAvailableProtocolName(protocolName)) {
            QMessageBox::warning(this,tr("New protocol"),tr("Nor available the new protocol name.\nPlease try again?"));
            return;
        }
        DialogProtocol protocolDialog(protocolName);
        if(protocolDialog.exec() == QDialog::Accepted) {
            ui->protocol_comboBox->addItem(protocolName);
            ui->protocol_comboBox->setCurrentText(protocolName);
        }

    }
}

void MainWindow::on_removeProtocol_pushButton_clicked()
{
    if(QMessageBox::question(this,tr("Remove protocol"),tr("Are you sure to delete the protocol permanently?")) == QMessageBox::Yes) {
        DatabaseStarlingLab db;
        TripleRegProtocolModel protocol;
        DatabaseResults results = db.select(&protocol,"name='"+ui->protocol_comboBox->currentText()+"'");
        if(results.count() != 1) {
            QMessageBox::warning(this,tr("Database"),tr("Reading error from database!\nPlease contact the administrator."));
            QMessageBox::warning(this,tr("Remove protocol"),tr("The protocol has not been deleted."));
            return;
        }
        protocol.setRecord(results.at(0)->record());

        if(!db.remove(&protocol,Settings::loggedUserId())) {
            QMessageBox::warning(this,tr("Database"),tr("Removing error from database!\nPlease contact the administrator."));
            QMessageBox::warning(this,tr("Remove protocol"),tr("The protocol has not been deleted."));
            return;
        }
        QMessageBox::information(this,tr("Remove protocol"),tr("The protocol was successfully deleted."));
        ui->protocol_comboBox->removeItem(ui->protocol_comboBox->findText(protocol.name));
    }
}

void MainWindow::on_editProtocol_pushButton_clicked()
{
    DialogProtocol protocolDialog(ui->protocol_comboBox->currentText());
    protocolDialog.exec();
}

void MainWindow::on_startNewMeasurement_pushButton_clicked()
{
    //check data
    if(ui->nuclide_lineEdit->text().isEmpty() ||
       ui->sourceID_lineEdit->text().isEmpty()) {
        QMessageBox::warning(this,tr("New measurement"),tr("Please provide nuclide and source ID."));
        return;
    }
    if(ui->sourceNo_spinBox->value() == 0 &&
       !ui->isBlank_checkBox->isChecked()) {
        QMessageBox::warning(this,tr("New measurement"),tr("There are no measurement objects.\nEnter the measurement objects (e.g. blank, source)."));
        return;
    }
    TripleRegMeasurementRegisterModel reg;
    TripleRegMeasurementProtocolModel protocol;
    TripleRegMeasuringSystemModel system;
    DatabaseStarlingLab db;
    int id = db.countMeasurementAt(QDateTime::currentDateTime().date().year());
    if(id == -1){
        if(!db.addCountMeasurementAt(QDateTime::currentDateTime().date().year())) {
            QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
            return;
        }
        id=0;
    }
    id++;
    DatabaseResults result = db.select(&system,"isDefault=1");
    if(result.count() !=1 ) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }
    system.setRecord(result.at(0)->record());
    reg.id = 0;
    reg.measurementId = Utils::generatorMeasurementId(system.number,id);
    reg.measurementDate = Utils::currentDate();
    reg.nuclide = ui->nuclide_lineEdit->text();
    reg.solutionId = ui->solutionID_lineEdit->text();
    reg.sourceId = ui->sourceID_lineEdit->text();
    reg.sourceNo = ui->sourceNo_spinBox->value();
    reg.isBlank = ui->isBlank_checkBox->isChecked();
    reg.blankTime = ui->blankTime_spinBox->value();
    reg.sourceTime = ui->sourceTime_spinBox->value();
    reg.repeat = ui->repeat_spinBox->value();
    //copy protocol
    DatabaseResults result2 = db.select(new TripleRegProtocolModel,"name='"+ui->protocol_comboBox->currentText()+"'");
    if(result2.count() != 1) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }
    protocol.setRecord(result2.at(0)->record());
    protocol.id = 0;
    protocol.measurementId = reg.measurementId;
    protocol.userId = Settings::loggedUserId();
    if(!db.insert(&protocol)) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }//end copy
    reg.protocolId = protocol.id;
    reg.linked = ui->linked_lineEdit->text();
    reg.category = ui->category_comboBox->currentText();
    reg.comments = ui->comment_plainTextEdit->toPlainText();
    reg.authorId = Settings::loggedUserId();
    reg.acceptedId = 0;
    reg.acceptedDateTime = "";
    reg.userId = Settings::loggedUserId();
    if(!db.insert(&reg)) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        //remove protocol
        db.remove(&protocol);
        return;
    }
    if(!db.increaseCountMeasurementAt(QDateTime::currentDateTime().date().year())) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        db.remove(&protocol);
        db.remove(&reg);
        return;
    }
    DialogMeasurementProcess dialogMeasurementProcess(reg,this);
    this->hide();
    dialogMeasurementProcess.exec();
    this->show();
    this->setFocus();
    on_measReg_pushButton_clicked();

}


void MainWindow::on_saveSystemInfo_pushButton_clicked()
{
    DatabaseStarlingLab db;
    TripleRegMeasuringSystemModel system;
    if(!db.select(1,&system)) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }
    system.number = ui->number_spinBox->value();
    system.name = ui->name_lineEdit->text();
    system.fullName = ui->fullName_plainTextEdit->toPlainText();
    system.measuremntProcedureName = ui->measurementProcedureName_plainTextEdit->toPlainText();
    system.location = ui->location_lineEdit->text();
    system.notes = ui->notes_plainTextEdit->toPlainText();
    system.userId = Settings::loggedUserId();
    if(!db.update(&system)) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }
}


void MainWindow::on_measReg_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    Utils::clearTableWidget(ui->measurementRegister_tableWidget);
    this->setFocus();
    DatabaseStarlingLab db;
    TripleRegMeasurementRegisterModel reg;
    QStringList filterNuclide;
    QStringList filterSolution;
    int countRecord = db.countRecord(&reg);
    int partSize = 10;
    for(int i=0; i<countRecord; i+=partSize) {
        QApplication::processEvents();
        DatabaseResults results = db.select(new TripleRegMeasurementRegisterModel,QString(),DatabaseStarlingLab::Order::DESC,partSize,i);
        UserModel autor;
        UserModel acceptedUser;
        QVector<QStringList> table;
        filterNuclide << QString("");
        filterSolution << QString("");
        for(int i=0; i < results.count(); i++) {
            reg.setRecord(results.at(i)->record());
            if(!db.select(reg.userId,&autor)){
                QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
                return;
            }
            if(reg.acceptedId > 0) {
                if(!db.select(reg.acceptedId,&acceptedUser)){
                    QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
                    return;
                }
            }else {
                acceptedUser.firstName = "";
            }
            if(!filterNuclide.contains(reg.nuclide))
                filterNuclide << reg.nuclide;
            if(!filterSolution.contains(reg.solutionId))
                filterSolution << reg.solutionId;
            QStringList record;
            record << reg.measurementId
                   << reg.measurementDate
                   << reg.nuclide
                   << reg.solutionId
                   << reg.sourceId
                   << reg.linked
                   << reg.category
                   << autor.captionShort()
                   << acceptedUser.captionShort()+" "+reg.acceptedDateTime;
            table << record;
        }
        ui->measurementRegister_tableWidget->setSortingEnabled(false);
        foreach(QStringList record, table)
            Utils::addItemTableWidget(ui->measurementRegister_tableWidget,record);
        ui->measurementRegister_tableWidget->setSortingEnabled(true);
    }

    ui->filterNuclide_comboBox->blockSignals(true);
    ui->filterNuclide_comboBox->clear();
    filterNuclide.sort();
    ui->filterNuclide_comboBox->addItems(filterNuclide);
    ui->filterNuclide_comboBox->blockSignals(false);

    ui->filterSolution_comboBox->blockSignals(true);
    ui->filterSolution_comboBox->clear();
    filterSolution.sort();
    ui->filterSolution_comboBox->addItems(filterSolution);
    ui->filterSolution_comboBox->blockSignals(false);
}

void MainWindow::on_filterNuclide_comboBox_currentIndexChanged(const QString &arg1)
{
    QStringList filterSolution;
    filterSolution << QString("");
    for(int i=0; i< ui->measurementRegister_tableWidget->rowCount(); i++) {
        QApplication::processEvents();
        if(!arg1.isEmpty()){
            bool match = ui->measurementRegister_tableWidget->item(i,2)->text() == arg1;
            if(match) {
                if(!filterSolution.contains(ui->measurementRegister_tableWidget->item(i,3)->text()))
                    filterSolution << ui->measurementRegister_tableWidget->item(i,3)->text();
            }
            ui->measurementRegister_tableWidget->setRowHidden(i,!match);
        }else {
            ui->measurementRegister_tableWidget->setRowHidden(i,false);
            if(!filterSolution.contains(ui->measurementRegister_tableWidget->item(i,3)->text()))
                filterSolution << ui->measurementRegister_tableWidget->item(i,3)->text();
        }
    }
    ui->filterSolution_comboBox->blockSignals(true);
    ui->filterSolution_comboBox->clear();
    filterSolution.sort();
    ui->filterSolution_comboBox->addItems(filterSolution);
    ui->filterSolution_comboBox->blockSignals(false);
}

void MainWindow::on_filterSolution_comboBox_currentIndexChanged(const QString &arg1)
{
    for(int i=0; i< ui->measurementRegister_tableWidget->rowCount(); i++) {
        if(!arg1.isEmpty()){
            bool match = ui->measurementRegister_tableWidget->item(i,3)->text() == arg1;
            ui->measurementRegister_tableWidget->setRowHidden(i,!match);
        }else {
            if(!ui->filterNuclide_comboBox->currentText().isEmpty()){
                bool match = ui->measurementRegister_tableWidget->item(i,2)->text() == ui->filterNuclide_comboBox->currentText();
                ui->measurementRegister_tableWidget->setRowHidden(i,!match);
            }else
                ui->measurementRegister_tableWidget->setRowHidden(i,false);
        }
    }
}

void MainWindow::on_saveLab_pushButton_clicked()
{
    DatabaseStarlingLab db;
    LabInfoModel lab;
    lab.id = 1;
    lab.institute = ui->institute_lineEdit->text();
    lab.deparment = ui->department_lineEdit->text();
    lab.lab = ui->lab_lineEdit->text();
    lab.addressLine1 = ui->addressLine1_lineEdit->text();
    lab.addressLine2 = ui->addressLine2_lineEdit->text();
    lab.zip = ui->zip_lineEdit->text();
    lab.city = ui->city_lineEdit->text();
    lab.country = ui->country_lineEdit->text();
    lab.phone = ui->phone_lineEdit->text();
    lab.email = ui->email_lineEdit->text();
    lab.userId = Settings::loggedUserId();
    if(!db.update(&lab)) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }
}

void MainWindow::on_measurementRegister_tableWidget_cellDoubleClicked(int row, int column)
{
    QString selectedMeasId = ui->measurementRegister_tableWidget->item(row,0)->text();
    DatabaseStarlingLab db;
    TripleRegMeasurementRegisterModel measReg;
    DatabaseResults result = db.select(&measReg,"measurementId='"+selectedMeasId+"'");
    if(result.count() != 1) {
        QMessageBox::warning(this,tr("Database"),tr("Database communication error. Please contact the administrator."));
        return;
    }
    measReg.setRecord(result.at(0)->record());
    DialogMeasurementReport *dialogReport = new DialogMeasurementReport(measReg,this);
    connect(dialogReport,SIGNAL(rejected()),dialogReport,SLOT(deleteLater()));
    connect(dialogReport,SIGNAL(rejected()),this,SLOT(on_measReg_pushButton_clicked()));
    dialogReport->show();
    dialogReport->load();
}

void MainWindow::on_logbook_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    Utils::clearTableWidget(ui->logbook_tableWidget);
    DatabaseStarlingLab db;
    QStringList rootFilter;
    QStringList elementFilter;
    rootFilter << QString("");
    elementFilter << QString("");
    int countRecord = db.countRecord(new TripleRegLogbookModel);
    int partSize = 10;
    for(int i=0; i<countRecord; i+=partSize) {
        QApplication::processEvents();
        DatabaseResults results = db.select(new TripleRegLogbookModel,QString(""),DatabaseStarlingLab::DESC,partSize,i);
        TripleRegLogbookModel logbook;
        UserModel author;
        QVector<QStringList> table;
        for(int j=0; j < results.count(); j++) {
            logbook.setRecord(results.at(j)->record());
            db.select(logbook.userId,&author);
            if(!rootFilter.contains(logbook.root))
                rootFilter << logbook.root;
            if(!elementFilter.contains(logbook.element))
                elementFilter << logbook.element;
            QStringList record;
            record << logbook.lastModification
                   << logbook.type
                   << logbook.description
                   << logbook.root
                   << logbook.element
                   << author.captionShort();
            table << record;
        }
        ui->logbook_tableWidget->setSortingEnabled(false);
        foreach(QStringList record, table)
            Utils::addItemTableWidget(ui->logbook_tableWidget,record);
        ui->logbook_tableWidget->setSortingEnabled(true);
    }
    ui->rootFilter_comboBox->blockSignals(true);
    ui->rootFilter_comboBox->clear();
    rootFilter.sort();
    ui->rootFilter_comboBox->addItems(rootFilter);
    ui->rootFilter_comboBox->blockSignals(false);

    ui->elementFilter_comboBox->blockSignals(true);
    ui->elementFilter_comboBox->clear();
    elementFilter.sort();
    ui->elementFilter_comboBox->addItems(elementFilter);
    ui->elementFilter_comboBox->blockSignals(false);

}


void MainWindow::on_addEventLogbook_pushButton_clicked()
{
    DialogAddEven addEven;
    if(addEven.exec() == QDialog::Accepted) {
        on_logbook_pushButton_clicked();
        this->setFocus();
    }
}


void MainWindow::on_rootFilter_comboBox_currentIndexChanged(const QString &arg1)
{
    QStringList elementFilter;
    elementFilter << QString("");
    for(int i=0; i<ui->logbook_tableWidget->rowCount();i++) {
        QApplication::processEvents();
        if(!arg1.isEmpty()) {
            bool match = ui->logbook_tableWidget->item(i,3)->text() == arg1;
            if(match) {
                if(!elementFilter.contains(ui->logbook_tableWidget->item(i,4)->text()))
                    elementFilter << ui->logbook_tableWidget->item(i,4)->text();
            }
            ui->logbook_tableWidget->setRowHidden(i,!match);
        }else {
            ui->logbook_tableWidget->setRowHidden(i,false);
            if(!elementFilter.contains(ui->logbook_tableWidget->item(i,4)->text()))
                elementFilter << ui->logbook_tableWidget->item(i,4)->text();
        }
    }
    ui->elementFilter_comboBox->blockSignals(true);
    ui->elementFilter_comboBox->clear();
    elementFilter.sort();
    ui->elementFilter_comboBox->addItems(elementFilter);
    ui->elementFilter_comboBox->blockSignals(false);
}


void MainWindow::on_elementFilter_comboBox_currentIndexChanged(const QString &arg1)
{
    for(int i=0; i< ui->logbook_tableWidget->rowCount(); i++) {
        if(!arg1.isEmpty()){
            bool match = ui->logbook_tableWidget->item(i,4)->text() == arg1;
            ui->logbook_tableWidget->setRowHidden(i,!match);
        }else {
            if(!ui->rootFilter_comboBox->currentText().isEmpty()){
                bool match = ui->logbook_tableWidget->item(i,3)->text() == ui->rootFilter_comboBox->currentText();
                ui->logbook_tableWidget->setRowHidden(i,!match);
            }else
                ui->logbook_tableWidget->setRowHidden(i,false);
        }
    }
}

