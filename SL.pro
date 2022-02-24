TEMPLATE = subdirs
SUBDIRS += \
    DatabaseStarlingLab \
    Settings \
    Statistics \
    TripleReg \
    Utils

DatabaseStarlingLab.depends = Utils
TripleReg.depends = DatabaseStarlingLab Settings Utils
