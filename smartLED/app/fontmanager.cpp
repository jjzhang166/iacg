#include "fontmanager.h"
#include "smartled.h"
#include <QDebug>

FontManager::FontManager(QObject *parent)
    : QObject(parent),
    ttf_root(SmartLED::workpath + "/ttf"),
    ini_setting("cfg.ini", QSettings::IniFormat) {

    if(!ttf_root.exists())
        throw new QUnhandledException;

    //load custom font
    foreach (QString ttf_name, ttf_root.entryList()) {
        if(ttf_name.toLower().endsWith("ttf") || ttf_name.toLower().endsWith("otf")) {
            int fontid = db.addApplicationFont(ttf_root.absoluteFilePath(ttf_name));
            if(fontid < -1)
                qDebug() << "load font error";
            else {
                QStringList fl = db.applicationFontFamilies(fontid);
                family_list.append(fl.at(0));
            }
        }
    }

    current_font = ini_setting.value("Font/FontFamily", "").toString();
    if(current_font.isEmpty()) {
        if(!family_list.isEmpty())
            current_font = family_list.at(0);
        else
            throw new QUnhandledException;
    }
}

FontManager::~FontManager() {
    qDebug() << "destroy fontmanager";
    ini_setting.setValue("Font/FontFamily", current_font);
}

QStringList FontManager::familylist() const {
    return this->family_list;
}

QString FontManager::curfont() const {
    return this->current_font;
}

void FontManager::setCurfont(const QString &f) {
    this->current_font = f;
    emit curfontChanged();
}

bool FontManager::isListempty() {
    return this->family_list.isEmpty();
}
