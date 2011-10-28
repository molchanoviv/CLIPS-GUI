#-------------------------------------------------
#
# Project created by QtCreator 2011-09-14T13:49:56
#
#-------------------------------------------------

QT       += core gui

TARGET = CLIPS-GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    consoleclass.cpp \
    clipsclass.cpp \
    projectstackedwidget.cpp \
    newprojectdialog.cpp

HEADERS  += mainwindow.h \
    consoleclass.h \
    clipsclass.h \
    projectstackedwidget.h \
    newprojectdialog.h

FORMS    += mainwindow.ui \
    newprojectdialog.ui

LIBS += -lclipsmm -lglibmm-2.4 -lboost_thread
LIBS += -L/usr/lib

OTHER_FILES +=

RESOURCES += \
    resources.qrc
