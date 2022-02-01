#ifndef DIALOGPOWERSUPPLYPROCESS_H
#define DIALOGPOWERSUPPLYPROCESS_H

#include <QDialog>

namespace Ui {
class DialogPowerSupplyProcess;
}

class DialogPowerSupplyProcess : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPowerSupplyProcess(QWidget *parent = nullptr);
    ~DialogPowerSupplyProcess();
public slots:
    void setSetupHV(const int &maxVoltage);
    void setStabilization(const int &startDelay);
    void setCurrentState(const int &val);

private slots:
    void on_abort_pushButton_clicked();

private:
    Ui::DialogPowerSupplyProcess *ui;
};

#endif // DIALOGPOWERSUPPLYPROCESS_H
