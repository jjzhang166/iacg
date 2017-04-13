#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QVariant>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onButtonOKClicked(bool);
    void onFrameHeaderChanged(QString);

private:
    void handleError(const QString &msg);
    void saveConfig();
    bool getFrameLength();
    bool checkLightSectionFormat(const QString &data);
    bool parseControlSection(const QString &data);
    bool parseLevelSection(const QString &data);

private:
    Ui::MainWindow *ui;
    QSettings *iniWriter;

private:
    QVariant FrameLen;
    QVariant FrameHeader;
    QVariant FrameheaderLen;
    QVariant TempPos;
    QVariant TempLen;
    QVariant HumiPos;
    QVariant HumiLen;
    QVariant LightPos;
    QVariant LightLen;
    QVariant LL_High;
    QVariant LL_HM;
    QVariant LL_Medium;
    QVariant LL_Low;

    QVariant CFrameHeader;
    QVariant CFrameCheck;
    QVariant CFrameUnCheck;
    QVariant CFrameData_0;
    QVariant CFrameData_1;
    QVariant CFrameData_2;
    QVariant CFrameData_3;
    QVariant CFrameData_4;
};

#endif // MAINWINDOW_H
