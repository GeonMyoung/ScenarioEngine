[CmdletBinding()]
param([string]$Config,[string]$OutputDirectory)
$ErrorActionPreference='Stop'
$microWorkspace=[IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
if(-not $Config){$Config=Join-Path $PSScriptRoot 'micro-vds-sut.example.json'}
if(-not $OutputDirectory){$OutputDirectory=Join-Path $microWorkspace ('.local\micro-vds-sut\'+(Get-Date -Format 'yyyyMMdd-HHmmss-ffff'))}
& python -X utf8 (Join-Path $PSScriptRoot 'micro_vds_client.py') --config $Config --output $OutputDirectory
exit $LASTEXITCODE
