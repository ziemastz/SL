#ifndef DIALOGVOLTAGETABLE_H
#define DIALOGVOLTAGETABLE_H

#include <QDialog>
#include <QVector>

#include "utils.h"

namespace Ui {
class DialogVoltageTable;
}

class DialogVoltageTable : public QDialog
{
    Q_OBJECT

public:
    explicit DialogVoltageTable(QWidget *parent = nullptr);
    ~DialogVoltageTable();

private slots:
    void on_anodeFrom_spinBox_editingFinished();

    void on_anodeTo_spinBox_editingFinished();

    void on_anodeStep_spinBox_valueChanged(int arg1);

    void on_anode_tableWidget_cellChanged(int row, int column);

    void on_clearAnode_pushButton_clicked();

    void on_focusingFrom_spinBox_editingFinished();

    void on_focusingTo_spinBox_editingFinished();

    void on_focusingStep_spinBox_valueChanged(int arg1);

    void on_focusing_tableWidget_cellChanged(int row, int column);

    void on_clearFocusing_pushButton_clicked();

private:
    Ui::DialogVoltageTable *ui;

    QVector<int> anodeTab;
    QVector<int> focusingTab;

    void fillAnode();
    void fillFocusing();
};

#endif // DIALOGVOLTAGETABLE_H
