param([Parameter(Mandatory)][string]$OutputDirectory)
$ErrorActionPreference='Stop'
$compiler=Join-Path $env:WINDIR 'Microsoft.NET\Framework64\v4.0.30319\csc.exe'
New-Item -ItemType Directory -Force -Path $OutputDirectory | Out-Null
$output=Join-Path ([IO.Path]::GetFullPath($OutputDirectory)) '시작하기.exe'
& $compiler /nologo /target:winexe /platform:x64 /optimize+ /r:System.Web.Extensions.dll /r:System.Windows.Forms.dll /r:System.Drawing.dll "/out:$output" (Join-Path $PSScriptRoot '..\..\interfaceconformance\launcher\WebFormLink.cs') (Join-Path $PSScriptRoot '..\..\interfaceconformance\launcher\PortReservation.cs') (Join-Path $PSScriptRoot 'QuickCore.cs') (Join-Path $PSScriptRoot 'SessionRunner.cs') (Join-Path $PSScriptRoot 'SettingsPanel.cs') (Join-Path $PSScriptRoot 'QuickForm.cs') (Join-Path $PSScriptRoot 'MessageArchive.cs') (Join-Path $PSScriptRoot 'MessageViewer.cs') (Join-Path $PSScriptRoot '..\..\interfaceconformance\launcher\UserReport.cs') (Join-Path $PSScriptRoot 'Program.cs')
if($LASTEXITCODE -ne 0){throw 'Launcher compilation failed'}
Write-Output $output
