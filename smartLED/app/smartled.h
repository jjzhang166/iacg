#ifndef SMARTLED_H
#define SMARTLED_H

#include "bootmanager.h"
#include "fontmanager.h"
#include "mailmanager.h"
#include "serialportmanager.h"
#include "application.h"
#include <QPixmap>
#include <QSplashScreen>
#include <memory>

namespace SmartLED {
    extern std::unique_ptr<Application> app;
    extern std::unique_ptr<BootManager> bootmanager;
    extern std::unique_ptr<FontManager> fontmanager;
    extern std::unique_ptr<MailManager> mailmanager;
    extern std::unique_ptr<SerialportManager> serialportmanager;
    extern QString workpath;
    extern QSplashScreen *splash;
    extern QPixmap *splash_pixmap;
    void init();
}

#endif // SMARTLED_H
