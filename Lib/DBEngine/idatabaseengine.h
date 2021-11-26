#ifndef STARLINGLAB_IDATABASEENGINE_H
#define STARLINGLAB_IDATABASEENGINE_H
#include "idatabasemodel.h"
#include "dbresults.h"
namespace StarlingLab {

class IDatabaseEngine
{
public:
    virtual ~IDatabaseEngine() {}
    virtual bool insert(IDatabaseModel* model) = 0;
    virtual DBResults select(IDatabaseModel* model, const QString& filter = QString(), const int& limit = 0, const int& offset = 0) = 0;
    virtual bool update(IDatabaseModel* model) = 0;
    virtual bool remove(IDatabaseModel* model) = 0;
};

} // namespace StarlingLab

#endif // STARLINGLAB_IDATABASEENGINE_H
