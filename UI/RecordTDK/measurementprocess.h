#ifndef MEASUREMENTPROCESS_H
#define MEASUREMENTPROCESS_H

#include <QObject>

class Points
{
public:
    void set(const int &size) {
        _points = size;
        n = 0;
    };
    bool next() {
        n++;
        if(n<_points)
            return true;
        else
            return false;
    };
    void reset() {
        n = 0;
    };
    int value() {
        return n;
    }
private:
    int _points;
    int n;
};

class MeasurementProcess : public QObject
{
    Q_OBJECT
public:
    explicit MeasurementProcess(QObject *parent = nullptr);

signals:
    void showMessageBox(const QString &title, const QString &text);
    void finished();

    void addRecord();
    void updateLastRecord(const QString &record);

public slots:
    void run();
private slots:
    void process();

private:
    Points repeat;
    Points anode;
    Points focusing;

};


#endif // MEASUREMENTPROCESS_H
