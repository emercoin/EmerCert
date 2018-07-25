; Inno Setup Script.
; 1) build Visual Studio solution for 32 and 64 targets in release configuration
; 2) go to OpenSSL folder, and copy openssl.exe and *dll files to the x64/Release
; 3) go to Qt 64 folder, cd there and run windeployqt .../EmerCert.exe
; 4) use his script to generate installer
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "EmerCert"
#define MyAppVersion "0.6.3"
#define MyAppPublisher "Emercoin developers"
#define MyAppURL "https://emercoin.com/"
#define MyAppExeName "EmerCert.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{793D3FCE-2A7D-448A-8F30-9A72158974BD}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf64}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
LicenseFile="..\LICENSE.txt"
; InfoBeforeFile="intro.txt"
OutputDir="..\x64"
OutputBaseFilename=EmerCert {#MyAppVersion} setup 64bit
SetupIconFile="..\EmerCert\EmcCert.ico"
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"
Name: "armenian"; MessagesFile: "compiler:Languages\Armenian.islu"
Name: "brazilianportuguese"; MessagesFile: "compiler:Languages\BrazilianPortuguese.isl"
Name: "catalan"; MessagesFile: "compiler:Languages\Catalan.isl"
Name: "corsican"; MessagesFile: "compiler:Languages\Corsican.isl"
Name: "czech"; MessagesFile: "compiler:Languages\Czech.isl"
Name: "danish"; MessagesFile: "compiler:Languages\Danish.isl"
Name: "dutch"; MessagesFile: "compiler:Languages\Dutch.isl"
Name: "finnish"; MessagesFile: "compiler:Languages\Finnish.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"
Name: "german"; MessagesFile: "compiler:Languages\German.isl"
Name: "greek"; MessagesFile: "compiler:Languages\Greek.isl"
Name: "hebrew"; MessagesFile: "compiler:Languages\Hebrew.isl"
Name: "hungarian"; MessagesFile: "compiler:Languages\Hungarian.isl"
Name: "italian"; MessagesFile: "compiler:Languages\Italian.isl"
Name: "japanese"; MessagesFile: "compiler:Languages\Japanese.isl"
Name: "nepali"; MessagesFile: "compiler:Languages\Nepali.islu"
Name: "norwegian"; MessagesFile: "compiler:Languages\Norwegian.isl"
Name: "polish"; MessagesFile: "compiler:Languages\Polish.isl"
Name: "portuguese"; MessagesFile: "compiler:Languages\Portuguese.isl"
Name: "scottishgaelic"; MessagesFile: "compiler:Languages\ScottishGaelic.isl"
Name: "serbiancyrillic"; MessagesFile: "compiler:Languages\SerbianCyrillic.isl"
Name: "serbianlatin"; MessagesFile: "compiler:Languages\SerbianLatin.isl"
Name: "slovenian"; MessagesFile: "compiler:Languages\Slovenian.isl"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"
Name: "turkish"; MessagesFile: "compiler:Languages\Turkish.isl"
Name: "ukrainian"; MessagesFile: "compiler:Languages\Ukrainian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\x64\Release\EmerCert.exe"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files
Source: "..\x64\Release\libssl-1_1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\x64\Release\libcrypto-1_1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\x64\Release\vcruntime140.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\x64\Release\D3Dcompiler_47.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\x64\Release\libEGL.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\x64\Release\libGLESV2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\x64\Release\opengl32sw.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\x64\Release\openssl.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\x64\Release\gzip.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\x64\Release\Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\x64\Release\Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\x64\Release\Qt5Svg.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\x64\Release\Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\x64\Release\msvcp140.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\Windows\openssl.cfg"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\x64\Release\iconengines\qsvgicon.dll"; DestDir: "{app}\iconengines"; Flags: ignoreversion
Source: "..\x64\Release\imageformats\qgif.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "..\x64\Release\imageformats\qicns.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "..\x64\Release\imageformats\qico.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "..\x64\Release\imageformats\qjpeg.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "..\x64\Release\imageformats\qsvg.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "..\x64\Release\imageformats\qtga.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "..\x64\Release\imageformats\qtiff.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "..\x64\Release\imageformats\qwbmp.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "..\x64\Release\imageformats\qwebp.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "..\x64\Release\platforms\qwindows.dll"; DestDir: "{app}\platforms"; Flags: ignoreversion
Source: "..\x64\Release\styles\qwindowsvistastyle.dll"; DestDir: "{app}\styles"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_ar.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_bg.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_ca.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_cs.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_da.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_de.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_en.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_es.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_fi.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_fr.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_gd.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_he.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_hu.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_it.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_ja.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_ko.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_lv.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_pl.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_ru.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_sk.qm"; DestDir: "{app}\translations"; Flags: ignoreversion
Source: "..\x64\Release\translations\qt_uk.qm"; DestDir: "{app}\translations"; Flags: ignoreversion

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[Dirs]
Name: "{app}\iconengines"
Name: "{app}\imageformats"
Name: "{app}\platforms"
Name: "{app}\styles"
Name: "{app}\translations"
