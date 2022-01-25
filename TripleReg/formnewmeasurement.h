#ifndef FORMNEWMEASUREMENT_H
#define FORMNEWMEASUREMENT_H

#include <QWidget>

namespace Ui {
class FormNewMeasurement;
}

class FormNewMeasurement : public QWidget
{
    Q_OBJECT

public:
    explicit FormNewMeasurement(QWidget *parent = nullptr);
    ~FormNewMeasurement();

private:
    Ui::FormNewMeasurement *ui;
};

#endif // FORMNEWMEASUREMENT_H
