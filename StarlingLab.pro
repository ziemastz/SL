TEMPLATE = subdirs

SUBDIRS += \
    Lib \
    UI

UI.depends = Lib
