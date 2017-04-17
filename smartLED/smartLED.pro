TEMPLATE = app

QT += gui widgets qml quick serialport
CONFIG += c++14

SOURCES += main.cpp \
    app/application.cpp \
    app/fontmanager.cpp \
    app/datamanager.cpp \
    app/serialportmanager.cpp \
    app/mailmanager.cpp \
    app/bootmanager.cpp \
    app/smartled.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = .

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    app/SmtpClient/SmtpMime \
    app/fontmanager.h \
    app/datamanager.h \
    app/serialportmanager.h \
    app/mailmanager.h \
    app/bootmanager.h \
    app/smartled.h \
    app/application.h

TRANSLATIONS += locale/zh_CN.ts \
                    locale/en_US.ts

lupdate_only{
    SOURCES += UI/*.qml \
                UI/SettingPanelItem/*.qml \
                app/*.cpp
}

RC_ICONS = sl.ico

win32: LIBS += -L$$PWD/./ -lSMTPEmail

INCLUDEPATH += $$PWD/app/.
DEPENDPATH += $$PWD/app/.

