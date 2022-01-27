#ifndef BASEMODEL_H
#define BASEMODEL_H
#include <QString>
#include <QVector>
#include <QVariantList>
class BaseModel
{
public:
    // most have id
    int id;
    // here model values
    //... and last two position in models
    QString lastModification;
    int userId;
    virtual ~BaseModel() {}
    virtual BaseModel* copy() = 0;
    virtual QString tableName()const = 0;
    virtual void setRecord(const QVariantList& record) = 0;
    virtual QVariantList record()const = 0;

    QVariant record(const int& index)const
    {
        if((index >= 0) && (index < count())) {
            return record().at(index);
        }else {
            return QVariant();
        }
    }

    int count()const
    {
        return record().count();
    }
};

#endif // BASEMODEL_H
