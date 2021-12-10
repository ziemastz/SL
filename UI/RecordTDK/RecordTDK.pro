QT       += core gui sql serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addmeasurementdialog.cpp \
    counter.cpp \
    counts.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
#    monitoringdialog.cpp \
    protocoldialog.cpp \
    settingsdialog.cpp \
    voltagetabledialog.cpp

HEADERS += \
    addmeasurementdialog.h \
    counter.h \
    counts.h \
    logindialog.h \
    mainwindow.h \
#    monitoringdialog.h \
    protocoldialog.h \
    settingsdialog.h \
    voltagetabledialog.h

FORMS += \
    addmeasurementdialog.ui \
    logindialog.ui \
    mainwindow.ui \
    monitoringdialog.ui \
    protocoldialog.ui \
    settingsdialog.ui \
    voltagetabledialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Lib/DBRecordTDK/release/ -lDBRecordTDK
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Lib/DBRecordTDK/debug/ -lDBRecordTDK

INCLUDEPATH += $$PWD/../../Lib/DBRecordTDK
DEPENDPATH += $$PWD/../../Lib/DBRecordTDK

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBRecordTDK/release/libDBRecordTDK.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBRecordTDK/debug/libDBRecordTDK.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBRecordTDK/release/DBRecordTDK.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBRecordTDK/debug/DBRecordTDK.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Lib/DBStarlingLab/release/ -lDBStarlingLab
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Lib/DBStarlingLab/debug/ -lDBStarlingLab

INCLUDEPATH += $$PWD/../../Lib/DBStarlingLab
DEPENDPATH += $$PWD/../../Lib/DBStarlingLab

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBStarlingLab/release/libDBStarlingLab.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBStarlingLab/debug/libDBStarlingLab.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBStarlingLab/release/DBStarlingLab.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBStarlingLab/debug/DBStarlingLab.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Lib/DBEngineSqlite/release/ -lDBEngineSqlite
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Lib/DBEngineSqlite/debug/ -lDBEngineSqlite

INCLUDEPATH += $$PWD/../../Lib/DBEngineSqlite
DEPENDPATH += $$PWD/../../Lib/DBEngineSqlite

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBEngineSqlite/release/libDBEngineSqlite.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBEngineSqlite/debug/libDBEngineSqlite.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBEngineSqlite/release/DBEngineSqlite.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBEngineSqlite/debug/DBEngineSqlite.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Lib/DBEngine/release/ -lDBEngine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Lib/DBEngine/debug/ -lDBEngine

INCLUDEPATH += $$PWD/../../Lib/DBEngine
DEPENDPATH += $$PWD/../../Lib/DBEngine

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBEngine/release/libDBEngine.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBEngine/debug/libDBEngine.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBEngine/release/DBEngine.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBEngine/debug/DBEngine.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Lib/DBModel/release/ -lDBModel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Lib/DBModel/debug/ -lDBModel

INCLUDEPATH += $$PWD/../../Lib/DBModel
DEPENDPATH += $$PWD/../../Lib/DBModel

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBModel/release/libDBModel.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBModel/debug/libDBModel.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBModel/release/DBModel.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBModel/debug/DBModel.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Lib/DBResults/release/ -lDBResults
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Lib/DBResults/debug/ -lDBResults

INCLUDEPATH += $$PWD/../../Lib/DBResults
DEPENDPATH += $$PWD/../../Lib/DBResults

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBResults/release/libDBResults.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBResults/debug/libDBResults.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBResults/release/DBResults.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/DBResults/debug/DBResults.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Lib/Utils/release/ -lUtils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Lib/Utils/debug/ -lUtils

INCLUDEPATH += $$PWD/../../Lib/Utils
DEPENDPATH += $$PWD/../../Lib/Utils

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/Utils/release/libUtils.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/Utils/debug/libUtils.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/Utils/release/Utils.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Lib/Utils/debug/Utils.lib

win32: LIBS += -L$$PWD/../../../CAEN/PowerSupplyN1470/CAENHVWrapper/lib/x86/ -lCAENHVWrapper

INCLUDEPATH += $$PWD/../../../CAEN/PowerSupplyN1470/CAENHVWrapper/include
DEPENDPATH += $$PWD/../../../CAEN/PowerSupplyN1470/CAENHVWrapper/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../CAEN/PowerSupplyN1470/release/ -lPowerSupplyN1470
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../CAEN/PowerSupplyN1470/debug/ -lPowerSupplyN1470

INCLUDEPATH += $$PWD/../../../CAEN/PowerSupplyN1470
DEPENDPATH += $$PWD/../../../CAEN/PowerSupplyN1470

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../CAEN/PowerSupplyN1470/release/libPowerSupplyN1470.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../CAEN/PowerSupplyN1470/debug/libPowerSupplyN1470.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../CAEN/PowerSupplyN1470/release/PowerSupplyN1470.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../CAEN/PowerSupplyN1470/debug/PowerSupplyN1470.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Adept/MAC3Counter/release/ -lMAC3Counter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../Adept/MAC3Counter/debug/ -lMAC3Counter

INCLUDEPATH += $$PWD/../../../Adept/MAC3Counter
DEPENDPATH += $$PWD/../../../Adept/MAC3Counter

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../Adept/MAC3Counter/release/libMAC3Counter.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../Adept/MAC3Counter/debug/libMAC3Counter.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../Adept/MAC3Counter/release/MAC3Counter.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../Adept/MAC3Counter/debug/MAC3Counter.lib

win32: LIBS += -L$$PWD/../../../Adept/MAC3Counter/digilent.adept.sdk_v2.4.2/lib/ -ldmgr
win32: LIBS += -L$$PWD/../../../Adept/MAC3Counter/digilent.adept.sdk_v2.4.2/lib/ -ldepp

INCLUDEPATH += $$PWD/../../../Adept/MAC3Counter/digilent.adept.sdk_v2.4.2/include
DEPENDPATH += $$PWD/../../../Adept/MAC3Counter/digilent.adept.sdk_v2.4.2/include
