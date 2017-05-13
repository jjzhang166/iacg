; �ýű�ʹ�� HM VNISEdit �ű��༭���򵼲���

; ��װ�����ʼ���峣��
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

; ------ MUI �ִ����涨�� (1.67 �汾���ϼ���) ------
!include "MUI.nsh"

; MUI Ԥ���峣��
!define MUI_ABORTWARNING
!define MUI_ICON "${PRODUCT_ICON_PATH}"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; ��ӭҳ��
!insertmacro MUI_PAGE_WELCOME
; ���Э��ҳ��
!insertmacro MUI_PAGE_LICENSE "${PRODUCT_LICENSE_PATH}"
; ���ѡ��ҳ��
!insertmacro MUI_PAGE_COMPONENTS
; ��װĿ¼ѡ��ҳ��
!insertmacro MUI_PAGE_DIRECTORY
; ��ʼ�˵�����ҳ��
var ICONS_GROUP
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "smartLED"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${PRODUCT_STARTMENU_REGVAL}"
!insertmacro MUI_PAGE_STARTMENU Application $ICONS_GROUP
; ��װ����ҳ��
!insertmacro MUI_PAGE_INSTFILES
; ��װ���ҳ��
!define MUI_FINISHPAGE_SHOWREADME_TEXT "��ʾ��л��Ϣ"
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\Thanks.txt"
!define MUI_FINISHPAGE_RUN_TEXT "������Ŀ��վ"
!define MUI_FINISHPAGE_RUN "C:\Program Files (x86)\Internet Explorer\iexplore.exe"
!define MUI_FINISHPAGE_RUN_PARAMETERS "${PRODUCT_WEB_SITE}"
!insertmacro MUI_PAGE_FINISH

; ��װж�ع���ҳ��
!insertmacro MUI_UNPAGE_INSTFILES

; ��װ�����������������
!insertmacro MUI_LANGUAGE "SimpChinese"

; ��װԤ�ͷ��ļ�
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI �ִ����涨����� ------

ReserveFile "${NSISDIR}\Plugins\system.dll"
ReserveFile "F:\cloudmusic\��݆ѧ - Old Memory.mp3"

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "sl.exe"
InstallDir "$PROGRAMFILES\smartLED"
ShowInstDetails show
ShowUnInstDetails show
BGGradient 0000FF 000000 FFFFFF

Section "������(����)" SEC01
	SectionIn RO
  SetOutPath "$INSTDIR\bin"
  SetOverwrite ifnewer
  File /r "${BIN_PATH}"
  SetOutPath "$INSTDIR"
  File "${THANKS_PATH}"
; ������ʼ�˵���ݷ�ʽ
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  !insertmacro MUI_STARTMENU_WRITE_END
  CreateShortCut "$DESKTOP\smartLED.lnk" "$INSTDIR\bin\smartLED.exe"
SectionEnd

Section "Դ����" SEC02
  SetOutPath "$INSTDIR\src\smartLED"
  File /r "${SOURCE_PATH1}"
  SetOutPath "$INSTDIR\src\stc89c52rc"
  File /r "${SOURCE_PATH2}"
  SetOutPath "$INSTDIR"
  File "${THANKS_PATH}"
; ������ʼ�˵���ݷ�ʽ
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

#-- ���� NSIS �ű��༭�������� Function ���α�������� Section ����֮���д���Ա��ⰲװ�������δ��Ԥ֪�����⡣--#

; �����������
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC01} "��λ���Ŀ�ִ�г���"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC02} "������λ���͵�Ƭ���ĳ���Դ����"
!insertmacro MUI_FUNCTION_DESCRIPTION_END

Function .onInit
  InitPluginsDir
  File "/oname=$PLUGINSDIR\bgm_��݆ѧ_-_Old_Memory.mp3" "F:\cloudmusic\��݆ѧ - Old Memory.mp3"
  ; �������ļ�
  System::Call "winmm.dll::mciSendString(t 'OPEN $PLUGINSDIR\bgm_��݆ѧ_-_Old_Memory.mp3 TYPE MPEGVIDEO ALIAS BGMUSIC', t .r0, i 130, i 0)"
  ; ��ʼ���������ļ�
  System::Call "winmm.dll::mciSendString(t 'PLAY BGMUSIC NOTIFY', t .r0, i 130, i 0)"
FunctionEnd

Function .onGUIEnd
  ; ֹͣ���������ļ�
  System::Call "winmm.dll::mciSendString(t 'STOP BGMUSIC',t .r0,i 130,i 0)"
  ; �ر������ļ�
  System::Call "winmm.dll::mciSendString(t 'CLOSE BGMUSIC',t .r0,i 130,i 0)"
FunctionEnd

/******************************
 *  �����ǰ�װ�����ж�ز���  *
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

#-- ���� NSIS �ű��༭�������� Function ���α�������� Section ����֮���д���Ա��ⰲװ�������δ��Ԥ֪�����⡣--#

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "��ȷʵҪ��ȫ�Ƴ� smartLED ���������е������" IDYES +2
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "smartLED �ѳɹ��ش����ļ�����Ƴ���"
FunctionEnd
