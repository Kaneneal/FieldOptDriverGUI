include(../defaults.pri)

QT       += core gui

CONFIG += c++11

LIBS += -L$$OUT_PWD/../Utilities -lutilities

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FieldOptDriverGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    optdialog.cpp \
    mwelldialog.cpp \
    bashdialog.cpp

HEADERS  += mainwindow.h \
    optdialog.h \
    mwelldialog.h \
    bashdialog.h

FORMS    += mainwindow.ui \
    optparametersdialog.ui \
    optobjetivedialog.ui \
    optconstraintsdialog.ui \
    mwellvariablesdialog.ui \
    mwelldialog.ui \
    mwellcontroldialog.ui \
    mwellcompletionsdialog.ui \
    bashdialog.ui \
    aboutdialog.ui

RESOURCES += \
    myres.qrc

DISTFILES += \
    save-icon.png \
    newdoc.png \
    editIcon.png \
    bluepensil.png \
    blankdoc.png \
    editicon.svg \
    Open-file.ico \
    exit.ico

