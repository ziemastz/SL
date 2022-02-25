TEMPLATE = subdirs

SUBDIRS += \
    Crystal \
    SLDatabase

Crystal.depends = SLDatabase
