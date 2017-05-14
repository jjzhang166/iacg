#include "smartled.h"
#include <QProcess>

std::unique_ptr<Application> SmartLED::app;
std::unique_ptr<BootManager> SmartLED::bootmanager;
std::unique_ptr<FontManager> SmartLED::fontmanager;
std::unique_ptr<MailManager> SmartLED::mailmanager;
std::unique_ptr<SerialportManager> SmartLED::serialportmanager;
QSplashScreen *SmartLED::splash = nullptr;
QColor SmartLED::splash_color = Qt::black;
QString SmartLED::workpath;

void SmartLED::init() {
    QSettings reg_setting("HKEY_CURRENT_USER\\SOFTWARE\\SmartLED", QSettings::NativeFormat);
    SmartLED::workpath = reg_setting.value("WorkPath", "").toString();
    if(SmartLED::workpath.isEmpty()) {
        QMessageBox::critical(NULL, QObject::tr("error"),
                              QObject::tr("get working path failed"), QMessageBox::Yes);
        throw new QUnhandledException;
    }
    QDir rootdir(SmartLED::workpath);
    if(rootdir.exists("special_splash.png")) {
        SmartLED::splash = new QSplashScreen(QPixmap(SmartLED::workpath + "/special_splash.png"));
        SmartLED::splash_color = QColor(Qt::white);
    }
    else
        SmartLED::splash = rootdir.exists("splash.png")? new QSplashScreen(QPixmap(SmartLED::workpath + "/splash.png"))
                                            : new QSplashScreen(QPixmap(":/splash.png"));
    SmartLED::splash->show();
    SmartLED::splash->showMessage("program init...", Qt::AlignLeft, SmartLED::splash_color);
    if(!rootdir.exists("frame.ini")) {
        QMessageBox::StandardButton button = QMessageBox::information(NULL, QObject::tr("info"),
                    QObject::tr("file 'frame.ini' is not exist,do you want to create a new file or use default config."),
                    QMessageBox::Yes, QMessageBox::No);
        if(button == QMessageBox::Yes) {
            QProcess framecreator;
            framecreator.startDetached(SmartLED::workpath + "/framecreator.exe");
            throw new QUnhandledException;
        }
    }
    Frame::initFrame(SmartLED::workpath + "/frame.ini");
    SmartLED::bootmanager = std::make_unique<BootManager>(SmartLED::workpath + "/cfg.ini");
    SmartLED::fontmanager = std::make_unique<FontManager>(SmartLED::workpath + "/cfg.ini");
    SmartLED::mailmanager = std::make_unique<MailManager>(SmartLED::workpath + "/cfg.ini");
    SmartLED::serialportmanager = std::make_unique<SerialportManager>(SmartLED::workpath + "/cfg.ini");
    SmartLED::app = std::make_unique<Application>();
}
