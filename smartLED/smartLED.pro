TEMPLATE = app

QT += qml quick serialport
CONFIG += c++11

SOURCES += main.cpp \
    serialconnect.cpp \
    maildata.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = .

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    serialconnect.h \
    maildata.h \
    SmtpClient/SmtpMime

TRANSLATIONS += locale/zh_CN.ts \
                    locale/en_US.ts

lupdate_only{
    SOURCES += UI/*.qml \
                UI/SettingPanelItem/*.qml
}

RC_ICONS = sl.ico

win32: LIBS += -L$$PWD/./ -lSMTPEmail

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
