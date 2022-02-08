#include "workermeasurementprocess.h"

WorkerMeasurementProcess::WorkerMeasurementProcess(const TripleRegMeasurementRegisterModel &measurementRegister, QObject *parent) : QObject(parent)
{
    n1470 = nullptr;
    counter = nullptr;
    timer = nullptr;
    _measurement = measurementRegister;
    currSource = 0;
    currPoint = 0;
    currAnode = 0;
    currFocusing = 0;
    currRepeat = 0;
    currTime = 0;
    startDelay = 0;
    isAbort = false;
}

WorkerMeasurementProcess::~WorkerMeasurementProcess()
{
    if(timer != nullptr) {
        timer->stop();
        delete timer;
    }
    if(n1470 != nullptr) {
        delete n1470;
    }
    if(counter != nullptr) {
        delete counter;
    }

}

void WorkerMeasurementProcess::init()
{
    DatabaseStarlingLab db;
    if(!db.select(_measurement.protocolId,&_protocol)) {
        QMessageBox::warning(nullptr,tr("Database"),tr("Reading error from database!\nPlease contact the administrator."));
        emit finished();
        return;
    }

    isBlank = _measurement.isBlank; //the value of isBlank will change to false after the blank measurement is completed;
    maxSource = _measurement.sourceNo;
    maxAnode = _protocol.anodaVoltage.count();
    maxFocusing = _protocol.focusingVoltage.count();
    maxPoint = maxAnode*maxFocusing;
    maxRepeat = _measurement.repeat;
    if(isBlank) {
        maxTime = _measurement.blankTime;
        stateProcess = WorkerMeasurementProcess::Blank;
    }else {
        maxTime = _measurement.sourceTime;
        stateProcess = WorkerMeasurementProcess::NextSource;
    }

    emit setMeasurementObject(_measurement.nuclide,_measurement.solutionId,_measurement.sourceId);
    emit setParameter(maxSource,maxPoint,maxRepeat,maxTime);

    emit setEndTime(generatorEndTime());
    emit setTimeLeft(timeLeft());

    timer = new QTimer(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(process()));
    connect(this, SIGNAL(finished()), timer, SLOT(stop()));
    timer->start(500);
}

void WorkerMeasurementProcess::acceptedMessageBox()
{
    stateProcess = WorkerMeasurementProcess::SetupHV;
}

void WorkerMeasurementProcess::rejectedMessageBox()
{
    stateProcess = WorkerMeasurementProcess::Finished;
}

void WorkerMeasurementProcess::abortedPowerSupplyProcessBox()
{
    isAbort = true;
}

