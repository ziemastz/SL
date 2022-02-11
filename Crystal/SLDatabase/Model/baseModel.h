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

    bool operator==(const BaseModel &other) const
    {
        QVariantList recOther = other.record();
        QVariantList rec = this->record();
        for(int i=0; i<rec.count(); i++){
            if(recOther.at(i) != rec.at(i))
                return false;
        }
        return true;
    }
};

#endif // BASEMODEL_H
