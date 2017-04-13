#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#define CHECK_STRING    \
    if(str.isEmpty()) return false;  \
    if(str.length() == 1) \
        str.insert(0, '0');

#define CHECK_ERROR(var, errmsg)    \
    if(ok)  \
        (var)=QVariant(res); \
    else{   \
        handleError(errmsg);  \
        return; \
    }

#define SET_LL_DATA(widget, var, errmsg1, errmsg2)   \
    if(ui->widget->text().isEmpty()){ \
        handleError(errmsg1);   \
        return; \
    }   \
    else{   \
        if(checkLightSectionFormat(ui->widget->text()))    \
            (var)=QVariant(ui->widget->text());  \
        else{   \
            handleError(errmsg2);  \
            return; \
        }   \
    }

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    iniWriter = new QSettings("frame.ini",QSettings::IniFormat);
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(onButtonOKClicked(bool)));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->lineEdit_3, SIGNAL(textChanged(QString)), this, SLOT(onFrameHeaderChanged(QString)));
}

MainWindow::~MainWindow()
{
    delete iniWriter;
    delete ui;
}

void MainWindow::onFrameHeaderChanged(QString text) {
    ui->lineEdit_2->setText(QString::number(text.length()/2));
}

void MainWindow::onButtonOKClicked(bool) {
    bool ok;
    int res = ui->lineEdit_2->text().toInt(&ok);
    CHECK_ERROR(FrameheaderLen, tr("header frame length error"))

    res = ui->lineEdit_3->text().toInt(&ok, 16);
    CHECK_ERROR(FrameHeader, tr("header frame error"))

    res = ui->lineEdit_4->text().toInt(&ok);
    CHECK_ERROR(TempPos, tr("temp pos error"))

    res = ui->lineEdit_5->text().toInt(&ok);
    CHECK_ERROR(TempLen, tr("temp length error"))

    res = ui->lineEdit_6->text().toInt(&ok);
    CHECK_ERROR(HumiPos, tr("humi pos error"))

    res = ui->lineEdit_7->text().toInt(&ok);
    CHECK_ERROR(HumiLen, tr("humi length error"))

    res = ui->lineEdit_8->text().toInt(&ok);
    CHECK_ERROR(LightPos, tr("light pos error"))

    res = ui->lineEdit_9->text().toInt(&ok);
    CHECK_ERROR(LightLen, tr("light length error"))

    SET_LL_DATA(lineEdit_10, LL_High, tr("ll_h is empty"), tr("ll_h format error"))
    SET_LL_DATA(lineEdit_11, LL_HM, tr("ll_hm is empty"), tr("ll_hm format error"))
    SET_LL_DATA(lineEdit_12, LL_Medium, tr("ll_m is empty"), tr("ll_m format error"))
    SET_LL_DATA(lineEdit_13, LL_Low, tr("ll_l is empty"), tr("ll_l format error"))

    if(!getFrameLength()) {
        handleError(tr("get frame error"));
        return;
    }

    CFrameHeader = ui->lineEdit_14->text().toLower();
    if(CFrameHeader.toString().isEmpty()) {
        handleError(tr("cframe header error"));
        return;
    }

    if(!parseControlSection(ui->lineEdit_15->text())) {
        handleError(tr("cframe check error"));
        return;
    }

    if(!parseLevelSection(ui->lineEdit_16->text())) {
        handleError(tr("cframe ll error"));
        return;
    }

    int btn = QMessageBox::information(nullptr, tr("info"), tr("no error find,save config?"),
                             QMessageBox::Ok, QMessageBox::No);
    if(btn == (int)QMessageBox::Ok)
        saveConfig();
}

void MainWindow::handleError(const QString &msg) {
    QMessageBox::critical(nullptr, tr("error"), msg, QMessageBox::Ok);
}