void WorkerMeasurementProcess::process()
{
    //timer->stop();

    if(!refreshN1470()) {
        stateProcess = WorkerMeasurementProcess::Finished;
    }

    if(!refreshMAC3()) {
        stateProcess = WorkerMeasurementProcess::Finished;
    }

    switch(stateProcess) {
    case WorkerMeasurementProcess::Blank: {
        if(!turnOffPowerSupply()) {
            stateProcess = WorkerMeasurementProcess::Finished;
            break;
        }
        emit showMessageBox(tr("Blank measurement"),tr("Please put the blank vial for measurement."));
        stateProcess = PlacingVial;
        break;
    }
    case WorkerMeasurementProcess::NextSource: {
        isBlank = false;
        maxTime = _measurement.sourceTime;
        currSource++;
        if(currSource<=maxSource) {
            if(!turnOffPowerSupply()) {
                stateProcess = WorkerMeasurementProcess::Finished;
                break;
            }
            emit showMessageBox(tr("Source measurement"),tr("Please put the source vial for measurement.\nSource No: ")+QString::number(currSource));
            stateProcess = WorkerMeasurementProcess::PlacingVial;
            emit setCurrentSource(currSource);
        }else {
            stateProcess = WorkerMeasurementProcess::Finished;
        }
        break;
    }
    case WorkerMeasurementProcess::PlacingVial: {
        //waiting
        break;
    }
    case WorkerMeasurementProcess::SetupHV: {// nextPoint
        if(!nextPoint()) {
            currPoint = 0;
            currAnode = 0;
            currFocusing = 0;
            stateProcess = WorkerMeasurementProcess::NextSource;
        }else {
            emit setCurrentPoint(currPoint);
            if(!turnOnPowerSupply()) {
                stateProcess = WorkerMeasurementProcess::Finished;
                break;
            }
            if(!stabilizationPowerSupply()) {
                stateProcess = WorkerMeasurementProcess::Finished;
                break;
            }

            stateProcess = WorkerMeasurementProcess::Start;
        }
        break;
    }
    case WorkerMeasurementProcess::Start: {
        if(currRepeat == 0) {
            currRepeat++;
        }
        counter->reset();
        counter->start();
        counter->readData();
        emit addRecord(generatorRecord(),generatorFullRecord());
        emit setCurrentRepeat(currRepeat);
        stateProcess = WorkerMeasurementProcess::Measurement;
        break;
    }
    case WorkerMeasurementProcess::Measurement: {
        currTime = (int)counter->realTime();
        emit setCurrentTime(currTime);
        if(currTime >= maxTime) {
            counter->stop();
            counter->readData();
            stateProcess = WorkerMeasurementProcess::Stop;
        }
        emit updateLastRecord(generatorRecord(),generatorFullRecord());
        break;
    }
    case WorkerMeasurementProcess::Stop: {
        DatabaseStarlingLab db;
        TripleRegMeasurementRAWModel raw;
        setRAW(&raw);
        raw.userId = Settings::loggedUserId();
        if(!db.insert(&raw)) {
            stateProcess = WorkerMeasurementProcess::Finished;
            break;
        }
        currRepeat++;
        if(currRepeat>maxRepeat) {
            stateProcess = WorkerMeasurementProcess::SetupHV;
            currRepeat = 0;
        }else {
            stateProcess = WorkerMeasurementProcess::Start;
        }
        break;
    }
    case WorkerMeasurementProcess::Finished: {
        if(n1470 != nullptr)
            turnOffPowerSupply();
        emit finished();
        break;
    }
    }
    emit setEndTime(generatorEndTime());
    emit setTimeLeft(timeLeft());
   // timer->start(500);
}

bool WorkerMeasurementProcess::refreshN1470()
{
    //update N1470
    if(n1470 == nullptr) {
        DatabaseStarlingLab db;
        TripleRegSettingsModel settings;
        if(!db.select(1,&settings)) {
            //QMessageBox::warning(new QWidget(),tr("Database"),tr("Reading error from database!\nPlease contact the administrator."));
            return false;
        }
        PowerSupplyN1470::setPort(settings.port);
        PowerSupplyN1470::setBaudRate(settings.braudRate);
        PowerSupplyN1470::setLBusAddress(QString::number(settings.lBusAddress));
        startDelay = settings.startDelay;
        n1470 = new PowerSupplyN1470();
        if(!n1470->isConnect()) {
            delete n1470;
            n1470 = nullptr;
            //QMessageBox::warning(new QWidget(),tr("Power Supply"),tr("Communication error with the CAEN N1470 power supply.\nPlease check the connectivity parameters."));
            return false;
        }
    }else {
        n1470->refresh();
    }
    return true;
}

bool WorkerMeasurementProcess::refreshMAC3()
{
    //update counter - MAC3
    if(counter == nullptr) {
        DatabaseStarlingLab db;
        TripleRegSettingsModel settings;
        if(!db.select(1,&settings)) {
            QMessageBox::warning(nullptr,tr("Database"),tr("Reading error from database!\nPlease contact the administrator."));
            return false;
        }
        MAC3Counter *mac3 = new MAC3Counter();
        mac3->setDeviceName(settings.deviceName.toStdString());
        counter = new Counter(mac3);
        if(!counter->isConnect()) {
            delete counter;
            counter = nullptr;
            //QMessageBox::warning(nullptr,tr("Counter"),tr("Communication error with the MAC3 counter.\nPlease check the connectivity parameters."));
            return false;
        }
    }else {
        counter->readData();
    }
    return true;
}

