#ifndef DIALOGMSGBOX_H
#define DIALOGMSGBOX_H

#include <QDialog>
#include "naicounter.h"
namespace Ui {
class DialogMsgBox;
}

class DialogMsgBox : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMsgBox(QWidget *parent = nullptr);
    ~DialogMsgBox();

    void setTitle(const QString &title);
    void setText(const QString &text);
    void setPortId(const int &portId);

private slots:
    void on_ok_pushButton_clicked();

    void on_cancel_pushButton_clicked();

private:
    Ui::DialogMsgBox *ui;
};

#endif // DIALOGMSGBOX_H
