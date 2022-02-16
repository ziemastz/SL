#ifndef DIALOGNEWMEASUREMENT_H
#define DIALOGNEWMEASUREMENT_H

#include <QDialog>
#include <QMessageBox>

#include "dialogpointstable.h"
#include "dbcrystal.h"
#include "settings.h"

namespace Ui {
class DialogNewMeasurement;
}

class DialogNewMeasurement : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewMeasurement(const int &id, QWidget *parent = nullptr);
    ~DialogNewMeasurement();
signals:
    void startNewMeasurement(int registerId);
private slots:
    void on_pointsTable_checkBox_toggled(bool checked);

    void on_cancel_pushButton_clicked();

    void on_pointsTable_pushButton_clicked();

    void on_start_pushButton_clicked();

private:
    Ui::DialogNewMeasurement *ui;
    int _id;
    QString _systemLabel;
    DialogPointsTable pointsTableDialog;

    void loadDefaultParameters();

};

#endif // DIALOGNEWMEASUREMENT_H
