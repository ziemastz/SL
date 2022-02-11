#include "dbcrystal.h"

DBCrystal::DBCrystal()
{
    setDatabaseName("crystal.db");
    setDriver("QSQLITE");
}
