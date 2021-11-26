#ifndef STARLINGLAB_DATABASEBASE_H
#define STARLINGLAB_DATABASEBASE_H

#include <QObject>
#include <QDateTime>
#include "idatabaseengine.h"
#include "Model/usermodel.h"

namespace StarlingLab {

class DatabaseBase : public QObject
{
public:
    const QString FORMAT_TIMESTAMP = "yyyy-MM-dd hh:mm:ss";
    DatabaseBase();
    ~DatabaseBase();
    static void addEngine(IDatabaseEngine *engine);

    bool insert(IDatabaseModel *model);
    bool update(IDatabaseModel *model);
    bool remove(IDatabaseModel *model);

    IDatabaseEngine *engine() const;

    QString lastError();

    bool loginUser(const QString& username, const QString& password);
    UserModel* getLoggeduser() const;
    UserModel getUser(const int& id);
    QStringList getUsernames();

private:
    static IDatabaseEngine *_engine;
    static UserModel *_loggedUser;

    QString _lastError;
};

} // namespace StarlingLab

#endif // STARLINGLAB_DATABASEBASE_H
