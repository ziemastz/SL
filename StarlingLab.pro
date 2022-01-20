TEMPLATE = subdirs

SUBDIRS += \
    Console \
    Lib \
    UI

UI.depends = Lib
