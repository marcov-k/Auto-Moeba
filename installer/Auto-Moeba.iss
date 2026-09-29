#define AppName "Auto-Moeba"
#define Publisher "Marco Vasko"
#define ExecutableName "Auto-Moeba.exe"

[Setup]
AppId={{224d502989f44fc8aa7aa6b6610ebaf5}}
AppName={#AppName}
AppVersion={#AppVersion}
AppPublisher={#Publisher}

DefaultDirName={autopf}\{#AppName}
DefaultGroupName={#AppName}

OutputDir=output
OutputBaseFileName=Auto-Moeba-v{#AppVersion}

ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible

PrivilegesRequired=admin

Compression=lzma
SolidCompression=yes

WizardStyle=modern

UninstallDisplayName={#AppName}
UninstallDisplayIcon={app}\{#ExecutableName}

[Files]
Source: "{#BuildDir}\*"; DestDir: "{app}"; Flags: recursesubdirs createallsubdirs ignoreversion

[Icons]
Name: "{autoprograms}\{#AppName}"; Filename: "{app}\{#ExecutableName}"; WorkingDir: "{app}"
Name: "{autodesktop}\{#AppName}"; Filename: "{app}\{#ExecutableName}"; WorkingDir: "{app}"

[Run]
Filename: "{app}\{#ExecutableName}"; WorkingDir: "{app}"; Description: "Launch {#AppName}"; Flags: nowait postinstall skipifsilent
