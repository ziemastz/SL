#ifndef MAP_H
#define MAP_H
#include <QObject>
#include <QList>

class Map
{
public:
    void insert(const QString &key, const QString &value);
    void clear();
    QList<QString> keys() const;
    QList<QString> values() const;
private:
    QList<QString> _keys;
    QList<QString> _values;
};

#endif // MAP_H
