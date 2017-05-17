#smartLED
##最新更新
- 2017.5.17 添加声音自动报警功能
- 2017.5.15 添加当窗口边框无法正常显示时的补救功能
- 2017.5.11 代码优化，添加串口自动查询功能
- 2017.5.10 代码优化
- 2017.4.13 添加了帧配置文件的图形界面，方便程序应用到其他场景
- 2017.4.9 添加了控制帧配置文件的支持，扩大程序应用范围
- 2017.4.8 添加了数据帧配置文件的支持，扩大程序应用范围
- 2017.4.6 添加了启动splash画面,可选启动功能的支持
- 2017.4.3 添加了配置文件的支持
- 2017.4.2 添加了自定义的字体支持
- 增加了SMTP客户端，温度湿度在高于某个阈值时可以给指定邮箱发送邮件
- SLComponent增加了部分QML的定制控件

##日志
- 2017/1/7   上位机版本1.0完成
- 2017/1/7   完成上位机通过串口控制STC52的部分，完成STC52控制光照强度的部分，完成上位机文本的国际化
- 2017/1/7   上位机模块UI更新，QML控件定制（checkbox）
- 2017/1/6   上位机模块UI更新，QML控件定制(gauge)
- 2017/1/5   完成STC52和上位机的数据搜集模块，更新上位机部分UI
- 2017/1/3   更新上位机部分UI，QML控件定制(combobox,button,tabview)
- 2017/1/1   更新上位机部分UI，串口连接部分程序
- 2016/12/31 更新上位机部分UI

##描述
- SlaveDataCollection文件夹内为上位机对应单片机的程序，硬件电路根据程序及注释自行焊接即可
- SLComponent文件夹内为所有上位机用到的控件，在使用时加上```import SLComponent 1.0```导入相关控件即可
- 上位机在windows和linux下测试均可以正常运行，串口有时可能需要安装相应驱动，在网上自行下载安装即可
- 本项目为作者毕设上位机及单片机的源码部分，上位机在搜集数据及控制方面能力有限

##FAQ
1. Linux下已经安装了相应驱动，为什么还是无法打开串口？ 
Linux下打开串口需要su权限，终端使用sudo启动相应程序即可正常打开串口