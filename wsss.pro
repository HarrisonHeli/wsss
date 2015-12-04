#-------------------------------------------------
#
# Project created by QtCreator 2013-07-29T17:41:00
#
#-------------------------------------------------

QT       += core gui webkitwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkit


TARGET = wsss
target.path = /opt/wsss/
INSTALLS += target

TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    webslide.cpp \
    webslideview.cpp

HEADERS  += mainwindow.h \
    webslide.h \
    webslideview.h

FORMS    += mainwindow.ui
