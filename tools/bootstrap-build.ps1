[CmdletBinding()]
param(
    [ValidateSet('Debug','Release')][string]$Configuration = 'Debug',
    [ValidateSet('Engine','Emulators','All','Tools')][string]$Target = 'All',
    [switch]$Rebuild
)
$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$workspaceRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
& (Join-Path $PSScriptRoot 'setup-sdk-dependencies.ps1')
$vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
if (-not (Test-Path -LiteralPath $vswhere)) { throw 'Install Visual Studio 2022 with the C++ Desktop workload (.vsconfig).' }
$msbuild = @(& $vswhere -latest -version '[17.0,18.0)' -products '*' -requires Microsoft.Component.MSBuild -find 'MSBuild\Current\Bin\MSBuild.exe') | Select-Object -First 1
if ([string]::IsNullOrWhiteSpace($msbuild)) { throw 'Visual Studio 2022 MSBuild was not found.' }
$projects = @()
if ($Target -in @('Engine','All')) {
    $projects += 'scenarioengine\project\vs2022\ScenarioEngineTest.vcxproj'
}
if ($Target -in @('Emulators','All')) {
    $projects += @(
        'GitsnDsrcEmulator\project\vs2022\GitsnDsrcEmulatorTest.vcxproj',
        'Itsk00126v1Emulator\project\vs2022\Itsk00126v1EmulatorTest.vcxproj',
        'ITSK00144_2Emulator\project\vs2022\ITSK00144_2EmulatorTest.vcxproj'
    )
}
if ($Target -eq 'Tools') {
    $projects += @(
        'dimz\dz1_tools\dz1_tdc\project\vs2022\dz1_tdc.vcxproj',
        'dimz\dz1_tools\dz1_json\project\vs2022\dz1_json_compiler.vcxproj'
    )
}
$logRoot = Join-Path $workspaceRoot ('.local\build-logs\' + (Get-Date -Format 'yyyyMMdd-HHmmss'))
New-Item -ItemType Directory -Path $logRoot -Force | Out-Null
$action = if ($Rebuild) { 'Rebuild' } else { 'Build' }
foreach ($relative in $projects) {
    $project = Join-Path $workspaceRoot $relative
    if (-not (Test-Path -LiteralPath $project)) { throw "Build project missing: $relative" }
    $name = [IO.Path]::GetFileNameWithoutExtension($project)
    $log = Join-Path $logRoot ($name + '.log')
    Write-Host "Building $name ($Configuration|x64)"
    $arguments = @($project, "/t:$action", "/p:Configuration=$Configuration", '/p:Platform=x64', '/p:VcpkgEnabled=false', '/m:4', '/nr:false', '/nologo', '/v:quiet', '/clp:ErrorsOnly;Summary', "/flp:logfile=$log;verbosity=normal")
    & $msbuild @arguments
    if ($LASTEXITCODE -ne 0) { throw "Build failed: $name. Log: $log" }
}
Write-Host "Build complete ($Target, $Configuration|x64). Logs: $logRoot"
