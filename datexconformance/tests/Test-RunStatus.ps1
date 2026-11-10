[CmdletBinding()]
param([Parameter(Mandatory)][string]$OutputDirectory)
$ErrorActionPreference='Stop'
$source=Join-Path $PSScriptRoot '..\manual'
$bundle=[IO.Path]::GetFullPath($OutputDirectory)
if(Test-Path -LiteralPath $bundle){throw 'Use a new test output directory.'}
$run=Join-Path $bundle 'runs\status-fixture'
New-Item -ItemType Directory -Path $run -Force | Out-Null
foreach($file in @('Common.ps1','Get-RunStatus.ps1')){Copy-Item -LiteralPath (Join-Path $source $file) -Destination (Join-Path $bundle $file)}
@{bundleRoot=$bundle;scenario=54;batch='custom'} | ConvertTo-Json | Set-Content -LiteralPath (Join-Path $run 'session.json') -Encoding UTF8
@'
{"event":"session_error","plannedTest":"test_normal_bsm","message":"CONNECTION_CLOSED"}
{"event":"error","message":"top-level failure"}
{"event":"finished","exitCode":1}
'@ | Set-Content -LiteralPath (Join-Path $run 'sut.jsonl') -Encoding UTF8
$failure=(& (Join-Path $bundle 'Get-RunStatus.ps1') -RunDirectory $run *>&1 | Out-String)
if($failure -notmatch 'errors=2' -or $failure -notmatch 'test_normal_bsm' -or $failure -notmatch 'session_error' -or $failure -notmatch 'exitCode=1'){throw ('Missing session failure in status: '+$failure)}
$failure | Set-Content -LiteralPath (Join-Path $bundle 'failure-status.txt') -Encoding UTF8
'{"event":"finished","exitCode":0}' | Set-Content -LiteralPath (Join-Path $run 'sut.jsonl') -Encoding UTF8
$success=(& (Join-Path $bundle 'Get-RunStatus.ps1') -RunDirectory $run *>&1 | Out-String)
if($success -notmatch 'errors=0' -or $success -notmatch 'exitCode=0' -or $success -match 'reached the end with errors'){throw ('Normal completion misclassified: '+$success)}
$success | Set-Content -LiteralPath (Join-Path $bundle 'success-status.txt') -Encoding UTF8
'PASS status: session errors, run errors, affected testName, failed/normal completion'
