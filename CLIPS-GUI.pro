#-------------------------------------------------
#
# Project created by QtCreator 2011-09-14T13:49:56
#
#-------------------------------------------------

QT       += core gui

TARGET = CLIPS-GUI
TEMPLATE = app


SOURCES += src/main.cpp\
	src/mainwindow.cpp \
    src/consoleclass.cpp \
    src/clipsclass.cpp \
    src/projectstackedwidget.cpp \
    src/dialogs/newprojectdialog.cpp \
    src/dialogs/addtemplatedialog.cpp \
    src/dialogs/addfactbytemplatedialog.cpp \
    src/dialogs/adddeffactsdialog.cpp \
    src/dialogs/addruledialog.cpp \
    src/dialogs/addglobalsdialog.cpp \
    src/dialogs/addfunctiondialog.cpp

HEADERS  += src/mainwindow.h \
    src/consoleclass.h \
    src/clipsclass.h \
    src/projectstackedwidget.h \
    src/dialogs/newprojectdialog.h \
    src/dialogs/addtemplatedialog.h \
    src/dialogs/addfactbytemplatedialog.h \
    src/dialogs/adddeffactsdialog.h \
    src/dialogs/addruledialog.h \
    src/dialogs/addglobalsdialog.h \
    src/dialogs/addfunctiondialog.h

FORMS    += src/mainwindow.ui \
    src/dialogs/newprojectdialog.ui \
    src/dialogs/addtemplatedialog.ui \
    src/dialogs/addfactbytemplatedialog.ui \
    src/dialogs/adddeffactsdialog.ui \
    src/dialogs/addruledialog.ui \
    src/dialogs/addglobalsdialog.ui \
    src/dialogs/addfunctiondialog.ui

LIBS += -lclips #-lboost_thread
LIBS += -L/usr/lib

OTHER_FILES += \
    README \
    TODO

RESOURCES += \
    resources.qrc

TRANSLATIONS += translations/CLIPS-GUI_ru.ts






