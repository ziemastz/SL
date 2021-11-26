#ifndef STARLINGLAB_IDATABASEMODEL_H
#define STARLINGLAB_IDATABASEMODEL_H
#include <QString>
#include <QVariantList>

namespace StarlingLab {

class  IDatabaseModel
{
public:
    // most have id
    int id;
    // here model values
    //... and last two position in models
    QString timestamp;
    int userId;
    virtual ~IDatabaseModel() {}
    virtual IDatabaseModel* copy() = 0;
    virtual QString tableName()const = 0;
    virtual void setRecord(const QVariantList& record) = 0;
    virtual QVariantList record()const = 0;

    QVariant record(const int& index)const;

    int count()const;
};

} // namespace StarlingLab

#endif // STARLINGLAB_IDATABASEMODEL_H
