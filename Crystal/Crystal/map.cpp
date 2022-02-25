#include "map.h"

void Map::insert(const QString &key, const QString &value)
{
    _keys << key;
    _values << value;
}

void Map::clear()
{
    _keys.clear();
    _values.clear();
}

QList<QString> Map::keys() const
{
    return _keys;
}

QList<QString> Map::values() const
{
    return _values;
}
