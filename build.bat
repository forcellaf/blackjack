@echo off
REM Build script for Blackjack game with Raylib (Windows)

setlocal enabledelayedexpansion

REM Set paths
set SRC_DIR=src
set INCLUDE_DIR=include
set OUTPUT=RaylibGame.exe

REM Compiler flags (adjust for your environment)
REM Common setup: GCC via scoop, MinGW, or similar
set CXX=g++
set CXXFLAGS=-std=c++17 -Wall -O2
set INCLUDES=-I%INCLUDE_DIR% -Iexternal\raylib\src

REM Linker flags for Windows with OpenGL
set LDFLAGS=-lopengl32 -lgdi32 -lwinmm

REM Use pre-built raylib library
set RAYLIB_LIB=libraylib.a

REM Our game source files
set GAME_SOURCES=%SRC_DIR%\main.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\core\Game.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\core\Entity.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\models\Card.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\models\Deck.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\models\Hand.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\models\GameModel.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\models\MenuModel.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\models\SaveData.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\models\SaveManager.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\views\GameView.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\views\MenuView.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\controllers\GameController.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\controllers\MenuController.cpp

echo Building Blackjack Game...
echo.

REM Compile game sources and link with raylib library
%CXX% %CXXFLAGS% %INCLUDES% %GAME_SOURCES% -o %OUTPUT% %RAYLIB_LIB% %LDFLAGS%

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful!
    echo Run %OUTPUT% to play the game.
) else (
    echo.
    echo Build failed. Please check error messages above.
)

endlocal
