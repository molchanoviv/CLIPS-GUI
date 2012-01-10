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
    addtemplatedialog.cpp \
    addfactbytemplatedialog.cpp \
    adddeffactsdialog.cpp \
    addruledialog.cpp \
    addglobalsdialog.cpp \
    addfunctiondialog.cpp

HEADERS  += mainwindow.h \
    consoleclass.h \
    clipsclass.h \
    projectstackedwidget.h \
    newprojectdialog.h \
    addtemplatedialog.h \
    addfactbytemplatedialog.h \
    adddeffactsdialog.h \
    addruledialog.h \
    addglobalsdialog.h \
    addfunctiondialog.h

FORMS    += mainwindow.ui \
    newprojectdialog.ui \
    addtemplatedialog.ui \
    addfactbytemplatedialog.ui \
    adddeffactsdialog.ui \
    addruledialog.ui \
    addglobalsdialog.ui \
    addfunctiondialog.ui

LIBS += -lclips #-lboost_thread
LIBS += -L/usr/lib

OTHER_FILES += \
    README \
    TODO

RESOURCES += \
    resources.qrc

TRANSLATIONS += translations/CLIPS-GUI_ru.ts






