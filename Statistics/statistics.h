#ifndef STATISTICS_H
#define STATISTICS_H
#include <QVector>
#include <math.h>

class Statistics
{
public:
    static double arithmeticAverage(const QVector<double> &tab);
    static double standardDeviation(const QVector<double> &tab);
};

#endif // STATISTICS_H
