#ifndef DATABASERESULTS_H
#define DATABASERESULTS_H
#include "Model/baseModel.h"
class DatabaseResults
{
public:
    ~DatabaseResults()
    {
        foreach(BaseModel* model,_results)
            delete model;
    }
    void add(BaseModel* model)
    {
        _results << model;
    }
    BaseModel* const& at(const int& index)
    {
        return _results.at(index);
    }
    int count() const
    {
        return _results.count();
    }
private:
    QVector<BaseModel*> _results;
};

#endif // DATABASERESULTS_H
