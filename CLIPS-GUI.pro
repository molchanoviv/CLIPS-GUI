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
    newprojectdialog.cpp \
    addtemplatedialog.cpp

HEADERS  += mainwindow.h \
    consoleclass.h \
    clipsclass.h \
    projectstackedwidget.h \
    newprojectdialog.h \
    addtemplatedialog.h

FORMS    += mainwindow.ui \
    newprojectdialog.ui \
    addtemplatedialog.ui

LIBS += -lclips #-lboost_thread
LIBS += -L/usr/lib

OTHER_FILES += \
    README \
    TODO

RESOURCES += \
    resources.qrc






