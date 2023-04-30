QT       += core gui sql
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    caddclassinfodlg.cpp \
    caddlessoninfo.cpp \
    caddscoreinfodlg.cpp \
    caddstuinfodlg.cpp \
    cclassinfodto.cpp \
    cfindstudlg.cpp \
    clessoninfodto.cpp \
    cscoreinfodto.cpp \
    cstudent.cpp \
    cstudentinfodto.cpp \
    ilogic.cpp \
    logicimpl.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    caddclassinfodlg.h \
    caddlessoninfo.h \
    caddscoreinfodlg.h \
    caddstuinfodlg.h \
    cclassinfodto.h \
    cfindstudlg.h \
    clessoninfodto.h \
    cscoreinfodto.h \
    cstudent.h \
    cstudentinfodto.h \
    ilogic.h \
    logicimpl.h \
    mainwindow.h

FORMS += \
    caddclassinfodlg.ui \
    caddlessoninfo.ui \
    caddscoreinfodlg.ui \
    caddstuinfodlg.ui \
    cfindstudlg.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
