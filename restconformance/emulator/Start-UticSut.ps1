[CmdletBinding()]
param(
    [string]$ConfigurationFile,
    [string]$OutputDirectory,
    [string]$PythonExecutable='python'
)
$ErrorActionPreference='Stop'
$workspace=[IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
if(-not $ConfigurationFile){$ConfigurationFile=Join-Path $PSScriptRoot 'center-sut.example.json'}
if(-not $OutputDirectory){$OutputDirectory=Join-Path $workspace ('.local\utic-sut-evidence\'+(Get-Date -Format 'yyyyMMdd-HHmmss-ffff'))}
Write-Output ('UT center processing evidence: '+[IO.Path]::GetFullPath($OutputDirectory))
& $PythonExecutable -X utf8 (Join-Path $PSScriptRoot 'ut_center_utic.py') --config ([IO.Path]::GetFullPath($ConfigurationFile)) --output ([IO.Path]::GetFullPath($OutputDirectory))
exit $LASTEXITCODE
