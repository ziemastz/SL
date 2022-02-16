#ifndef FORMNEWMEASUREMENT_H
#define FORMNEWMEASUREMENT_H

#include <QWidget>
#include "dialognewmeasurement.h"
#include "dbcrystal.h"
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
    void startNewMeasurement(int registerId);
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

private slots:
    void on_start_pushButton_clicked();

private:
    Ui::FormNewMeasurement *ui;
    QString _systemLabel;
    int _id;
};

#endif // FORMNEWMEASUREMENT_H
