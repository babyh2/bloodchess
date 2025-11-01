# Build Script for Blood Chess Game
# Automatically build the game with proper configuration

param(
    [string]$Configuration = "Release",
    [string]$Platform = "Win32",
    [switch]$Clean,
    [switch]$CopyDLLs
)

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  Blood Chess - Build Script" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

$SolutionPath = "$PSScriptRoot\gameSDL2\gameSDL2.sln"
$OutputPath = "$PSScriptRoot\gameSDL2\$Configuration"
$DllSourcePath = "$PSScriptRoot\gameSDL2\LibSdl2\Dll\X86"

# Check if solution exists
if (-not (Test-Path $SolutionPath)) {
    Write-Host "ERROR: Solution file not found at: $SolutionPath" -ForegroundColor Red
    exit 1
}

# Clean if requested
if ($Clean) {
    Write-Host "Cleaning previous build..." -ForegroundColor Yellow
    if (Test-Path $OutputPath) {
        Remove-Item -Path $OutputPath -Recurse -Force
        Write-Host "Clean completed!" -ForegroundColor Green
    }
    Write-Host ""
}

# Build
Write-Host "Building project..." -ForegroundColor Yellow
Write-Host "Configuration: $Configuration" -ForegroundColor Gray
Write-Host "Platform: $Platform" -ForegroundColor Gray
Write-Host ""

try {
    $buildCmd = "msbuild `"$SolutionPath`" /p:Configuration=$Configuration /p:Platform=$Platform /m /v:minimal"
    Invoke-Expression $buildCmd
    
    if ($LASTEXITCODE -ne 0) {
        Write-Host ""
        Write-Host "BUILD FAILED!" -ForegroundColor Red
        Write-Host "Please check the error messages above." -ForegroundColor Red
        exit 1
    }
    
    Write-Host ""
    Write-Host "BUILD SUCCESS!" -ForegroundColor Green
}
catch {
    Write-Host ""
    Write-Host "BUILD ERROR: $_" -ForegroundColor Red
    exit 1
}

# Copy DLLs if requested or if they don't exist
$shouldCopyDLLs = $CopyDLLs -or (-not (Test-Path "$OutputPath\SDL2.dll"))

if ($shouldCopyDLLs) {
    Write-Host ""
    Write-Host "Copying SDL2 DLLs..." -ForegroundColor Yellow
    
    if (-not (Test-Path $DllSourcePath)) {
        Write-Host "WARNING: DLL source path not found: $DllSourcePath" -ForegroundColor Yellow
        Write-Host "You may need to copy DLLs manually." -ForegroundColor Yellow
    }
    else {
        $dlls = Get-ChildItem -Path $DllSourcePath -Filter "*.dll"
        foreach ($dll in $dlls) {
            Copy-Item -Path $dll.FullName -Destination $OutputPath -Force
            Write-Host "  Copied: $($dll.Name)" -ForegroundColor Gray
        }
        Write-Host "DLLs copied successfully!" -ForegroundColor Green
    }
}

# Check for required resources
Write-Host ""
Write-Host "Checking resources..." -ForegroundColor Yellow

$requiredFiles = @(
    "Dreams.ttf",
    "dennham.jpg",
    "menuchinh.png",
    "shop.png",
    "win.png",
    "loss.png",
    "RULES_OF_THE_GAME.png"
)

$missingFiles = @()
foreach ($file in $requiredFiles) {
    if (-not (Test-Path "$OutputPath\$file")) {
        $missingFiles += $file
    }
}

if ($missingFiles.Count -gt 0) {
    Write-Host "WARNING: Missing resource files:" -ForegroundColor Yellow
    foreach ($file in $missingFiles) {
        Write-Host "  - $file" -ForegroundColor Gray
    }
    Write-Host "Game may not run correctly without these files." -ForegroundColor Yellow
}
else {
    Write-Host "All required resources found!" -ForegroundColor Green
}

# Summary
Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "  Build Complete!" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Output location: $OutputPath" -ForegroundColor White
Write-Host "Executable: $OutputPath\gameSDL2.exe" -ForegroundColor White
Write-Host ""
Write-Host "To run the game:" -ForegroundColor Yellow
Write-Host "  cd `"$OutputPath`"" -ForegroundColor Gray
Write-Host "  .\gameSDL2.exe" -ForegroundColor Gray
Write-Host ""
Write-Host "Or simply press F5 in Visual Studio!" -ForegroundColor Cyan
Write-Host ""
