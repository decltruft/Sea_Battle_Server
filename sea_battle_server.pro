QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    seabattledb.cpp \
    seabattleserver.cpp \
    userstable.cpp

HEADERS += \
    mainwindow.h \
    seabattledb.h \
    seabattleserver.h \
    server_commands.h \
    userstable.h

FORMS += \
    mainwindow.ui \
    userstable.ui

win32:RC_FILE = file.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
