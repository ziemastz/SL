#ifndef DIALOGADDEVEN_H
#define DIALOGADDEVEN_H

#include <QDialog>
#include <QMessageBox>
#include "settings.h"
#include "dbcrystal.h"

namespace Ui {
class DialogAddEven;
}

class DialogAddEven : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddEven(QWidget *parent = nullptr);
    ~DialogAddEven();

private slots:
    void on_cancel_pushButton_clicked();

    void on_add_pushButton_clicked();

private:
    Ui::DialogAddEven *ui;
};

#endif // DIALOGADDEVEN_H
