param(
    [ValidateSet("x64", "Win32")]
    [string]$Architecture = "x64"
)

$ErrorActionPreference = "Stop"

function Invoke-Checked {
    param(
        [Parameter(Mandatory = $true)]
        [string]$Command,

        [Parameter(Mandatory = $true)]
        [string[]]$ArgumentList
    )

    & $Command @ArgumentList
    if ($LASTEXITCODE -ne 0) {
        throw "$Command failed with exit code $LASTEXITCODE"
    }
}

$RepoDir = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path.Replace("\", "/")
$ExtSourceDir = "$RepoDir/s2e-core/ExtLibraries"
$ExtInstallDir = "$RepoDir/ExtLibraries"
$SettingsDir = "$RepoDir/settings"

if ($Architecture -eq "x64") {
    $Build64Bit = "ON"
    $Preset = "windows-x64-debug"
} else {
    $Build64Bit = "OFF"
    $Preset = "windows-win32-debug"
}

$ExtBuildDir = "$RepoDir/build/extlibraries-$Preset"

Invoke-Checked "git" @(
    "-C", $RepoDir,
    "submodule", "update", "--init", "--recursive"
)

Invoke-Checked "cmake" @(
    "-S", $ExtSourceDir,
    "-B", $ExtBuildDir,
    "-G", "Visual Studio 17 2022",
    "-A", $Architecture,
    "-DEXT_LIB_DIR=$ExtInstallDir",
    "-DSETTINGS_DIR=$SettingsDir",
    "-DBUILD_64BIT=$Build64Bit"
)

Invoke-Checked "cmake" @(
    "--build", $ExtBuildDir,
    "--config", "Debug",
    "--parallel"
)

Invoke-Checked "cmake" @(
    "--install", $ExtBuildDir,
    "--config", "Debug"
)

Push-Location $RepoDir
try {
    Invoke-Checked "cmake" @("--preset", $Preset)
    Invoke-Checked "cmake" @("--build", "--preset", $Preset, "--parallel")
} finally {
    Pop-Location
}

Write-Host "Setup completed with preset: $Preset"
