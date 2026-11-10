[CmdletBinding()]
param([int]$Port=55328,[string]$OutputDirectory,[string]$Fixture)
$ErrorActionPreference='Stop'
$uticWorkspace=[IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
if(-not $OutputDirectory){$OutputDirectory=Join-Path $uticWorkspace ('.local\utic-provider-sut\'+(Get-Date -Format 'yyyyMMdd-HHmmss-ffff'))}
$uticArgs=@('-X','utf8',(Join-Path $PSScriptRoot 'utic_provider.py'),'--port',$Port,'--output',$OutputDirectory)
if($Fixture){$uticArgs+=@('--fixture',$Fixture)}
& python @uticArgs
exit $LASTEXITCODE
