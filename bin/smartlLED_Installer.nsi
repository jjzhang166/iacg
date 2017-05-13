; 该脚本使用 HM VNISEdit 脚本编辑器向导产生

; 安装程序初始定义常量
!define PRODUCT_NAME "smartLED"
!define PRODUCT_VERSION "1.7"
!define PRODUCT_PUBLISHER "nxlgdjk"
!define PRODUCT_WEB_SITE "https://git.oschina.net/linuxlike/iacg"
!define PRODUCT_INSTALL_KEY "Software\${PRODUCT_NAME}"
!define PRODUCT_INSTALL_ROOT_KEY "HKCU"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_STARTMENU_REGVAL "NSIS:StartMenuDir"
!define PRODUCT_ICON_PATH "E:\iacg\smartLED\sl.ico"
!define PRODUCT_LICENSE_PATH "E:\iacg\LICENSE"

!define BIN_PATH "E:\iacg\bin\smartLED\*.*"
!define SOURCE_PATH1 "E:\iacg\smartLED\*.*"
!define SOURCE_PATH2 "E:\iacg\SlaveDataCollection\*.*"
!define THANKS_PATH "E:\iacg\Thanks.txt"

SetCompressor lzma

; ------ MUI 现代界面定义 (1.67 版本以上兼容) ------
!include "MUI.nsh"

; MUI 预定义常量
!define MUI_ABORTWARNING
!define MUI_ICON "${PRODUCT_ICON_PATH}"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; 欢迎页面
!insertmacro MUI_PAGE_WELCOME
; 许可协议页面
!insertmacro MUI_PAGE_LICENSE "${PRODUCT_LICENSE_PATH}"
; 组件选择页面
!insertmacro MUI_PAGE_COMPONENTS
; 安装目录选择页面
!insertmacro MUI_PAGE_DIRECTORY
; 开始菜单设置页面
var ICONS_GROUP
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "smartLED"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${PRODUCT_STARTMENU_REGVAL}"
!insertmacro MUI_PAGE_STARTMENU Application $ICONS_GROUP
; 安装过程页面
!insertmacro MUI_PAGE_INSTFILES
; 安装完成页面
!define MUI_FINISHPAGE_SHOWREADME_TEXT "显示致谢信息"
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\Thanks.txt"
!define MUI_FINISHPAGE_RUN_TEXT "访问项目网站"
!define MUI_FINISHPAGE_RUN "C:\Program Files (x86)\Internet Explorer\iexplore.exe"
!define MUI_FINISHPAGE_RUN_PARAMETERS "${PRODUCT_WEB_SITE}"
!insertmacro MUI_PAGE_FINISH

; 安装卸载过程页面
!insertmacro MUI_UNPAGE_INSTFILES

; 安装界面包含的语言设置
!insertmacro MUI_LANGUAGE "SimpChinese"

; 安装预释放文件
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI 现代界面定义结束 ------

ReserveFile "${NSISDIR}\Plugins\system.dll"
ReserveFile "F:\cloudmusic\三輪学 - Old Memory.mp3"

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "sl.exe"
InstallDir "$PROGRAMFILES\smartLED"
ShowInstDetails show
ShowUnInstDetails show
BGGradient 0000FF 000000 FFFFFF

Section "主程序(必须)" SEC01
	SectionIn RO
  SetOutPath "$INSTDIR\bin"
  SetOverwrite ifnewer
  File /r "${BIN_PATH}"
  SetOutPath "$INSTDIR"
  File "${THANKS_PATH}"
; 创建开始菜单快捷方式
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  !insertmacro MUI_STARTMENU_WRITE_END
  CreateShortCut "$DESKTOP\smartLED.lnk" "$INSTDIR\bin\smartLED.exe"
SectionEnd

Section "源代码" SEC02
  SetOutPath "$INSTDIR\src\smartLED"
  File /r "${SOURCE_PATH1}"
  SetOutPath "$INSTDIR\src\stc89c52rc"
  File /r "${SOURCE_PATH2}"
  SetOutPath "$INSTDIR"
  File "${THANKS_PATH}"
; 创建开始菜单快捷方式
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
  WriteRegStr ${PRODUCT_INSTALL_ROOT_KEY} "${PRODUCT_INSTALL_KEY}" "WorkPath" "$INSTDIR\bin"
SectionEnd

#-- 根据 NSIS 脚本编辑规则，所有 Function 区段必须放置在 Section 区段之后编写，以避免安装程序出现未可预知的问题。--#

; 区段组件描述
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC01} "上位机的可执行程序"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC02} "包含上位机和单片机的程序源代码"
!insertmacro MUI_FUNCTION_DESCRIPTION_END

Function .onInit
  InitPluginsDir
  File "/oname=$PLUGINSDIR\bgm_三輪学_-_Old_Memory.mp3" "F:\cloudmusic\三輪学 - Old Memory.mp3"
  ; 打开音乐文件
  System::Call "winmm.dll::mciSendString(t 'OPEN $PLUGINSDIR\bgm_三輪学_-_Old_Memory.mp3 TYPE MPEGVIDEO ALIAS BGMUSIC', t .r0, i 130, i 0)"
  ; 开始播放音乐文件
  System::Call "winmm.dll::mciSendString(t 'PLAY BGMUSIC NOTIFY', t .r0, i 130, i 0)"
FunctionEnd

Function .onGUIEnd
  ; 停止播放音乐文件
  System::Call "winmm.dll::mciSendString(t 'STOP BGMUSIC',t .r0,i 130,i 0)"
  ; 关闭音乐文件
  System::Call "winmm.dll::mciSendString(t 'CLOSE BGMUSIC',t .r0,i 130,i 0)"
FunctionEnd

/******************************
 *  以下是安装程序的卸载部分  *
 ******************************/

Section Uninstall
  !insertmacro MUI_STARTMENU_GETFOLDER "Application" $ICONS_GROUP
  Delete "$INSTDIR\uninst.exe"
	Delete "$INSTDIR\Thanks.txt"
	Delete "$DESKTOP\smartLED.lnk"

  RMDir /r "$INSTDIR\src"
  RMDir /r "$INSTDIR\bin"

  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey ${PRODUCT_INSTALL_ROOT_KEY} "${PRODUCT_INSTALL_KEY}"
  SetAutoClose true
SectionEnd

#-- 根据 NSIS 脚本编辑规则，所有 Function 区段必须放置在 Section 区段之后编写，以避免安装程序出现未可预知的问题。--#

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "您确实要完全移除 smartLED ，及其所有的组件？" IDYES +2
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "smartLED 已成功地从您的计算机移除。"
FunctionEnd
