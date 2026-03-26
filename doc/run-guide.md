# Bin X-ray Run Guide

## Visual Studio

1. Open `src/BinXray.slnx`.
2. Select configuration `Debug` and platform `x64`.
3. Build solution.
4. Run `BinXray` startup project.
5. Optionally run `BinXray.Tests` for quick sanity checks.

## VS Code

Recommended extensions:

- `ms-vscode.cpptools`
- `ms-vscode.powershell`

Common tasks:

- `Build BinXray (x64 Debug)`
- `Run BinXray (x64 Debug)`
- `Run Tests (x64 Debug)`

Debug launch profiles are provided in `.vscode/launch.json`.

## CLI Build

From repository root:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\scripts\invoke-msbuild.ps1 -ProjectPath src\BinXray.slnx -Configuration Debug -Platform x64 -Targets Build
```

## Local Release Pipeline Simulation

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\scripts\test-release-pipeline-local.ps1
```

Current packaging is a phase-1 placeholder that stages the executable artifact.
