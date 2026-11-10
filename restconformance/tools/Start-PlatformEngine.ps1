[CmdletBinding()]
param(
    [Parameter(Mandatory)][string]$AgentUrl,
    [switch]$PrepareEvidenceReview
)
$ErrorActionPreference = 'Stop'
$workspace = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
if ($AgentUrl.StartsWith('scts://')) { $AgentUrl = $AgentUrl.Substring(7) }
if ($AgentUrl -notmatch '^wss://106\.250\.189\.37:8443/ws/test/agent/\d+/$') {
    throw 'Use the Agent connection URL provided by the selected test on the police test platform.'
}
$engine = Join-Path $workspace 'scenarioengine\project\vs2022\DebugTest64\ScenarioEngineTest.exe'
if (-not (Test-Path -LiteralPath $engine)) {
    throw 'Build the improved ScenarioEngineTest (Debug|x64) first.'
}
if ($PrepareEvidenceReview) {
    & (Join-Path $PSScriptRoot 'Prepare-ReviewRuntime.ps1') -Executable $engine
}
$runDirectory = Join-Path $workspace ('.local\rest-platform-runs\' + (Get-Date -Format 'yyyyMMdd-HHmmss-ffff'))
New-Item -ItemType Directory -Path $runDirectory | Out-Null
$process = Start-Process -FilePath $engine -ArgumentList $AgentUrl -WorkingDirectory $runDirectory -WindowStyle Hidden -PassThru -RedirectStandardOutput (Join-Path $runDirectory 'engine-stdout.log') -RedirectStandardError (Join-Path $runDirectory 'engine-stderr.log')
[ordered]@{
    processId = $process.Id
    executable = $engine
    executableSha256 = (Get-FileHash -LiteralPath $engine -Algorithm SHA256).Hash
    startedAt = (Get-Date).ToString('o')
} | ConvertTo-Json | Set-Content -LiteralPath (Join-Path $runDirectory 'process.json') -Encoding utf8
Write-Output ('Engine process: ' + $process.Id)
Write-Output ('Results and logs: ' + $runDirectory)
Write-Output ('After finishing the test, close this engine with: Stop-Process -Id ' + $process.Id)
