QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FileSystem/sources/filesystem.cpp \
    FileSystem/sources/mainfun.cpp \
    FileSystem/sources/user.cpp \
    dialog.cpp \
    filesystemitem.cpp \
    filesystemlistwidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    FileSystem/headers/filesystem.h \
    FileSystem/headers/main.h \
    FileSystem/headers/types.h \
    FileSystem/headers/user.h \
    dialog.h \
    filesystemitem.h \
    filesystemlistwidget.h \
    mainwindow.h

FORMS += \
    dialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
