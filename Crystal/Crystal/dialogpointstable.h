#ifndef DIALOGPOINTSTABLE_H
#define DIALOGPOINTSTABLE_H

#include <QDialog>

#include "utils.h"

namespace Ui {
class DialogPointsTable;
}

class DialogPointsTable : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPointsTable(QWidget *parent = nullptr);
    ~DialogPointsTable();

    const QString &typePoints() const;

    QVector<double> points() const;

    void setTypePoints(const QString &newTypePoints);

    void setPoints(const QStringList &newPoints);

private slots:
    void on_cancel_pushButton_clicked();

    void on_clear_pushButton_clicked();

    void on_set_pushButton_clicked();

    void on_points_tableWidget_cellChanged(int row, int column);

private:
    Ui::DialogPointsTable *ui;
    QString _typePoints;
    QStringList _points;
};

#endif // DIALOGPOINTSTABLE_H
