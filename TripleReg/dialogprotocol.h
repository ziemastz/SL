#ifndef DIALOGPROTOCOL_H
#define DIALOGPROTOCOL_H

#include <QDialog>

namespace Ui {
class DialogProtocol;
}

class DialogProtocol : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProtocol(QWidget *parent = nullptr);
    ~DialogProtocol();

private:
    Ui::DialogProtocol *ui;
};

#endif // DIALOGPROTOCOL_H
