[CmdletBinding()]
param(
    [Parameter(Mandatory)][ValidateSet('Rse','Center')][string]$Role,
    [string]$ConfigurationFile,
    [string]$LogFile,
    [ValidateSet('single','session')][string]$Request = 'single',
    [ValidateRange(1,1000)][int]$Sessions = 1,
    [ValidateRange(1,86400)][int]$DurationSeconds = 600,
    [ValidateSet('none','wrong-reject','changed-retry','bad-content','after-cancel','slow-period')]
    [string]$Fault = 'none'
)
$ErrorActionPreference = 'Stop'
$taskWorkspace = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$emulatorExe = Join-Path $PSScriptRoot '..\project\vs2022\Debug64\DatexBsmEmulator.exe'
if (-not (Test-Path -LiteralPath $emulatorExe)) {
    throw 'Build datexconformance/project/vs2022/DatexBsmEmulator.vcxproj (Debug|x64) first.'
}
if (-not $ConfigurationFile) {
    $ConfigurationFile = Join-Path $PSScriptRoot ($Role.ToLowerInvariant() + '-sut.example.json')
}
if (-not $LogFile) {
    $runName = (Get-Date -Format 'yyyyMMdd-HHmmss-ffff') + '-' + $Role.ToLowerInvariant() + '.jsonl'
    $LogFile = Join-Path $taskWorkspace ('.local\bsm-sut-evidence\' + $runName)
}
$ConfigurationFile = [IO.Path]::GetFullPath($ConfigurationFile)
$LogFile = [IO.Path]::GetFullPath($LogFile)
Write-Output ('Emulator SUT role: ' + $Role)
Write-Output ('Evidence: ' + $LogFile)
& $emulatorExe --mode emulator --role $Role.ToLowerInvariant() --config $ConfigurationFile --log $LogFile --request $Request --sessions $Sessions --duration $DurationSeconds --fault $Fault
exit $LASTEXITCODE
