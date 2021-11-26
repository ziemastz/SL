QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databasebase.cpp

HEADERS += \
    Model/usermodel.h \
    databasebase.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

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