bool WorkerMeasurementProcess::turnOffPowerSupply()
{
    int maxValue = qRound(n1470->monVoltCh0() + n1470->monVoltCh1() + n1470->monVoltCh2() + n1470->monVoltCh3());
    emit showPowerSupplyProcessBox();
    emit setSetupHVPowerSupplyProcess(maxValue);
    //turn off n1470
    n1470->setTurnCh0(false);
    n1470->setTurnCh1(false);
    n1470->setTurnCh2(false);
    n1470->setTurnCh3(false);
    QString error = n1470->lastError();
    if(!error.isEmpty()){
        QMessageBox::warning(nullptr,tr("Power Supply"),tr("Error: ")+error);
        emit hidePowerSupplyProcessBox();
        return false;
    }
    while(1) {
        QApplication::processEvents();
        if(isAbort) {
            emit hidePowerSupplyProcessBox();
            return false;
        }

        int currValue = qRound(n1470->monVoltCh0() + n1470->monVoltCh1() + n1470->monVoltCh2() + n1470->monVoltCh3());
        emit setCurrentStatusPowerSupplyProcess(maxValue - currValue);
        if(currValue <= 2) {
            break;
        }
        n1470->refresh();
    }
    emit hidePowerSupplyProcessBox();
    return true;
}

bool WorkerMeasurementProcess::turnOnPowerSupply()
{
    int ch0 = _protocol.anodaVoltage.at(currAnode-1) + _protocol.voltageShiftA;
    int ch1 = _protocol.anodaVoltage.at(currAnode-1) + _protocol.voltageShiftB;
    int ch2 = _protocol.anodaVoltage.at(currAnode-1) + _protocol.voltageShiftC;
    int ch3 = _protocol.focusingVoltage.at(currFocusing-1);

    int maxValue = ch0 + ch1 + ch2 + ch3;
    emit showPowerSupplyProcessBox();
    emit setSetupHVPowerSupplyProcess(maxValue);
    n1470->setTurnCh0(true);
    n1470->setTurnCh1(true);
    n1470->setTurnCh2(true);
    n1470->setTurnCh3(true);
    n1470->setVoltCh0(ch0);
    n1470->setVoltCh1(ch1);
    n1470->setVoltCh2(ch2);
    n1470->setVoltCh3(ch3);
    QString error = n1470->lastError();
    if(!error.isEmpty()){
        QMessageBox::warning(nullptr,tr("Power Supply"),tr("Error: ")+error);
        emit hidePowerSupplyProcessBox();
        return false;
    }
    while(1) {
        QApplication::processEvents();
        if(isAbort) {
            emit hidePowerSupplyProcessBox();
            return false;
        }

        int currValue = qRound(n1470->monVoltCh0() + n1470->monVoltCh1() + n1470->monVoltCh2() + n1470->monVoltCh3());
        if(maxValue - currValue <= 2) {
            break;
        }
        emit setCurrentStatusPowerSupplyProcess(currValue);
        n1470->refresh();
    }
    emit hidePowerSupplyProcessBox();
    return true;
}

bool WorkerMeasurementProcess::stabilizationPowerSupply()
{
    emit showPowerSupplyProcessBox();
    emit setStabilizationPowerSupplyProcess(startDelay);
    QElapsedTimer time;
    time.start();
    while(1) {
        QApplication::processEvents();
        if(isAbort) {
            emit hidePowerSupplyProcessBox();
            return false;
        }

        int curr = qRound((float)time.elapsed()/1000);
        emit setCurrentStatusPowerSupplyProcess(curr);
        if(curr >= startDelay)
            break;
    }
    emit hidePowerSupplyProcessBox();
    return true;
}

bool WorkerMeasurementProcess::nextPoint()
{
    currPoint++;
    if(currPoint == 1) {
        currAnode = 1;
    }
    if(currPoint <= maxPoint) {
        currFocusing++;
        if(currFocusing>maxFocusing) {
            currFocusing = 1;
            currAnode++;
        }
        if(currAnode>maxAnode)
            return false;

        return true;
    }else {
        return false;
    }
}

QString WorkerMeasurementProcess::generatorEndTime() const
{
    QDateTime ret(QDateTime::currentDateTime());
    int sec = 0;
    if(isBlank) {
        sec = (maxSource-currSource)*_measurement.blankTime*maxPoint*maxRepeat;
        sec += (maxPoint-currPoint)*_measurement.blankTime*maxRepeat;
        sec += (maxRepeat-currRepeat)*_measurement.blankTime;
        sec += (_measurement.blankTime-currTime);
        sec += maxSource*_measurement.sourceTime*maxPoint*maxRepeat;
    }else {
        sec = (maxSource-currSource)*_measurement.sourceTime*maxPoint*maxRepeat;
        sec += (maxPoint-currPoint)*_measurement.sourceTime*maxRepeat;
        sec += (maxRepeat-currRepeat)*_measurement.sourceTime;
        sec += (_measurement.sourceTime-currTime);
    }
    return ret.addSecs(sec).toString("hh:mm:ss yyyy-MM-dd");
}

