[CmdletBinding()]
param(
    [Parameter(Mandatory)][ValidateSet('SC03','SC22','SC04','SC23','SC05','SC20','SC21','SC24','SC25','SC26')][string]$Scenario,
    [ValidateSet('single','session')][string]$Request='single',
    [string]$Message='all',
    [ValidateRange(1,1000)][int]$Sessions=1,
    [string]$ConfigurationFile,
    [string]$LogFile
)
$ErrorActionPreference='Stop'
$profiles=@{
    SC26=@('centerClient2signalserver_v2','signalserver','signal')
    SC20=@('vehicleServer2rse_v2','rse','bsm')
    SC21=@('vehicleClient2rse_v2','rse','traffic')
    SC24=@('rseClient2vehicle_v2','vehicle','bsm')
    SC25=@('rseServer2vehicle_v2','vehicle','traffic')
    SC03=@('vehicleServer2center_v2','center','bsm')
    SC22=@('centerClient2vehicle_v2','vehicle','bsm')
    SC04=@('vehicleClient2center_v2','center','traffic')
    SC23=@('centerServer2vehicle_v2','vehicle','traffic')
    SC05=@('signalserverServer2center_v2','center','signal')
}
$selected=$profiles[$Scenario]
$workspace=[IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$exe=Join-Path $PSScriptRoot '..\project\vs2022\Debug64\DatexBsmEmulator.exe'
if(-not(Test-Path -LiteralPath $exe)){throw 'Build DatexBsmEmulator.vcxproj (Debug|x64) first.'}
if(-not $ConfigurationFile){$ConfigurationFile=Join-Path $PSScriptRoot ($selected[0]+'.sut.json')}
if(-not $LogFile){$LogFile=Join-Path $workspace ('.local\datex-sut-evidence\'+(Get-Date -Format 'yyyyMMdd-HHmmss-ffff')+'-'+$Scenario+'.jsonl')}
Write-Output ('Scenario: '+$Scenario+' / '+$selected[0])
Write-Output ('Evidence: '+[IO.Path]::GetFullPath($LogFile))
& $exe --case $selected[0] --role $selected[1] --profile $selected[2] --mode emulator --request $Request --message $Message --sessions $Sessions --duration 1800 --config ([IO.Path]::GetFullPath($ConfigurationFile)) --log ([IO.Path]::GetFullPath($LogFile))
exit $LASTEXITCODE
