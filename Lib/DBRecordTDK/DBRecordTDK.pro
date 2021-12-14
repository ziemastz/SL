QT -= gui
QT += sql serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dbrecordtdk.cpp

HEADERS += \
    Model/MeasurementRAWModel.h \
    Model/ProtocolModel.h \
    Model/SettingConnectionModel.h \
    Model/SettingGeneralModel.h \
    Model/TDKLogModel.h \
    dbrecordtdk.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DBStarlingLab/release/ -lDBStarlingLab
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DBStarlingLab/debug/ -lDBStarlingLab
else:unix: LIBS += -L$$OUT_PWD/../DBStarlingLab/ -lDBStarlingLab

INCLUDEPATH += $$PWD/../DBStarlingLab
DEPENDPATH += $$PWD/../DBStarlingLab

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBStarlingLab/release/libDBStarlingLab.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBStarlingLab/debug/libDBStarlingLab.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBStarlingLab/release/DBStarlingLab.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBStarlingLab/debug/DBStarlingLab.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../DBStarlingLab/libDBStarlingLab.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DBEngineSqlite/release/ -lDBEngineSqlite
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DBEngineSqlite/debug/ -lDBEngineSqlite
else:unix: LIBS += -L$$OUT_PWD/../DBEngineSqlite/ -lDBEngineSqlite

INCLUDEPATH += $$PWD/../DBEngineSqlite
DEPENDPATH += $$PWD/../DBEngineSqlite

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBEngineSqlite/release/libDBEngineSqlite.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBEngineSqlite/debug/libDBEngineSqlite.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBEngineSqlite/release/DBEngineSqlite.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBEngineSqlite/debug/DBEngineSqlite.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../DBEngineSqlite/libDBEngineSqlite.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DBModel/release/ -lDBModel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DBModel/debug/ -lDBModel
else:unix: LIBS += -L$$OUT_PWD/../DBModel/ -lDBModel

INCLUDEPATH += $$PWD/../DBModel
DEPENDPATH += $$PWD/../DBModel

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBModel/release/libDBModel.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBModel/debug/libDBModel.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBModel/release/DBModel.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBModel/debug/DBModel.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../DBModel/libDBModel.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DBEngine/release/ -lDBEngine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DBEngine/debug/ -lDBEngine
else:unix: LIBS += -L$$OUT_PWD/../DBEngine/ -lDBEngine

INCLUDEPATH += $$PWD/../DBEngine
DEPENDPATH += $$PWD/../DBEngine

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBEngine/release/libDBEngine.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBEngine/debug/libDBEngine.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBEngine/release/DBEngine.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBEngine/debug/DBEngine.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../DBEngine/libDBEngine.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DBResults/release/ -lDBResults
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DBResults/debug/ -lDBResults
else:unix: LIBS += -L$$OUT_PWD/../DBResults/ -lDBResults

INCLUDEPATH += $$PWD/../DBResults
DEPENDPATH += $$PWD/../DBResults

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBResults/release/libDBResults.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBResults/debug/libDBResults.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBResults/release/DBResults.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../DBResults/debug/DBResults.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../DBResults/libDBResults.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Utils/release/ -lUtils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Utils/debug/ -lUtils
else:unix: LIBS += -L$$OUT_PWD/../Utils/ -lUtils

INCLUDEPATH += $$PWD/../Utils
DEPENDPATH += $$PWD/../Utils

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Utils/release/libUtils.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Utils/debug/libUtils.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Utils/release/Utils.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Utils/debug/Utils.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Utils/libUtils.a
