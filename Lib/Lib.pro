TEMPLATE = subdirs

SUBDIRS += \
    DBEngine \
    DBEngineSqlite \
    DBModel \
    DBRecordTDK \
    DBResults \
    DBStarlingLab \
    Utils

DBResults.depends = DBModel
DBEngine.depends = DBModel DBResults
DBEngineSqlite.depends = DBModel DBResults DBEngine Utils
DBStarlingLab.depends = DBModel DBResults DBEngine
DBRecordTDK.depends = DBModel DBResults DBEngine DBEngineSqlite DBStarlingLab Utils
