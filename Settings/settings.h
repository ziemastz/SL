#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
public:
    static int loggedUserId();
    static void setLoggedUserId(int newLoggedUserId);

private:
    static int _loggedUserId;
};

#endif // SETTINGS_H
