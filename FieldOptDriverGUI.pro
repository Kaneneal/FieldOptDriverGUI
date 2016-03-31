include(../defaults.pri)

QT       += core gui

CONFIG += c++11

LIBS += -L$$OUT_PWD/../Utilities -lutilities

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FieldOptDriverGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mwelldialog.cpp \
    bashdialog.cpp \
    modwellcompletionsdialog.cpp \
    modwellcontrolsdialog.cpp \
    modwellvariablesdialog.cpp \
    optparametersdialog.cpp \
    optconstraintdialog.cpp \
    optobjectivedialog.cpp

HEADERS  += mainwindow.h \
    mwelldialog.h \
    bashdialog.h \
    modwellcompletionsdialog.h \
    modwellcontrolsdialog.h \
    modwellvariablesdialog.h \
    optparametersdialog.h \
    optconstraintdialog.h \
    optobjectivedialog.h

FORMS    += mainwindow.ui \
    mwelldialog.ui \
    bashdialog.ui \
    aboutdialog.ui \
    modwellcompletionsdialog.ui \
    modwellcontrolsdialog.ui \
    modwellvariablesdialog.ui \
    optconstraintdialog.ui \
    optparametersdialog.ui \
    optobjectivedialog.ui

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

