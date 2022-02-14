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

    void setSystemLabel(const QString &newSystemLabel);
signals:
    void startNewMeasurement(CrystalMeasurementRegister reg);
public slots:
    void setNuclide(const QString &nuclide);
    void setSourceId(const QString &sourceId);
    void setGeometry(const QString &geometry);
    void setProcess(const QString &process);
    void setCurrentRepeat(const int &value);
    void setRepeat(const int &value);
    void setEndTime(const QString &endTime);
    void setActivity(const double &value);
    void setCounts(const double &value);
    void setDeadTime(const double &value);

private:
    Ui::FormNewMeasurement *ui;
    QString _systemLabel;
};

#endif // FORMNEWMEASUREMENT_H
