#ifndef SMARTLED_H
#define SMARTLED_H

#include "bootmanager.h"
#include "datamanager.h"
#include "fontmanager.h"
#include "mailmanager.h"
#include "serialportmanager.h"
#include "application.h"
#include <memory>

namespace SmartLED {
    extern std::unique_ptr<Application> app;
    extern std::unique_ptr<BootManager> bootmanager;
    extern std::unique_ptr<DataManager, void(*)(DataManager*)> datamanager;
    extern std::unique_ptr<FontManager> fontmanager;
    extern std::unique_ptr<MailManager> mailmanager;
    extern std::unique_ptr<SerialportManager> serialportmanager;
    void init();
}

#endif // SMARTLED_H
