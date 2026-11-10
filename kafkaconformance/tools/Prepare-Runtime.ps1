[CmdletBinding()]
param([Parameter(Mandatory)][string]$Destination,[string]$Python='python')
$ErrorActionPreference='Stop'
$moduleRoot=[IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
$repoRoot=[IO.Path]::GetFullPath((Join-Path $moduleRoot '..'))
$targetRoot=[IO.Path]::GetFullPath($Destination)
if(Test-Path -LiteralPath $targetRoot){throw 'Use a new directory; existing execution evidence is preserved.'}
$buildRoot=Join-Path $repoRoot 'scenarioengine\project\vs2022\DebugTest64'
$enginePath=Join-Path $buildRoot 'ScenarioEngineTest.exe'
if(-not(Test-Path -LiteralPath $enginePath)){throw 'Build ScenarioEngineTest Debug/x64 first.'}
New-Item -ItemType Directory -Path $targetRoot | Out-Null
Copy-Item -LiteralPath $enginePath -Destination $targetRoot
Get-ChildItem -LiteralPath $buildRoot -Filter '*.dll' | ForEach-Object {Copy-Item -LiteralPath $_.FullName -Destination $targetRoot}
$targetModule=Join-Path $targetRoot 'kafkaconformance';New-Item -ItemType Directory -Path $targetModule | Out-Null
foreach($part in @('runtime','emulator','fixtures','registration')){Copy-Item -LiteralPath (Join-Path $moduleRoot $part) -Destination (Join-Path $targetModule $part) -Recurse}
& $Python -m venv (Join-Path $targetRoot 'python')
if($LASTEXITCODE){throw 'Python venv creation failed.'}
$targetPython=Join-Path $targetRoot 'python\Scripts\python.exe'
& $targetPython -m pip install -r (Join-Path $moduleRoot 'requirements.txt')
if($LASTEXITCODE){throw 'Kafka dependency installation failed.'}
$runtimeJson=@{python=$targetPython;module=$targetModule} | ConvertTo-Json
[IO.File]::WriteAllText((Join-Path $targetRoot 'kafka-runtime.json'),$runtimeJson,[Text.UTF8Encoding]::new($false))
Get-FileHash -LiteralPath (Join-Path $targetRoot 'ScenarioEngineTest.exe') -Algorithm SHA256
Write-Output "Prepared $targetRoot. Use a separate working directory for each test run."
