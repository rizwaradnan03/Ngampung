$env:PATH="C:\raylib\w64devkit\bin;" + $env:PATH

g++ ($files = Get-ChildItem .\src -Recurse -Filter *.cpp | ForEach-Object FullName) `
-o game.exe `
-Isrc -Iinclude -Ilib/include -Llib/lib `
-lraylib -lopengl32 -lgdi32 -lwinmm -lws2_32

if ($LASTEXITCODE -ne 0) {
    echo "compile error"
    exit
}

./game.exe