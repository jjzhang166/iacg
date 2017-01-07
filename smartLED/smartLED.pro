TEMPLATE = app

QT += qml quick serialport
CONFIG += c++11

SOURCES += main.cpp \
    serialconnect.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = .

# Default rules for deployment.
include(deployment.pri)

INCLUDEPATH += "D:\Microsoft Visual Studio 14.0\VC\include" \
                "D:\Microsoft Visual Studio 14.0\VC\atlmfc\include" \
                "C:\Program Files (x86)\Windows Kits\10\Include\10.0.10240.0\ucrt"  \
                "C:\Program Files (x86)\Windows Kits\8.1\Include\um"    \
                "C:\Program Files (x86)\Windows Kits\8.1\Include\shared"    \
                "C:\Program Files (x86)\Windows Kits\8.1\Include\winrt"

LIBS += "-LD:\Microsoft Visual Studio 14.0\VC\lib\amd64"    \
        "-LD:\Microsoft Visual Studio 14.0\VC\atlmfc\lib\amd64"   \
        "-LC:\Program Files (x86)\Windows Kits\10\lib\10.0.10240.0\ucrt\x64"    \
        "-LC:\Program Files (x86)\Windows Kits\8.1\lib\winv6.3\um\x64"    \
        "-LC:\Program Files (x86)\Windows Kits\NETFXSDK\4.6.1\Lib\um\x64"

HEADERS += \
    serialconnect.h

TRANSLATIONS += locale/zh_CN.ts \
                    locale/en_US.ts

lupdate_only{
    SOURCES += UI/*.qml
}

RC_ICONS = sl.ico
