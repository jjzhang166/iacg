#include "smartled.h"

std::unique_ptr<Application> SmartLED::app;
std::unique_ptr<BootManager> SmartLED::bootmanager;
std::unique_ptr<FontManager> SmartLED::fontmanager;
std::unique_ptr<MailManager> SmartLED::mailmanager;
std::unique_ptr<SerialportManager> SmartLED::serialportmanager;
QSplashScreen *SmartLED::splash = nullptr;
QString SmartLED::workpath;

void SmartLED::init() {
    QSettings reg_setting("HKEY_CURRENT_USER\\SOFTWARE\\SmartLED", QSettings::NativeFormat);
    SmartLED::workpath = reg_setting.value("WorkPath", "").toString();
    if(SmartLED::workpath.isEmpty())
        throw new QUnhandledException;
    QDir splash_file(SmartLED::workpath + "/splash.png");
    SmartLED::splash = splash_file.exists()? new QSplashScreen(QPixmap(splash_file.absolutePath()))
                                           : new QSplashScreen(QPixmap(":/splash.png"));
    SmartLED::splash->show();
    SmartLED::splash->showMessage("program init...");
    SmartLED::bootmanager = std::make_unique<BootManager>();
    SmartLED::fontmanager = std::make_unique<FontManager>();
    SmartLED::mailmanager = std::make_unique<MailManager>();
    SmartLED::serialportmanager = std::make_unique<SerialportManager>();
    SmartLED::app = std::make_unique<Application>();
}
