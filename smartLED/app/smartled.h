/****************************************************************************
**
** Copyright (C) 2017 dengjunkai.
** All rights reserved.
** Contact: linuxlike@foxmail.com
**
******************************************************************************/
#ifndef SMARTLED_H
#define SMARTLED_H

#include "bootmanager.h"
#include "fontmanager.h"
#include "mailmanager.h"
#include "serialportmanager.h"
#include "application.h"
#include "frame.h"
#include <QSplashScreen>
#include <QMessageBox>
#include <memory>

namespace SmartLED {
    extern std::unique_ptr<Application> app;
    extern std::unique_ptr<BootManager> bootmanager;
    extern std::unique_ptr<FontManager> fontmanager;
    extern std::unique_ptr<MailManager> mailmanager;
    extern std::unique_ptr<SerialportManager> serialportmanager;
    extern QString workpath;
    extern QSplashScreen *splash;
    extern QColor splash_color;
    void init();
}

#endif // SMARTLED_H
