QT       += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    RegistryBlocker.cpp \
    gamestate.cpp \
    helpers.cpp \
    main.cpp \
    mainwindow.cpp \
    skill.cpp \
    statstab.cpp

HEADERS += \
    RegistryBlocker.h \
    gamestate.h \
    helpers.h \
    mainwindow.h \
    skill.h \
    statstab.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# win32:QMAKE_LFLAGS += -shared

win32 {
  CONFIG += embed_manifest_exe
  QMAKE_LFLAGS_WINDOWS += /MANIFESTUAC:"level='requireAdministrator'"
}

RESOURCES += \
    icons.qrc \
    styles.qrc

DISTFILES += \
    README.md \
    icons/temp \
    styles/ElegantDark.qss \
    styles/aqua.qss
