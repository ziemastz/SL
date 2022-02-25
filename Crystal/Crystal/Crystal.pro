QT       += core gui sql serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    counter.cpp \
    dbcrystal.cpp \
    dialogaddeven.cpp \
    dialogcreateanaccount.cpp \
    dialogmeasurementreport.cpp \
    dialogmsgbox.cpp \
    dialognewmeasurement.cpp \
    dialogpointstable.cpp \
    dialogsinginuser.cpp \
    formnewmeasurement.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    reportgenerator.cpp \
    workermeasurement.cpp

HEADERS += \
    Model/crystalLogbookModel.h \
    Model/crystalMeasurementProtocolModel.h \
    Model/crystalMeasurementRAWModel.h \
    Model/crystalMeasurementRegisterModel.h \
    Model/crystalMeasuringSystemModel.h \
    Model/crystalProtocolModel.h \
    Model/crystalSettingsModel.h \
    counter.h \
    dbcrystal.h \
    dialogaddeven.h \
    dialogcreateanaccount.h \
    dialogmeasurementreport.h \
    dialogmsgbox.h \
    dialognewmeasurement.h \
    dialogpointstable.h \
    dialogsinginuser.h \
    formnewmeasurement.h \
    mainwindow.h \
    map.h \
    reportgenerator.h \
    workermeasurement.h

FORMS += \
    dialogaddeven.ui \
    dialogcreateanaccount.ui \
    dialogmeasurementreport.ui \
    dialogmsgbox.ui \
    dialognewmeasurement.ui \
    dialogpointstable.ui \
    dialogsinginuser.ui \
    formnewmeasurement.ui \
    mainwindow.ui

TRANSLATIONS += \
    Crystal_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations
RC_FILE = icon.rc
RESOURCES += \
    resources.qrc
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SLDatabase/release/ -lSLDatabase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SLDatabase/debug/ -lSLDatabase

INCLUDEPATH += $$PWD/../SLDatabase
DEPENDPATH += $$PWD/../SLDatabase

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../SLDatabase/release/libSLDatabase.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../SLDatabase/debug/libSLDatabase.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../SLDatabase/release/SLDatabase.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../SLDatabase/debug/SLDatabase.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Settings/release/ -lSettings
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Settings/debug/ -lSettings

INCLUDEPATH += $$PWD/../../Settings
DEPENDPATH += $$PWD/../../Settings

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Settings/release/libSettings.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Settings/debug/libSettings.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Settings/release/Settings.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Settings/debug/Settings.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Utils/release/ -lUtils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Utils/debug/ -lUtils

INCLUDEPATH += $$PWD/../../Utils
DEPENDPATH += $$PWD/../../Utils

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Utils/release/libUtils.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Utils/debug/libUtils.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Utils/release/Utils.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Utils/debug/Utils.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Adept/NaICounter/release/ -lNaICounter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../Adept/NaICounter/debug/ -lNaICounter

INCLUDEPATH += $$PWD/../../../Adept/NaICounter
DEPENDPATH += $$PWD/../../../Adept/NaICounter

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../Adept/NaICounter/release/libNaICounter.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../Adept/NaICounter/debug/libNaICounter.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../Adept/NaICounter/release/NaICounter.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../Adept/NaICounter/debug/NaICounter.lib

win32: LIBS += -L$$PWD/../../../Adept/digilent.adept.sdk_v2.4.2/lib64/ -ldepp

INCLUDEPATH += $$PWD/../../../Adept/digilent.adept.sdk_v2.4.2/include
DEPENDPATH += $$PWD/../../../Adept/digilent.adept.sdk_v2.4.2/include

win32: LIBS += -L$$PWD/../../../Adept/digilent.adept.sdk_v2.4.2/lib64/ -ldmgr

INCLUDEPATH += $$PWD/../../../Adept/digilent.adept.sdk_v2.4.2/include
DEPENDPATH += $$PWD/../../../Adept/digilent.adept.sdk_v2.4.2/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Statistics/release/ -lStatistics
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Statistics/debug/ -lStatistics

INCLUDEPATH += $$PWD/../../Statistics
DEPENDPATH += $$PWD/../../Statistics

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Statistics/release/libStatistics.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Statistics/debug/libStatistics.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Statistics/release/Statistics.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Statistics/debug/Statistics.lib
