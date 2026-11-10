[CmdletBinding()]
param([int]$Port=55311,[string]$OutputDirectory)
$ErrorActionPreference='Stop'
$vdsWorkspace=[IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
if(-not $OutputDirectory){$OutputDirectory=Join-Path $vdsWorkspace ('.local\vds-sut\'+(Get-Date -Format 'yyyyMMdd-HHmmss-ffff'))}
& python -X utf8 (Join-Path $PSScriptRoot 'ut_center_vds.py') --port $Port --output $OutputDirectory
exit $LASTEXITCODE
