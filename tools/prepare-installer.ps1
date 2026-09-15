[CmdletBinding()]
param()
$ErrorActionPreference = 'Stop'
$workspaceRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
$output = Join-Path $workspaceRoot 'scenarioengine\project\vs2022\ReleaseTest64'
$installer = Join-Path $workspaceRoot 'ScenarioEngineSetup'
foreach ($name in @('ScenarioEngineTest.exe','pthreadVC2.dll','libcrypto-1_1-x64.dll','libssl-1_1-x64.dll')) {
    $source = Join-Path $output $name
    if (-not (Test-Path -LiteralPath $source -PathType Leaf)) { throw "Release build output missing: $source" }
    if ($name -ne 'ScenarioEngineTest.exe') { Copy-Item -LiteralPath $source -Destination (Join-Path $installer $name) }
}
foreach ($name in @('ScenarioEngineTest.ico','Product.bmp')) {
    Copy-Item -LiteralPath (Join-Path $workspaceRoot ('scenarioengine\' + $name)) -Destination (Join-Path $output $name)
}
[IO.File]::WriteAllText((Join-Path $installer 'ScenarioEngineTest.log'), '')
Write-Host 'Installer inputs prepared. Build ScenarioEngineSetup.vdproj with Visual Studio Installer Projects.'
