# SPDX-License-Identifier: MIT
param(
    [Parameter(Mandatory = $true)]
    [string]$AppExePath,
    [Parameter(Mandatory = $true)]
    [string]$Version,
    [string]$OutputDir = "artifacts\release"
)

$ErrorActionPreference = "Stop"

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path
$outputPath = Join-Path $repoRoot $OutputDir
New-Item -ItemType Directory -Path $outputPath -Force | Out-Null

if (-not (Test-Path -LiteralPath $AppExePath)) {
    throw "Application executable was not found: $AppExePath"
}

$stagingExe = Join-Path $outputPath ("BinXray-{0}.exe" -f $Version)
Copy-Item -LiteralPath $AppExePath -Destination $stagingExe -Force

Write-Host "Packaging placeholder complete."
Write-Host "Staged executable: $stagingExe"
Write-Host "Next phase: replace this script with real WiX build (MSI + bootstrapper)."
