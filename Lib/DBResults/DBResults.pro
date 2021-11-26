QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dbresults.cpp

HEADERS += \
    dbresults.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

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
