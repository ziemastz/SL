QT       += core gui sql serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    counter.cpp \
    counts.cpp \
    dialogaddeven.cpp \
    dialogcreateanaccount.cpp \
    dialogmeasurementprocess.cpp \
    dialogmeasurementreport.cpp \
    dialogpowersupplyprocess.cpp \
    dialogprotocol.cpp \
    dialogsinginuser.cpp \
    dialogvoltagetable.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    reportgenerator.cpp \
    workermeasurementprocess.cpp

HEADERS += \
    counter.h \
    counts.h \
    dialogaddeven.h \
    dialogcreateanaccount.h \
    dialogmeasurementprocess.h \
    dialogmeasurementreport.h \
    dialogpowersupplyprocess.h \
    dialogprotocol.h \
    dialogsinginuser.h \
    dialogvoltagetable.h \
    mainwindow.h \
    map.h \
    reportgenerator.h \
    workermeasurementprocess.h

FORMS += \
    dialogaddeven.ui \
    dialogcreateanaccount.ui \
    dialogmeasurementprocess.ui \
    dialogmeasurementreport.ui \
    dialogpowersupplyprocess.ui \
    dialogprotocol.ui \
    dialogsinginuser.ui \
    dialogvoltagetable.ui \
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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Utils/release/ -lUtils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Utils/debug/ -lUtils

INCLUDEPATH += $$PWD/../Utils
DEPENDPATH += $$PWD/../Utils

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Utils/release/libUtils.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Utils/debug/libUtils.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Utils/release/Utils.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Utils/debug/Utils.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../CAEN/PowerSupplyN1470/release/ -lPowerSupplyN1470
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../CAEN/PowerSupplyN1470/debug/ -lPowerSupplyN1470

INCLUDEPATH += $$PWD/../../CAEN/PowerSupplyN1470
DEPENDPATH += $$PWD/../../CAEN/PowerSupplyN1470

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../CAEN/PowerSupplyN1470/release/libPowerSupplyN1470.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../CAEN/PowerSupplyN1470/debug/libPowerSupplyN1470.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../CAEN/PowerSupplyN1470/release/PowerSupplyN1470.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../CAEN/PowerSupplyN1470/debug/PowerSupplyN1470.lib

win32: LIBS += -L$$PWD/../../CAEN/PowerSupplyN1470/CAENHVWrapper/lib/x86_64/ -lCAENHVWrapper

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Adept/MAC3Counter/release/ -lMAC3Counter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Adept/MAC3Counter/debug/ -lMAC3Counter

INCLUDEPATH += $$PWD/../../Adept/MAC3Counter
DEPENDPATH += $$PWD/../../Adept/MAC3Counter

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Adept/MAC3Counter/release/libMAC3Counter.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Adept/MAC3Counter/debug/libMAC3Counter.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../Adept/MAC3Counter/release/MAC3Counter.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../Adept/MAC3Counter/debug/MAC3Counter.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Adept/digilent.adept.sdk_v2.4.2/lib64/ -ldmgr
else:win32:CONFIG(debug, debug|release): LIBS += -$$PWD/../../Adept/digilent.adept.sdk_v2.4.2/lib64/ -ldmgr

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Adept/digilent.adept.sdk_v2.4.2/lib64/ -ldepp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Adept/digilent.adept.sdk_v2.4.2/lib64/ -ldepp

INCLUDEPATH += $$PWD/../../Adept/digilent.adept.sdk_v2.4.2/include
DEPENDPATH += $$PWD/../../Adept/digilent.adept.sdk_v2.4.2/include
