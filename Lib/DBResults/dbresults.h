#ifndef STARLINGLAB_DBRESULTS_H
#define STARLINGLAB_DBRESULTS_H
#include "idatabasemodel.h"
namespace StarlingLab {

class DBResults
{
public:
    DBResults();
    ~DBResults();
    void add(IDatabaseModel* model);
    IDatabaseModel* const& at(const int& index);
    int count() const;
private:
    QVector<IDatabaseModel*> _results;
};

} // namespace StarlingLab

#endif // STARLINGLAB_DBRESULTS_H
