[CmdletBinding()]
param()
$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$workspaceRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
$lock = Get-Content -LiteralPath (Join-Path $workspaceRoot 'dependencies.lock.json') -Raw -Encoding UTF8 | ConvertFrom-Json
$sdkRoot = Join-Path $workspaceRoot '.deps\sdk'
foreach ($sdk in $lock.externalSdks) {
    $archive = Join-Path $workspaceRoot $sdk.artifact
    if (-not (Test-Path -LiteralPath $archive -PathType Leaf)) { throw "SDK archive missing. Run git lfs pull: $archive" }
    $file = Get-Item -LiteralPath $archive
    if ($file.Length -ne $sdk.bytes) { throw "SDK archive size mismatch. Run git lfs pull: $archive" }
    $hash = (Get-FileHash -LiteralPath $archive -Algorithm SHA256).Hash.ToLowerInvariant()
    if ($hash -ne $sdk.sha256) { throw "SDK archive SHA-256 mismatch: $archive" }
    $destination = Join-Path $sdkRoot $sdk.directory
    $marker = Join-Path $destination '.scenarioengine-artifact-sha256'
    if (Test-Path -LiteralPath $marker) {
        if ((Get-Content -LiteralPath $marker -Raw).Trim() -eq $hash) {
            Write-Host "Verified installed SDK: $($sdk.name) $($sdk.version)"
            continue
        }
        throw "Different SDK is already installed: $destination"
    }
    if (Test-Path -LiteralPath $destination) { throw "Unmanaged or incomplete SDK directory: $destination" }
    New-Item -ItemType Directory -Path $sdkRoot -Force | Out-Null
    Expand-Archive -LiteralPath $archive -DestinationPath $sdkRoot
    $required = @('x64\include\openssl\opensslv.h', 'x64\lib\VC\static\libcrypto64MTd.lib', 'x64\lib\VC\static\libssl64MTd.lib', 'x64\lib\VC\static\libcrypto64MT.lib', 'x64\lib\VC\static\libssl64MT.lib', 'x64\libcrypto-1_1-x64.dll', 'x64\libssl-1_1-x64.dll')
    foreach ($relative in $required) {
        if (-not (Test-Path -LiteralPath (Join-Path $destination $relative) -PathType Leaf)) { throw "SDK payload missing: $relative" }
    }
    [IO.File]::WriteAllText($marker, $hash + [Environment]::NewLine)
    Write-Host "Installed SDK: $($sdk.name) $($sdk.version)"
}
Write-Host "SDK setup complete: $sdkRoot"
Write-Host 'Directory.Build.props selects this checkout-local SDK. No user/system environment change is needed.'
