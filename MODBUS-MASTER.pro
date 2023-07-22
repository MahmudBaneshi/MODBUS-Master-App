QT       += core gui
QT       += quickwidgets
QT       += sql
QT       += serialport
QT       += printsupport
QT       += charts

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
    adddevwin.cpp \
    breakeritem.cpp \
    breakerstablewin.cpp \
    checkboxdelegate.cpp \
    comboboxdelegate.cpp \
    connectionthread.cpp \
    controlviewwin.cpp \
    databasethread.cpp \
    doublespinboxdelegate.cpp \
    linediagramscene.cpp \
    lineeditdelegate.cpp \
    main.cpp \
    mainwindow.cpp \
    noteditabledelegate.cpp \
    propertyvaluedelegate.cpp \
    pushbuttondelegate.cpp \
    readcoilswin.cpp \
    readinputwin.cpp \
    readwin.cpp \
    removedevwin.cpp \
    serportsettwin.cpp \
    spinboxdelegate.cpp \
    writecoilwin.cpp \
    writewin.cpp

HEADERS += \
    adddevwin.h \
    breakeritem.h \
    breakerstablewin.h \
    checkboxdelegate.h \
    comboboxdelegate.h \
    connectionthread.h \
    controlviewwin.h \
    databasethread.h \
    doublespinboxdelegate.h \
    linediagramscene.h \
    lineeditdelegate.h \
    mainwindow.h \
    noteditabledelegate.h \
    propertyvaluedelegate.h \
    pushbuttondelegate.h \
    readcoilswin.h \
    readinputwin.h \
    readwin.h \
    removedevwin.h \
    serportsettwin.h \
    shareddata.h \
    spinboxdelegate.h \
    writecoilwin.h \
    writewin.h

FORMS += \
    adddevwin.ui \
    breakerstablewin.ui \
    controlviewwin.ui \
    mainwindow.ui \
    readcoilswin.ui \
    readinputwin.ui \
    readwin.ui \
    removedevwin.ui \
    serportsettwin.ui \
    writecoilwin.ui \
    writewin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sources.qrc
