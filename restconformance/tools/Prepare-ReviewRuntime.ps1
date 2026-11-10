[CmdletBinding()]
param(
    [Parameter(Mandatory)][string]$Executable,
    [string]$PythonExecutable
)
$ErrorActionPreference = 'Stop'
$reviewExe = (Resolve-Path -LiteralPath $Executable).Path
if (-not $PythonExecutable) { $PythonExecutable = @(Get-Command python -CommandType Application -ErrorAction Stop)[0].Source }
$reviewPython = (Resolve-Path -LiteralPath $PythonExecutable).Path
& $reviewPython -I -c 'import sys; assert sys.version_info >= (3, 10)'
if ($LASTEXITCODE -ne 0) { throw 'Python 3.10 or newer is required for the evidence reviewer.' }
$reviewRoot = Split-Path -Parent $reviewExe
$reviewPackage = Join-Path $reviewRoot 'rest-review'
New-Item -ItemType Directory -Path $reviewPackage -Force | Out-Null
foreach ($name in @('engine_review_worker.py','review_method_evidence.py','evidence_method_contract.py','evidence_values.py')) {
    Copy-Item -LiteralPath (Join-Path $PSScriptRoot $name) -Destination (Join-Path $reviewPackage $name) -Force
}
$reviewConfig = [ordered]@{ schemaVersion = 1; pythonExecutable = $reviewPython; worker = 'rest-review/engine_review_worker.py' }
[IO.File]::WriteAllText((Join-Path $reviewRoot 'rest-review-runtime.json'), ($reviewConfig | ConvertTo-Json), (New-Object Text.UTF8Encoding($false)))
Write-Output ('Evidence review runtime prepared for: ' + $reviewExe)
