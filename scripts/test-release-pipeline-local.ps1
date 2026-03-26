# SPDX-License-Identifier: MIT
param(
    [string]$Configuration = "Release",
    [string]$Platform = "x64",
    [string]$PlatformToolset = "v143",
    [string]$OutputDir = "artifacts\release",
    [switch]$SkipPackaging
)

$ErrorActionPreference = "Stop"

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path
Push-Location $repoRoot

try {
    $version = python scripts/get_version.py
    if (-not $version) {
        throw "Failed to read version from scripts/get_version.py."
    }

    $solutionDir = Join-Path $repoRoot "src\"
    $intDir = Join-Path $repoRoot "build\obj\"
    $outDir = Join-Path $repoRoot "build\bin\"

    $repoUrl = (& git config --get remote.origin.url 2>$null)
    if ($repoUrl) {
        $repoUrl = $repoUrl.Trim()
    }
    if (-not $repoUrl) {
        $repoUrl = "unknown"
    }

    $branch = (& git rev-parse --abbrev-ref HEAD 2>$null)
    if ($branch) { $branch = $branch.Trim() }
    if (-not $branch) { $branch = "unknown" }

    $commit = (& git rev-parse HEAD 2>$null)
    if ($commit) { $commit = $commit.Trim() }
    if (-not $commit) { $commit = "unknown" }

    & ".\scripts\invoke-msbuild.ps1" `
        -ProjectPath "src\BinXray\BinXray.vcxproj" `
        -Configuration $Configuration `
        -Platform $Platform `
        -Targets "Build" `
        -AdditionalMsBuildArgs @(
            "/p:PlatformToolset=$PlatformToolset",
            "/p:BxrBuildRepoUrl=$repoUrl",
            "/p:BxrBuildBranch=$branch",
            "/p:BxrBuildCommit=$commit",
            "/p:BxrBuildVersion=$version",
            "/p:SolutionDir=$solutionDir",
            "/p:IntDir=$intDir",
            "/p:OutDir=$outDir"
        )

    if ($SkipPackaging) {
        Write-Host "SkipPackaging was set. Build stage completed successfully."
        return
    }

    & ".\packaging\build-packages.ps1" `
        -AppExePath "$repoRoot\build\bin\BinXray.exe" `
        -Version $version `
        -OutputDir $OutputDir

    if ($LASTEXITCODE -ne 0) {
        throw "Packaging failed with exit code $LASTEXITCODE."
    }
}
finally {
    Pop-Location
}
