;--------------------------------
; Including required extensions

  !include x64.nsh

;--------------------------------
; Custom defines
Section 
  SetShellVarContext current
SectionEnd
	
	SilentInstall silent
	!define NAME "MediaKeys"
	!define APPFILE "MediaKeys.exe"
	
	Name "${NAME}"
	OutFile "MediaKeysSetup.exe"
	InstallDir "$APPDATA\EscapeApps\${Name}"
	InstallDirRegKey HKCU "Software\EscapeApps\${NAME}" $INSTDIR
	RequestExecutionLevel user

Function LaunchAndQuit
	Exec "$INSTDIR\MediaKeys.exe"
	Quit
FunctionEnd

Section "Uninstall"
	Delete $INSTDIR\uninstaller.exe
	RMDir $INSTDIR
SectionEnd

Section "Install"
	InitPluginsDir
	SetOutPath $INSTDIR
	FILE MediaKeys.exe
	WriteUninstaller $INSTDIR\uninstaller.exe

SectionEnd

Section "StartMenu Shortcut" StartShort
  CreateShortCut "$SMPROGRAMS\Startup\MediaKeys.lnk" "$INSTDIR\MediaKeys.exe" \
  "" "$INSTDIR\MediaKeys.exe" 2 SW_SHOWNORMAL \
  ALT|CTRL|SHIFT|F5 "MediaKeys Start menu shortcut"
SectionEnd

Section "Launch and quit"
	Call LaunchAndQuit
SectionEnd




