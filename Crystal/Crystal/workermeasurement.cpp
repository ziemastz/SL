#include "workermeasurement.h"

WorkerMeasurement::WorkerMeasurement(const NaICounter::PORT &port, Counter *counter, QObject *parent) : QObject(parent)
{
    _port = port;
    _counter = counter;
}

void WorkerMeasurement::startNewMeasurement(int registerId)
{
    DBCrystal db;
    if(!db.select(registerId,&reg)) {
        emit msgBox(tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."),_port);
        return;
    }
    if(!db.select(reg.protocolId,&protocol)) {
        emit msgBox(tr("Reading error"),tr("Database communication error!\nPlease contact the administrator."),_port);
        return;
    }
    mutex.lock();
    _counter->setDeadTime(_port,protocol.extendableDeadTime);
    mutex.unlock();

    emit setNuclide(reg.nuclide);
    emit setGeometry(reg.geometry);
    emit setSourceId(reg.sourceId);
    emit setProcess(tr("Measurement initiation ... "));
    emit setCurrentRepeat(0);
    emit setRepeat(reg.repeat);
    emit setActivity(0.0);
    emit setCounts(0.0);
    emit setDeadTime(0.0);
    if(reg.blankTime == 0) {
       isBlank = false;
       maxTime = reg.sourceTime;
       stateProcess = WorkerMeasurement::NextSource;
       emit setProcess(tr("Measurement source"));
    }else {
       isBlank = true;
       maxTime = reg.blankTime;
       stateProcess = WorkerMeasurement::Blank;
       emit setProcess(tr("Measurement blank"));
    }
    currTime = 0;
    maxSource = reg.sourceNo;
    maxPoint = protocol.anodeVoltage.count() * protocol.thresholdVoltage.count();
    maxRepeat = reg.repeat;
    currSource = 0;
    currPoint = 0;
    currRepeat = 0;


    timer = new QTimer(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(process()));
    connect(this, SIGNAL(finished()), timer, SLOT(stop()));
    timer->start(500);
}

void WorkerMeasurement::acceptedMsgBox(const int &portId)
{
    if(portId != _port)
        return;
    if(stateProcess == WorkerMeasurement::SettingPoint) {
        stateProcess = WorkerMeasurement::Start;
    }else if(stateProcess == WorkerMeasurement::Finished)
    {

    }
    else {
        stateProcess = WorkerMeasurement::NextPoint;
    }
}

void WorkerMeasurement::rejectedMsgBox(const int &portId)
{
    if(portId != _port)
        return;
    stateProcess = WorkerMeasurement::Finished;
}

void WorkerMeasurement::abortMeasurement(const int &portId)
{
    if(portId != _port)
        return;
    stateProcess = WorkerMeasurement::Finished;

}

void WorkerMeasurement::process()
{
    mutex.lock();
    _counter->readData();
    mutex.unlock();

    switch (stateProcess) {
    case WorkerMeasurement::Blank: {
        emit msgBox(tr("Blank measurement"),tr("Please put the blank for measurement."),_port);
        stateProcess = WorkerMeasurement::PlacingVial;

        break;
    }
    case WorkerMeasurement::NextSource: {
        currSource++;
        isBlank = false;
        if(currSource > maxSource) {
            stateProcess = WorkerMeasurement::Finished;
        }else {
            emit setProcess(tr("Waiting for the source no ")+QString::number(currSource));
            emit msgBox(tr("Source measurement"),tr("Please put the source No ")+QString::number(currSource),_port);
            stateProcess = WorkerMeasurement::PlacingVial;
        }
        break;
    }
    case WorkerMeasurement::PlacingVial: {
        //waitting
        emit setProcess(tr("Waiting for the source ... "));
        break;
    }
    case WorkerMeasurement::SettingPoint: {
        //waitting
        emit setProcess(tr("Waiting for parameter setting ... "));
        break;
    }
    case WorkerMeasurement::NextPoint: {
        currPoint++;
        if(currPoint>maxPoint) {
            currPoint = 0;
            stateProcess = WorkerMeasurement::NextSource;
        }else {
            if(maxPoint!=1) {
                //char process
                if(protocol.anodeVoltage.count() > 1) {
                    emit msgBox(tr("Measurement point"),tr("Point No ")+QString::number(currPoint)+"\n"+
                                tr("Set the anode voltage to ")+QString::number(protocol.anodeVoltage.at(currPoint-1))+" V",_port);
                }else if(protocol.thresholdVoltage.count() > 1) {
                    emit msgBox(tr("Measurement point"),tr("Point No ")+QString::number(currPoint)+"\n"+
                                tr("Set the threshold voltage to ")+QString::number(protocol.thresholdVoltage.at(currPoint-1))+" V",_port);
                }
            }else {
                emit msgBox(tr("Measurement parameter"),tr("Set parameters to\n")+
                            tr("Anode to ")+QString::number(protocol.anodeVoltage.at(0))+" V\n"+
                            tr("Threshold to ")+QString::number(protocol.thresholdVoltage.at(0))+" V",_port);

            }

            stateProcess = WorkerMeasurement::SettingPoint;
        }
        break;
    }
    case WorkerMeasurement::Start: {
        currRepeat++;
        if(currRepeat > maxRepeat) {
            currRepeat = 0;
            stateProcess = WorkerMeasurement::NextPoint;
        }else {
            currTime = 0;
            mutex.lock();
            _counter->setReset(_port);
            _counter->setStart(_port);
            _counter->readData();
            mutex.unlock();
            emit setActivity(0.0);
            emit setCounts(0.0);
            emit setDeadTime(0.0);
            emit setProcess(tr("Measurement started.."));
            stateProcess = WorkerMeasurement::Measurement;
        }
        emit setCurrentRepeat(currRepeat);
        break;
    }
    case WorkerMeasurement::Measurement: {
        currTime = qRound(_counter->realTime(_port));
        if(currTime>maxTime) {
            mutex.lock();
            _counter->setStop(_port);
            _counter->readData();
            mutex.unlock();
            stateProcess = WorkerMeasurement::Stop;
        }
        //update activity counts deadTIme
        emit setCounts(_counter->cps(_port));
        emit setDeadTime(_counter->deadTime(_port));
        break;
    }
    case WorkerMeasurement::Stop: {
        DBCrystal db;
        CrystalMeasurementRAWModel raw;
        raw.id = 0;
        raw.measurementId = reg.id;
        raw.startMeasurementDateTime = _counter->startDateTime(_port).toString("yyyy-MM-dd hh:mm:ss");
        raw.sourceNo = currSource;
        raw.pointTag = generatorPointTag();
        raw.repeat = currRepeat;
        raw.counts = _counter->counts(_port);
        raw.liveTime = _counter->countsLiveTime(_port);
        raw.realTime = _counter->countsRealTime(_port);
        raw.userId = Settings::loggedUserId();
        if(!db.insert(&raw)) {
            emit msgBox(tr("Writting error"),tr("Database communication error!\nPlease contact the administrator."),_port);
            stateProcess = WorkerMeasurement::Finished;
        }else {
            stateProcess = WorkerMeasurement::Start;
        }
        break;
    }
    case WorkerMeasurement::Finished: {
        emit setProcess(tr("Finished."));
        emit msgBox(tr("Finished"),tr("The measurement is complete."),_port);
        emit finished();
        break;
    }
    }
    emit setEndTime(generatorEndTime());
}

QString WorkerMeasurement::generatorEndTime()
{
    int sec = 0;
    if(isBlank) {
        sec = (maxSource-currSource)*reg.blankTime*maxPoint*maxRepeat;
        sec += (maxPoint-currPoint)*reg.blankTime*maxRepeat;
        sec += (maxRepeat-currRepeat)*reg.blankTime;
        sec += (reg.blankTime-currTime);
        sec += maxSource*reg.sourceTime*maxPoint*maxRepeat;
    }else {
        sec = (maxSource-currSource)*reg.sourceTime*maxPoint*maxRepeat;
        sec += (maxPoint-currPoint)*reg.sourceTime*maxRepeat;
        sec += (maxRepeat-currRepeat)*reg.sourceTime;
        sec += (reg.sourceTime-currTime);
    }
    return Utils::generatorTimeDHMSString(sec);
}

QString WorkerMeasurement::generatorPointTag()
{
    QString ret;
    if(maxPoint == 1) {
        ret = "1";
    }else {
        if(protocol.anodeVoltage.count() > 1) {
            ret = QString("A:%1V").arg(protocol.anodeVoltage.at(currPoint-1));
        }else if(protocol.thresholdVoltage.count() > 1) {
            ret = QString("THR:%1V").arg(protocol.thresholdVoltage.at(currPoint-1));
        }else {
            ret = "1";
        }
    }
    return ret;
}

