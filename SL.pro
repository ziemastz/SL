TEMPLATE = subdirs
SUBDIRS += \
    DatabaseStarlingLab \
    Settings \
    TripleReg \
    Utils

DatabaseStarlingLab.depends = Utils
TripleReg.depends = DatabaseStarlingLab Settings Utils
