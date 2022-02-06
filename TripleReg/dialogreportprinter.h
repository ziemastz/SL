#ifndef DIALOGREPORTPRINTER_H
#define DIALOGREPORTPRINTER_H

#include <QDialog>

namespace Ui {
class DialogReportPrinter;
}

class DialogReportPrinter : public QDialog
{
    Q_OBJECT

public:
    explicit DialogReportPrinter(QWidget *parent = nullptr);
    ~DialogReportPrinter();

private:
    Ui::DialogReportPrinter *ui;
};

#endif // DIALOGREPORTPRINTER_H
