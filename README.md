#smartLED
##日志
- 2016/12/30 完成"BugReport.exe"程序
- 2016/12/31 更新上位机部分UI
- 2017/1/1   更新上位机部分UI，串口连接部分程序
- 2017/1/3   更新上位机部分UI，QML控件定制(combobox,button,tabview)
- 2017/1/5   完成STC52和上位机的数据搜集模块，更新上位机部分UI
- 2017/1/6   上位机模块UI更新，QML控件定制(gauge)
- 2017/1/7   上位机模块UI更新，QML控件定制（checkbox）
- 2017/1/7   完成上位机通过串口控制STC52的部分，完成STC52控制光照强度的部分，完成上位机文本的国际化
- 2017/1/7   上位机版本1.0完成

##项目描述
###1. 为什么写？
    临近大学毕业，毕业设计自然是不可缺少的╮(╯_╰)╭。我的毕设题目为“智能LED补光灯控制系统”，因此我就想要设计这样一个上位机：可以将单片机搜集到的信息以图形的方式展现在用户面前，并且用户可以通过该上位机来控制单片机是否进行自动光强的调整。于是乎，这个项目就这样产生了。
###2. 如何使用？
    smartLED是一个简单用的图形化上位机程序。程序使用QML编写，可以将从单片机搜集来的光强，湿度，温度数据通过串口以图形化的方式显示。即使不使用已有的单片机程序，只要你发送的字节序列符合相应的格式（你也可以通过修改程序源码进行格式定制）就可以轻松的和本程序进行通信。
    smartLED不仅提供程序的全部源代码，如果你使用的是MS Windows操作系统，它还提供编译好的二进制安装包，你可以直接获取它并且轻而易举的安装到你的系统上。