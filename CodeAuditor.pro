QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    anaycfile.cpp \
    cfileinfo.cpp \
    d_addfunction.cpp \
    dangerfun.cpp \
    dangerfun_manage.cpp \
    dangerinfo.cpp \
    filepane.cpp \
    funcinfo.cpp \
    funsql.cpp \
    highlighter.cpp \
    main.cpp \
    mainwindow.cpp \
    myhigher.cpp \
    mytext.cpp \
    parainfo.cpp \
    searchdia.cpp \
    logindialog.cpp

HEADERS += \
    anaycfile.h \
    cfileinfo.h \
    d_addfunction.h \
    dangerfun.h \
    dangerfun_manage.h \
    dangerinfo.h \
    filepane.h \
    funcinfo.h \
    funsql.h \
    highlighter.h \
    mainwindow.h \
    myhigher.h \
    mytext.h \
    parainfo.h \
    searchdia.h \
    logindialog.h

FORMS += \
    d_addfunction.ui \
    dangerfun_manage.ui \
    mainwindow.ui \
    searchdia.ui \
    logindialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    C:/Users/lenovo/Desktop/实验/ico/file.png \
    C:/Users/lenovo/Desktop/实验/ico/folder.png

RESOURCES += \
    res.qrc
RC_FILE=res/myico.rc
