@echo off
REM Blackjack Game Setup Script for Windows

echo Setting up Blackjack Game with Raylib...

REM Create external directory if it doesn't exist
if not exist "external" mkdir external

REM Clone raylib if it doesn't exist
if not exist "external\raylib" (
    echo Cloning raylib...
    cd external
    git clone https://github.com/raysan5/raylib.git
    cd ..
) else (
    echo Raylib already exists in external\raylib
)

REM Create build directory
if not exist "build" mkdir build
cd build

REM Generate build files
echo Generating CMake build files...
cmake ..

REM Build the project
echo Building project...
cmake --build . --config Release

echo.
echo Build complete!
echo.
echo To run the game:
echo   cd build\Release
echo   RaylibGame.exe
pause
