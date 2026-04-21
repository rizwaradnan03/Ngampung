$env:PATH="C:\raylib\w64devkit\bin;" + $env:PATH

# g++ src/*.cpp src/engine/*.cpp -o game.exe -Iinclude -Ilib/include -Llib/lib -lraylib -lopengl32 -lgdi32 -lwinmm
g++ src/*.cpp src/engine/*.cpp -o game.exe -Isrc -Iinclude -Ilib/include -Llib/lib -lraylib -lopengl32 -lgdi32 -lwinmm

if ($LASTEXITCODE -ne 0) {
    echo "compile error"
    exit
}

./game.exe