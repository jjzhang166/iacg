#include "smartled.h"

std::unique_ptr<Application> SmartLED::app; //= std::make_unique<Application>();
std::unique_ptr<BootManager> SmartLED::bootmanager;
std::unique_ptr<DataManager, void(*)(DataManager*)> SmartLED::datamanager(nullptr, [](DataManager *p) {
    delete p;
});
std::unique_ptr<FontManager> SmartLED::fontmanager;
std::unique_ptr<MailManager> SmartLED::mailmanager;
std::unique_ptr<SerialportManager> SmartLED::serialportmanager;

void SmartLED::init() {
    SmartLED::datamanager.reset(new DataManager);
    SmartLED::bootmanager.reset(new BootManager(SmartLED::datamanager.get()));
    SmartLED::fontmanager.reset(new FontManager(SmartLED::datamanager.get()));
    SmartLED::mailmanager.reset(new MailManager(SmartLED::datamanager.get()));
    SmartLED::serialportmanager.reset(new SerialportManager(SmartLED::datamanager.get()));
}
