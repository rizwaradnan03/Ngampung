$env:PATH="C:\raylib\w64devkit\bin;" + $env:PATH

g++ src/*.cpp -o game.exe -Ilib/include -Llib/lib -lraylib -lopengl32 -lgdi32 -lwinmm

if ($LASTEXITCODE -ne 0) {
    echo "compile error"
    exit
}

./game.exe