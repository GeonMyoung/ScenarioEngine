[CmdletBinding()]
param([switch]$SkipBuild)
$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$workspace = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
Push-Location $workspace
try {
    if (-not $SkipBuild) {
        & (Join-Path $PSScriptRoot 'setup-sdk-dependencies.ps1')
        $vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
        $builder = @(& $vswhere -latest -version '[17.0,18.0)' -products '*' -requires Microsoft.Component.MSBuild -find 'MSBuild\Current\Bin\MSBuild.exe') | Select-Object -First 1
        if (-not $builder) { throw 'Visual Studio 2022 MSBuild not found.' }
        & $builder 'datexconformance\project\vs2022\DatexConformanceTests.vcxproj' /t:Build /p:Configuration=Debug /p:Platform=x64 /m:4 /nr:false /nologo /v:quiet '/clp:ErrorsOnly;Summary'
        if ($LASTEXITCODE -ne 0) { throw 'New DATEX test build failed.' }
    }
    & '.\datexconformance\project\vs2022\Debug64\DatexConformanceTests.exe'
    if ($LASTEXITCODE -ne 0) { throw 'New DATEX local tests failed.' }
    python -X utf8 'datexconformance\tools\check_legacy.py'
    if ($LASTEXITCODE -ne 0) { throw 'Legacy baseline mismatch.' }
} finally { Pop-Location }
