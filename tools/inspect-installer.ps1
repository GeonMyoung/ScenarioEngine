[CmdletBinding()]
param(
    [Parameter(Mandatory)][string]$Msi,
    [Parameter(Mandatory)][string]$OutputJson
)
$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$installer = New-Object -ComObject WindowsInstaller.Installer
$path = (Resolve-Path -LiteralPath $Msi).Path
$database = $installer.GetType().InvokeMember('OpenDatabase', 'InvokeMethod', $null, $installer, @($path, 0))
function Read-InstallerTable {
    param([string]$Sql, [string[]]$Columns)
    $view = $database.GetType().InvokeMember('OpenView', 'InvokeMethod', $null, $database, @($Sql))
    try {
        [void]$view.GetType().InvokeMember('Execute', 'InvokeMethod', $null, $view, $null)
        while ($record = $view.GetType().InvokeMember('Fetch', 'InvokeMethod', $null, $view, $null)) {
            $row = [ordered]@{}
            for ($n = 1; $n -le $Columns.Count; $n++) {
                $row[$Columns[$n-1]] = $record.GetType().InvokeMember('StringData', 'GetProperty', $null, $record, @($n))
            }
            [pscustomobject]$row
        }
    } finally { [void]$view.GetType().InvokeMember('Close', 'InvokeMethod', $null, $view, $null) }
}
$properties = @{}
Read-InstallerTable 'SELECT Property, Value FROM Property' @('name','value') | ForEach-Object { $properties[$_.name] = $_.value }
$files = @(Read-InstallerTable 'SELECT File, Component_, FileName, FileSize, Version FROM File' @('id','component','name','bytes','version'))
$components = @(Read-InstallerTable 'SELECT Component, ComponentId, Directory_, Attributes, KeyPath FROM Component' @('id','guid','directory','attributes','keyPath'))
$shortcuts = @(Read-InstallerTable 'SELECT Shortcut, Directory_, Name, Component_, Target, Arguments, WkDir FROM Shortcut' @('id','directory','name','component','target','arguments','workingDirectory'))
$upgrades = @(Read-InstallerTable 'SELECT UpgradeCode, VersionMin, VersionMax, Attributes, ActionProperty FROM Upgrade' @('upgradeCode','minimum','maximum','attributes','property'))
$directories = @(Read-InstallerTable 'SELECT Directory, Directory_Parent, DefaultDir FROM Directory' @('id','parent','name'))
$summary = $database.GetType().InvokeMember('SummaryInformation', 'GetProperty', $null, $database, @(0))
$template = $summary.GetType().InvokeMember('Property', 'GetProperty', $null, $summary, @(7))
$resolvedShortcuts = @($shortcuts | ForEach-Object {
    $shortcut = $_
    $targetFiles = @($files | Where-Object { $_.component -eq $shortcut.component } | ForEach-Object { ($_.name -split '\|')[-1] })
    [pscustomobject]@{name=($_.name -split '\|')[-1]; directory=$_.directory; workingDirectory=$_.workingDirectory; files=$targetFiles}
})
$result = [ordered]@{
    msi=$path; sha256=(Get-FileHash -LiteralPath $path -Algorithm SHA256).Hash.ToLowerInvariant()
    productName=$properties['ProductName']; version=$properties['ProductVersion']; productCode=$properties['ProductCode']
    upgradeCode=$properties['UpgradeCode']; template=$template; allUsers=$properties['ALLUSERS']
    files=$files; components=$components; shortcuts=$resolvedShortcuts; upgrades=$upgrades; directories=$directories
}
if ($result.productName -ne 'ScenarioEngine' -or $result.upgradeCode -ne '{A490AAFB-0951-4654-B4EA-241C2DEA54B4}') { throw 'Unexpected product identity.' }
if ($template -notlike 'x64;*') { throw "Not an x64 installer: $template" }
foreach ($name in @('Edit Scenario Engine','Run Scenario Engine')) {
    $matches = @($resolvedShortcuts | Where-Object name -eq $name)
    if ($matches.Count -ne 2) { throw "Expected desktop/start-menu shortcuts for $name" }
    $target = if ($name.StartsWith('Edit')) {'edit_runbat.cmd'} else {'run_runbat.cmd'}
    if (@($matches | Where-Object {$_.files -notcontains $target}).Count) { throw "Incorrect target for $name" }
}
[IO.File]::WriteAllText([IO.Path]::GetFullPath($OutputJson), ($result | ConvertTo-Json -Depth 10), (New-Object Text.UTF8Encoding($false)))
Write-Output ("Verified MSI: {0}, version {1}, {2}, {3} files, 4 correct shortcuts." -f $result.productName,$result.version,$template,$files.Count)
