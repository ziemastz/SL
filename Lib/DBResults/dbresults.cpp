#include "dbresults.h"

namespace StarlingLab {

DBResults::DBResults()
{

}

DBResults::~DBResults()
{
    foreach(IDatabaseModel* model,_results)
        delete model;
}

void DBResults::add(IDatabaseModel *model)
{
    _results << model;
}

IDatabaseModel * const &DBResults::at(const int &index)
{
    return _results.at(index);
}

int DBResults::count() const
{
    return _results.count();
}
} // namespace StarlingLab
