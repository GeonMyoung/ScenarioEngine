[CmdletBinding()]
param([ValidateSet('Debug','Release')][string]$Configuration='Debug',[switch]$Engine)
$ErrorActionPreference='Stop'
$root=[IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
$vswhere=Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
$builder=@(& $vswhere -latest -version '[17.0,18.0)' -products '*' -requires Microsoft.Component.MSBuild -find 'MSBuild\Current\Bin\MSBuild.exe') | Select-Object -First 1
if(-not $builder){throw 'Visual Studio 2022 MSBuild not found.'}
$targets=@('mqttv2nconformance\project\vs2022\MqttPayload.vcxproj','mqttv2nconformance\project\vs2022\MqttV2NConformance.vcxproj')
if($Engine){$targets+='scenarioengine\project\vs2022\ScenarioEngineTest.vcxproj'}
Push-Location $root
try {
 foreach($target in $targets){
  & $builder $target /t:Build "/p:Configuration=$Configuration" /p:Platform=x64 /m:4 /nr:false /nologo /v:quiet '/clp:ErrorsOnly;Summary'
  if($LASTEXITCODE -ne 0){throw "Build failed: $target"}
 }
} finally {Pop-Location}
