#ifndef PROTOCOLDIALOG_H
#define PROTOCOLDIALOG_H

#include <QDialog>

namespace Ui {
class ProtocolDialog;
}

class ProtocolDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProtocolDialog(QWidget *parent = nullptr);
    ~ProtocolDialog();

private:
    Ui::ProtocolDialog *ui;
};

#endif // PROTOCOLDIALOG_H
