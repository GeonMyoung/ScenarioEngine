[CmdletBinding()]
param(
    [Parameter(Mandatory)][ValidateSet('Center','Rse')][string]$Role,
    [string]$ConfigurationFile,
    [string]$LogFile,
    [ValidateSet('single','session')][string]$Request='single',
    [ValidateSet('all','map','rsa','tim')][string]$Message='all',
    [ValidateRange(1,1000)][int]$Sessions=1,
    [ValidateRange(1,86400)][int]$DurationSeconds=1200,
    [ValidateSet('none','wrong-reject','changed-retry','bad-content','after-cancel','slow-period')]
    [string]$Fault='none'
)
$ErrorActionPreference='Stop'
$workspace=[IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$emulator=Join-Path $PSScriptRoot '..\project\vs2022\Debug64\DatexBsmEmulator.exe'
if(-not(Test-Path -LiteralPath $emulator)){throw 'Build DatexBsmEmulator.vcxproj (Debug|x64) first.'}
if(-not $ConfigurationFile){$ConfigurationFile=Join-Path $PSScriptRoot ('traffic-'+$Role.ToLowerInvariant()+'-sut.example.json')}
if(-not $LogFile){$LogFile=Join-Path $workspace ('.local\traffic-sut-evidence\'+(Get-Date -Format 'yyyyMMdd-HHmmss-ffff')+'-'+$Role.ToLowerInvariant()+'.jsonl')}
$ConfigurationFile=[IO.Path]::GetFullPath($ConfigurationFile)
$LogFile=[IO.Path]::GetFullPath($LogFile)
Write-Output ('Traffic SUT role: '+$Role+'; message: '+$Message)
Write-Output ('Evidence: '+$LogFile)
& $emulator --profile traffic --mode emulator --role $Role.ToLowerInvariant() --message $Message --config $ConfigurationFile --log $LogFile --request $Request --sessions $Sessions --duration $DurationSeconds --fault $Fault
exit $LASTEXITCODE
