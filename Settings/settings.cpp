#include "settings.h"
// default value;
int Settings::_loggedUserId = 0;

int Settings::loggedUserId()
{
    return _loggedUserId;
}

void Settings::setLoggedUserId(int newLoggedUserId)
{
    _loggedUserId = newLoggedUserId;
}
