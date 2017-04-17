﻿/****************************************************************************
**
** Copyright (C) 2017 dengjunkai.
** All rights reserved.
** Contact: linuxlike@foxmail.com
**
******************************************************************************/

#include <QApplication>
#include <QTranslator>
#include "app/smartled.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator ts;
    ts.load(":/locale/zh_CN.qm");
    app.installTranslator(&ts);
    try{
        SmartLED::app = std::make_unique<Application>(":/splash.png");
        app.exec();
    }
    catch(...) {
        app.quit();
    }
}
