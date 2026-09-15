[CmdletBinding()]
param()
$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$workspaceRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
$failures = [Collections.Generic.List[string]]::new()
function Check([bool]$Condition, [string]$Message) {
    if ($Condition) { Write-Host "PASS $Message" }
    else { $failures.Add($Message); Write-Host "FAIL $Message" }
}
$lock = Get-Content -LiteralPath (Join-Path $workspaceRoot 'dependencies.lock.json') -Raw -Encoding UTF8 | ConvertFrom-Json
foreach ($module in $lock.modules) {
    $path = Join-Path $workspaceRoot $module.name
    $exists = Test-Path -LiteralPath $path -PathType Container
    Check $exists "Source module: $($module.name)"
    if ($exists) {
        Check (((Get-Item -LiteralPath $path).Attributes -band [IO.FileAttributes]::ReparsePoint) -eq 0) "Regular directory: $($module.name)"
        Check (-not (Test-Path -LiteralPath (Join-Path $path '.git'))) "Monorepo ownership: $($module.name)"
    }
}
$pending = [Collections.Generic.Queue[string]]::new()
@(
    'scenarioengine\project\vs2022\ScenarioEngineTest.vcxproj',
    'GitsnDsrcEmulator\project\vs2022\GitsnDsrcEmulatorTest.vcxproj',
    'Itsk00126v1Emulator\project\vs2022\Itsk00126v1EmulatorTest.vcxproj',
    'ITSK00144_2Emulator\project\vs2022\ITSK00144_2EmulatorTest.vcxproj',
    'dimz\dz1_tools\dz1_tdc\project\vs2022\dz1_tdc.vcxproj',
    'dimz\dz1_tools\dz1_json\project\vs2022\dz1_json_compiler.vcxproj'
) | ForEach-Object { $pending.Enqueue((Join-Path $workspaceRoot $_)) }
$visited = [Collections.Generic.HashSet[string]]::new([StringComparer]::OrdinalIgnoreCase)
$referenceCount = 0
while ($pending.Count -gt 0) {
    $path = [IO.Path]::GetFullPath($pending.Dequeue())
    if (-not $visited.Add($path)) { continue }
    if (-not (Test-Path -LiteralPath $path -PathType Leaf)) { $failures.Add("Missing project: $path"); continue }
    [xml]$project = Get-Content -LiteralPath $path -Raw
    $base = Split-Path -Parent $path
    foreach ($node in $project.SelectNodes("//*[local-name()='ProjectReference' or local-name()='ClCompile' or local-name()='ClInclude' or local-name()='CustomBuild']")) {
        $include = $node.GetAttribute('Include')
        if ([string]::IsNullOrWhiteSpace($include) -or $include.Contains('$(') -or $include.Contains('%(')) { continue }
        $resolved = [IO.Path]::GetFullPath((Join-Path $base $include))
        $referenceCount++
        if (-not $resolved.StartsWith($workspaceRoot + '\', [StringComparison]::OrdinalIgnoreCase)) { $failures.Add("Reference escapes checkout: $path -> $include") }
        elseif (-not (Test-Path -LiteralPath $resolved -PathType Leaf)) { $failures.Add("Missing source/reference: $path -> $include") }
        if ($node.LocalName -eq 'ProjectReference') { $pending.Enqueue($resolved) }
    }
    foreach ($node in $project.SelectNodes("//*[local-name()='AdditionalIncludeDirectories' or local-name()='AdditionalLibraryDirectories']")) {
        if ($node.InnerText -match '[A-Za-z]:[\\/]') { $failures.Add("Absolute SDK path: $path") }
    }
}
Write-Host "Checked $($visited.Count) build projects and $referenceCount source/project references."
foreach ($sdk in $lock.externalSdks) {
    $archive = Join-Path $workspaceRoot $sdk.artifact
    $exists = Test-Path -LiteralPath $archive -PathType Leaf
    Check $exists "SDK archive: $($sdk.name)"
    if ($exists) {
        Check ((Get-Item -LiteralPath $archive).Length -eq $sdk.bytes) "SDK archive size: $($sdk.name)"
        Check ((Get-FileHash -LiteralPath $archive -Algorithm SHA256).Hash.ToLowerInvariant() -eq $sdk.sha256) "SDK archive SHA-256: $($sdk.name)"
    }
    foreach ($relative in @('x64\include\openssl\opensslv.h','x64\lib\VC\static\libcrypto64MTd.lib','x64\lib\VC\static\libssl64MT.lib')) {
        Check (Test-Path -LiteralPath (Join-Path $workspaceRoot ('.deps\sdk\' + $sdk.directory + '\' + $relative)) -PathType Leaf) "Installed SDK: $relative"
    }
}
Write-Host "FAIL=$($failures.Count)"
if ($failures.Count -gt 0) { throw ($failures -join [Environment]::NewLine) }
