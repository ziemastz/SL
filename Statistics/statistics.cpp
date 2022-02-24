#include "statistics.h"


double Statistics::arithmeticAverage(const QVector<double> &tab)
{
    double ret = 0;
    double n = tab.size();
    for(int i=0; i<n; i++) {
        ret += tab.at(i);
    }
    return ret/n;
}

double Statistics::standardDeviation(const QVector<double> &tab)
{
    double ret = 0;
    double avarage = arithmeticAverage(tab);
    double n = tab.size();

    foreach(double value, tab)
        ret += pow(value-avarage,2);

    return sqrt(ret/(n-1));
}
