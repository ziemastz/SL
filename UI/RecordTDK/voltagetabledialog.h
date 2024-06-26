#ifndef VOLTAGETABLEDIALOG_H
#define VOLTAGETABLEDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "utils.h"

namespace Ui {
class VoltageTableDialog;
}

class VoltageTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VoltageTableDialog(QWidget *parent = nullptr);
    ~VoltageTableDialog();

    const QVector<int> &getAnodeTab() const;

    const QVector<int> &getFocusingTab() const;

    void setAnodeTab(const QVector<int> &newAnodeTab);

    void setFocusingTab(const QVector<int> &newFocusingTab);

private slots:
    void on_fillAnode_pushButton_clicked();

    void on_fillFocusing_pushButton_clicked();

    void on_cancel_pushButton_clicked();

    void on_clear_pushButton_clicked();

    void on_set_pushButton_clicked();

    void on_anode_tableWidget_cellChanged(int row, int column);

    void on_focusing_tableWidget_cellChanged(int row, int column);

    void on_clearAnode_pushButton_clicked();

    void on_clearFocusing_pushButton_clicked();

private:
    Ui::VoltageTableDialog *ui;
    QVector<int> anodeTab;
    QVector<int> focusingTab;
};

#endif // VOLTAGETABLEDIALOG_H
