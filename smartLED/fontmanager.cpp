#include "fontmanager.h"
#include <QDebug>

FontManager::FontManager(DataManager *dm,QObject *parent)
    : QObject(parent),datamanager(dm) {
    QString path = QDir::currentPath() + "/ttf";
    qDebug() << "ttf root:" << path;
    ttf_root = new QDir(path);
    if(!ttf_root->exists()) {
        current_font = "Times New Roman";
        return;
    }

    foreach (QString ttf_name, ttf_root->entryList()) {
        if(ttf_name.toLower().endsWith("ttf") || ttf_name.toLower().endsWith("otf")) {
            int fontid = db.addApplicationFont(ttf_root->absoluteFilePath(ttf_name));
            if(fontid < -1)
                qDebug() << "load font error";
            else {
                QStringList fl = db.applicationFontFamilies(fontid);
                family_list.append(fl.at(0));
            }
        }
    }

    current_font = datamanager->ReadFontfamilyData().toString();
    if(current_font.isEmpty()) {
        if(!family_list.isEmpty())
            current_font = family_list.at(0);
        else
            current_font = "Times New Roman";
    }
}

FontManager::~FontManager() {
    datamanager->WriteFontfamilyData(current_font);
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
