#include "idatabasemodel.h"

namespace StarlingLab {

QVariant IDatabaseModel::record(const int &index) const {
    if((index >= 0) && (index < count())) {
        return record().at(index);
    }else {
        return QVariant();
    }
}

int IDatabaseModel::count() const {
    return record().count();
}


} // namespace StarlingLab