bool MainWindow::checkLightSectionFormat(const QString &data) {
    int index = data.indexOf('|');
    if(index == -1) return false;
    bool ok;
    data.mid(0, index).toInt(&ok);
    if(!ok) return false;
    data.mid(index+1).toInt(&ok);
    if(!ok) return false;
    return true;
}

bool MainWindow::getFrameLength() {
    bool ok;
    int framelen = 0;

    int res = FrameheaderLen.toInt(&ok);
    if(ok) framelen += res;
    else return ok;

    res = TempLen.toInt(&ok);
    if(ok) framelen += res;
    else return ok;

    res = HumiLen.toInt(&ok);
    if(ok) framelen += res;
    else return ok;

    res = LightLen.toInt(&ok);
    if(ok) framelen += res;
    else return ok;

    ui->lineEdit->setText(QString::number(framelen));
    FrameLen = QVariant(framelen);
    return ok;
}

bool MainWindow::parseControlSection(const QString &data) {
    int index = data.indexOf(',');
    if(index == -1) return false;
    QString str;
    str = data.mid(0, index).toLower();
    CHECK_STRING
    CFrameCheck = str;
    str = data.mid(index+1).toLower();
    CHECK_STRING
    CFrameUnCheck = str;
    return true;
}

bool MainWindow::parseLevelSection(const QString &data) {
    int index = data.indexOf(',');
    if(index == -1) return false;

    QString str;
    str = data.mid(0, index).toLower();
    CHECK_STRING
    CFrameData_0 = str;

    QString _data = data.mid(index+1);
    index = _data.indexOf(',');
    if(index == -1) return false;
    str = _data.mid(0, index).toLower();
    CHECK_STRING
    CFrameData_1 = str;

    _data = _data.mid(index+1);
    index = _data.indexOf(',');
    if(index == -1) return false;
    str = _data.mid(0, index).toLower();
    CHECK_STRING
    CFrameData_2 = str;

    _data = _data.mid(index+1);
    index = _data.indexOf(',');
    if(index == -1) return false;
    str = _data.mid(0, index).toLower();
    CHECK_STRING
    CFrameData_3 = str;

    str = _data.mid(index+1);
    CHECK_STRING
    CFrameData_4 = str;

    return true;
}

void MainWindow::saveConfig() {
    iniWriter->setValue("DataFrame/FrameLen", FrameLen);
    iniWriter->setValue("DataFrame/FrameHeader", QString::number(FrameHeader.toInt(), 16));
    iniWriter->setValue("DataFrame/FrameHeaderLen", FrameheaderLen);
    iniWriter->setValue("DataFrame/FrameHumi", HumiPos);
    iniWriter->setValue("DataFrame/FrameHumiLen", HumiLen);
    iniWriter->setValue("DataFrame/FrameTemp", TempPos);
    iniWriter->setValue("DataFrame/FrameTempLen", TempLen);
    iniWriter->setValue("DataFrame/FrameLight", LightPos);
    iniWriter->setValue("DataFrame/FrameLightLen", LightLen);
    iniWriter->setValue("DataFrame/LightValue_H", LL_High);
    iniWriter->setValue("DataFrame/LightValue_MH", LL_HM);
    iniWriter->setValue("DataFrame/LightValue_M", LL_Medium);
    iniWriter->setValue("DataFrame/LightValue_L", LL_Low);
    iniWriter->setValue("ControlFrame/FrameHeader", CFrameHeader);
    iniWriter->setValue("ControlFrame/FrameCheck", CFrameCheck);
    iniWriter->setValue("ControlFrame/FrameUnCheck", CFrameUnCheck);
    iniWriter->setValue("ControlFrame/FrameBody_0", CFrameData_0);
    iniWriter->setValue("ControlFrame/FrameBody_1", CFrameData_1);
    iniWriter->setValue("ControlFrame/FrameBody_2", CFrameData_2);
    iniWriter->setValue("ControlFrame/FrameBody_3", CFrameData_3);
    iniWriter->setValue("ControlFrame/FrameBody_4", CFrameData_4);
}
