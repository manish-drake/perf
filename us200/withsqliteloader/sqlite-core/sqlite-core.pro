QT       -= core gui

TEMPLATE = lib
CONFIG += c++11
CONFIG -= qt app_bundle

SOURCES += \
    columns.cpp \
    db.cpp \
    table.cpp \
    persistablebase.cpp \
    objecttype.cpp \
    catalogue.cpp \
    dbcache.cpp \
    master.cpp \
    datetime.cpp

HEADERS += \
    columns.h \
    databroker.h \
    datadefinition.h \
    db.h \
    table.h \
    persistablebase.h \
    objecttype.h \
    sqlscripthelper.h \
    filter.h \
    catalogue.h \
    dbcache.h \
    master.h \
    datetime.h \
    charmap.h

#!macx:!ios{
#     QMAKE_LFLAGS +=-Wl,-Map=sqlite-core.map
#     QMAKE_LFLAGS_DEBUG +=-Wl,-Map=sqlite-core.map
#}

unix {
    LIBS += -lsqlite3
    target.path = /opt/ts-qt/bin
    INSTALLS += target
}

win32: LIBS += -LC:/sqlite/ -lsqlite3
