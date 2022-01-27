#ifndef DIALOGPROTOCOL_H
#define DIALOGPROTOCOL_H

#include <QDialog>
#include "dialogvoltagetable.h"
#include "databasestarlinglab.h"

namespace Ui {
class DialogProtocol;
}

class DialogProtocol : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProtocol(const QString &protocolName, QWidget *parent = nullptr);
    ~DialogProtocol();

private:
    Ui::DialogProtocol *ui;
    DialogVoltageTable voltageTable;
    TripleRegProtocolModel protocol;

    void load();
};

#endif // DIALOGPROTOCOL_H