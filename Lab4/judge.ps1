$ErrorActionPreference = "Stop"

$exe = "main.exe"
$sourceFiles = @("main.c", "avl.c")
$testDir = "tests"

Write-Host "Building $exe ..."
& gcc -fdiagnostics-color=always -g @sourceFiles -o $exe
if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed." -ForegroundColor Red
    exit 1
}

$inputFiles = Get-ChildItem -Path $testDir -Filter "*_input.txt" | Sort-Object Name
if ($inputFiles.Count -eq 0) {
    Write-Host "No test input files found in $testDir." -ForegroundColor Red
    exit 1
}

$passed = 0
$failed = 0

foreach ($inputFile in $inputFiles) {
    $caseName = $inputFile.BaseName -replace "_input$", ""
    $expectedFile = Join-Path $testDir "$caseName`_output.txt"

    if (-not (Test-Path $expectedFile)) {
        Write-Host "[$caseName] FAIL: missing expected file $expectedFile" -ForegroundColor Red
        $failed++
        continue
    }

    $actualFile = Join-Path $env:TEMP "lab4_$caseName`_actual.txt"
    $command = ".\$exe < `"$($inputFile.FullName)`" > `"$actualFile`""

    cmd /c $command
    if ($LASTEXITCODE -ne 0) {
        Write-Host "[$caseName] FAIL: program exited with code $LASTEXITCODE" -ForegroundColor Red
        $failed++
        continue
    }

    $diff = Compare-Object `
        -ReferenceObject (Get-Content $expectedFile) `
        -DifferenceObject (Get-Content $actualFile)

    if ($diff) {
        Write-Host "[$caseName] FAIL: output differs" -ForegroundColor Red
        Write-Host "Expected: $expectedFile"
        Write-Host "Actual:   $actualFile"
        $failed++
    }
    else {
        Write-Host "[$caseName] PASS" -ForegroundColor Green
        Remove-Item -LiteralPath $actualFile -ErrorAction SilentlyContinue
        $passed++
    }
}

Write-Host ""
Write-Host "Result: $passed passed, $failed failed."

if ($failed -ne 0) {
    exit 1
}

exit 0
