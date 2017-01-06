#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QVariant>
#include <QtQml>
#include <Windows.h>

#include "serialconnect.h"

LONG WINAPI UnExceptionFilter(PEXCEPTION_POINTERS pExInfo) {
    QVariant code((quint32)pExInfo->ExceptionRecord->ExceptionCode);
    code = QVariant(QString("0x") + QString::number(code.toUInt(),16).toUpper());
    QString info("UnExceptedError");
    QString cmdline = QString("BugReport.exe ") + code.toString() + " " + info;

    TCHAR szCmdLine[MAX_PATH];
    wcscpy_s(szCmdLine,_countof(szCmdLine),cmdline.toStdWString().c_str());
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    CreateProcess(NULL,                             //pAppName
                  szCmdLine,   //cmdLine
                  NULL,                             //psaProc
                  NULL,                             //psaThread
                  FALSE,                            //InheritHandles
                  0,                                //createFlags
                  NULL,                             //pEnv
                  NULL,                             //pCurDir
                  &si,                              //startInfo
                  &pi                               //processInfo
                );

    ExitProcess(-1);
}

int main(int argc, char *argv[])
{
    SetUnhandledExceptionFilter(UnExceptionFilter);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("sc",new serialConnect);
    engine.addImportPath("D:/QMLStudy/smartLED");
    engine.load(QUrl(QStringLiteral("qrc:/UI/main.qml")));

    return app.exec();
}
