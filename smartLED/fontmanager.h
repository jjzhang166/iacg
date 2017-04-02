#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <QObject>
#include <QDir>
#include <QFontDatabase>

class FontManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList familylist READ familylist)
    Q_PROPERTY(QString curfont READ curfont WRITE setCurfont NOTIFY curfontChanged)

signals:
    void curfontChanged();

public:
    explicit FontManager(QObject *parent = 0);

public:
    QStringList familylist() const;
    QString curfont() const;
    void setCurfont(const QString &f);

    Q_INVOKABLE bool isListempty();

private:
    QFontDatabase db;
    QStringList family_list;
    QDir *ttf_root;
    QString current_font;
};

#endif // FONTMANAGER_H
