QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogsinginuser.cpp \
    formnewmeasurement.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    dialogsinginuser.h \
    formnewmeasurement.h \
    mainwindow.h

FORMS += \
    dialogsinginuser.ui \
    formnewmeasurement.ui \
    mainwindow.ui

TRANSLATIONS += \
    TripleReg_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations
RC_FILE = icon.rc
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DatabaseStarlingLab/release/ -lDatabaseStarlingLab
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DatabaseStarlingLab/debug/ -lDatabaseStarlingLab

INCLUDEPATH += $$PWD/../DatabaseStarlingLab
DEPENDPATH += $$PWD/../DatabaseStarlingLab

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DatabaseStarlingLab/release/libDatabaseStarlingLab.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DatabaseStarlingLab/debug/libDatabaseStarlingLab.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DatabaseStarlingLab/release/DatabaseStarlingLab.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DatabaseStarlingLab/debug/DatabaseStarlingLab.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Settings/release/ -lSettings
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Settings/debug/ -lSettings

INCLUDEPATH += $$PWD/../Settings
DEPENDPATH += $$PWD/../Settings

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Settings/release/libSettings.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Settings/debug/libSettings.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Settings/release/Settings.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Settings/debug/Settings.lib

RESOURCES += \
    resources.qrc
