#ifndef DIALOGMEASUREMENTPROCESS_H
#define DIALOGMEASUREMENTPROCESS_H

#include <QDialog>

namespace Ui {
class DialogMeasurementProcess;
}

class DialogMeasurementProcess : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMeasurementProcess(QWidget *parent = nullptr);
    ~DialogMeasurementProcess();

private:
    Ui::DialogMeasurementProcess *ui;
};

#endif // DIALOGMEASUREMENTPROCESS_H