int WorkerMeasurementProcess::timeLeft() const
{
    int sec = (maxPoint-currPoint)*maxTime*maxRepeat;
    sec += (maxRepeat-currRepeat)*maxTime;
    sec += (maxTime-currTime);
    return sec;
}

QString WorkerMeasurementProcess::generatorPointTag() const
{
    QString tag;
    if(maxAnode == 1 && maxFocusing == 1) {
        tag = "1";
    }else {
        if(maxAnode > 1)
            tag.append("(A) "+QString::number(_protocol.anodaVoltage.at(currAnode-1))+" V");
        if(maxFocusing > 1){
            if(!tag.isEmpty())
                tag.append(" | ");
            tag.append("(F) "+QString::number(_protocol.focusingVoltage.at(currFocusing-1))+" V");
        }
    }
    return tag;
}

QStringList WorkerMeasurementProcess::generatorRecord() const
{
    QStringList ret;
    ret << QString::number(currSource)
        << QString::number(currRepeat)
        << QString::number(counter->cpsAB(),'f',1)
        << QString::number(counter->cpsBC(),'f',1)
        << QString::number(counter->cpsAC(),'f',1)
        << QString::number(counter->cpsT(),'f',1)
        << QString::number(counter->cpsD(),'f',1)
        << QString::number(counter->cpsT()/counter->cpsD(),'f',4)
        << QString::number(counter->deadTime()*100/counter->realTime(),'f',1)
        << generatorPointTag();
    return ret;
}

QStringList WorkerMeasurementProcess::generatorFullRecord() const
{
    QStringList ret;
    ret << counter->startDateTime().toString("yyyy-MM-dd hh:mm:ss")
        << QString::number(currSource)
        << generatorPointTag()
        << QString::number(currRepeat)
        << QString::number(counter->cpsA(),'f',1)
        << QString::number(counter->cpsB(),'f',1)
        << QString::number(counter->cpsC(),'f',1)
        << QString::number(counter->cpsS(),'f',1)
        << QString::number(counter->cpsAB(),'f',1)
        << QString::number(counter->cpsBC(),'f',1)
        << QString::number(counter->cpsAC(),'f',1)
        << QString::number(counter->cpsT(),'f',1)
        << QString::number(counter->cpsD(),'f',1)
        << QString::number(counter->cpsT()/counter->cpsD(),'f',4)
        << QString::number(counter->deadTime()*100/counter->realTime(),'f',1)
        << QString::number(counter->rel1())
        << QString::number(counter->rel2())
        << QString::number(n1470->monVoltCh0())
        << n1470->statusCh0()
        << QString::number(n1470->monVoltCh1())
        << n1470->statusCh1()
        << QString::number(n1470->monVoltCh2())
        << n1470->statusCh2()
        << QString::number(n1470->monVoltCh3())
        << n1470->statusCh3();

    return ret;
}

void WorkerMeasurementProcess::setRAW(TripleRegMeasurementRAWModel *model)
{
    model->measurementId = _measurement.id;
    model->startMeasurementDateTime = counter->startDateTime().toString("yyyy-MM-dd hh:mm:ss");
    model->sourceNo = currSource;
    model->pointTag = generatorPointTag();
    model->repeat = currRepeat;
    model->A = counter->getCounts().A;
    model->B = counter->getCounts().B;
    model->C = counter->getCounts().C;
    model->S = counter->getCounts().S;
    model->AB = counter->getCounts().AB;
    model->BC = counter->getCounts().BC;
    model->AC = counter->getCounts().AC;
    model->T = counter->getCounts().T;
    model->D = counter->getCounts().D;
    model->LT = counter->getCounts().LT;
    model->CLK_IN = counter->getCounts().CLK_IN;
    model->voltageCh0 = n1470->monVoltCh0();
    model->voltageCh1 = n1470->monVoltCh1();
    model->voltageCh2 = n1470->monVoltCh2();
    model->voltageCh3 = n1470->monVoltCh3();
}
