[CmdletBinding()]
param(
    [string]$Version = '1.2.2',
    [Parameter(Mandatory)][string]$OutputDirectory,
    [Parameter(Mandatory)][string]$PythonRuntime,
    [Parameter(Mandatory)][string]$MqttRuntime,
    [string]$StagingDirectory,
    [switch]$SkipEngineBuild
)
$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$workspaceRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
$vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
$vsRoot = @(& $vswhere -latest -version '[17.0,18.0)' -products '*' -property installationPath)[0]
$msbuild = Join-Path $vsRoot 'MSBuild\Current\Bin\MSBuild.exe'
$devenv = Join-Path $vsRoot 'Common7\IDE\devenv.com'
if (-not (Test-Path -LiteralPath $devenv)) { throw 'Visual Studio with Installer Projects is required.' }
$runtimeRoot = (Resolve-Path -LiteralPath $PythonRuntime).Path
$mqttRuntimeRoot = (Resolve-Path -LiteralPath $MqttRuntime).Path
$python = Join-Path $runtimeRoot 'python.exe'
if (-not $StagingDirectory) { $StagingDirectory = Join-Path $workspaceRoot ('.local\installer-' + (Get-Date -Format 'yyyyMMdd-HHmmss')) }
$stage = [IO.Path]::GetFullPath($StagingDirectory)
$destination = [IO.Path]::GetFullPath($OutputDirectory)
if ((Test-Path -LiteralPath $stage) -or (Test-Path -LiteralPath $destination)) { throw 'Choose new staging and output directories.' }
Push-Location $workspaceRoot
try {
    if (-not $SkipEngineBuild) {
        & (Join-Path $PSScriptRoot 'setup-sdk-dependencies.ps1')
        & $msbuild 'scenarioengine\project\vs2022\ScenarioEngineTest.vcxproj' /t:Build /p:Configuration=Release /p:Platform=x64 /p:UseDebugLibraries=false /p:VcpkgEnabled=false /m:4 /nr:false /nologo /v:quiet '/clp:ErrorsOnly;Summary'
        if ($LASTEXITCODE -ne 0) { throw 'Release engine build failed.' }
        & $msbuild 'mqttv2nconformance\project\vs2022\MqttPayload.vcxproj' /t:Build /p:Configuration=Release /p:Platform=x64 /p:UseDebugLibraries=false /p:VcpkgEnabled=false /m:4 /nr:false /nologo /v:quiet '/clp:ErrorsOnly;Summary'
        if ($LASTEXITCODE -ne 0) { throw 'Release MQTT UPER tool build failed.' }
    }
    & $python -I -B -X utf8 (Join-Path $PSScriptRoot 'package-installer.py') --version $Version --stage $stage --output $destination --python-runtime $runtimeRoot --mqtt-runtime $mqttRuntimeRoot
    if ($LASTEXITCODE -ne 0) { throw 'Installer staging failed.' }
    & $devenv (Join-Path $stage 'ScenarioEngineInstaller.sln') /Build Release /Project ScenarioEngineSetup /ProjectConfig Release /Out (Join-Path $stage 'installer-build.log')
    if ($LASTEXITCODE -ne 0) { throw "MSI build failed. See $stage\installer-build.log" }
    $msi = Join-Path $destination 'ScenarioEngineSetup.msi'
    if (-not (Test-Path -LiteralPath $msi -PathType Leaf)) { throw 'MSI was not generated.' }
    $hash = (Get-FileHash -LiteralPath $msi -Algorithm SHA256).Hash.ToLowerInvariant()
    [IO.File]::WriteAllText((Join-Path $destination 'SHA256SUMS.txt'), ($hash + '  ScenarioEngineSetup.msi' + [Environment]::NewLine))
    Write-Output "MSI created: $msi"
    Write-Output "SHA256: $hash"
} finally { Pop-Location }
