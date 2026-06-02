@echo off
REM Build script for Blackjack game with Raylib (Windows)

setlocal enabledelayedexpansion

REM Set paths
set RAYLIB_SRC=external\raylib\src
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

REM All raylib source files
set RAYLIB_SOURCES=%RAYLIB_SRC%\rcore.c %RAYLIB_SRC%\rshapes.c %RAYLIB_SRC%\rtextures.c %RAYLIB_SRC%\rtext.c %RAYLIB_SRC%\rmodels.c %RAYLIB_SRC%\raudio.c

REM Our game source files
set GAME_SOURCES=%SRC_DIR%\main.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\core\Game.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\core\Entity.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\models\Card.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\models\Deck.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\models\Hand.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\models\GameModel.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\views\GameView.cpp
set GAME_SOURCES=%GAME_SOURCES% %SRC_DIR%\controllers\GameController.cpp

echo Building Blackjack Game...
echo.

REM Compile and link
%CXX% %CXXFLAGS% %INCLUDES% %RAYLIB_SOURCES% %GAME_SOURCES% -o %OUTPUT% %LDFLAGS%

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful!
    echo Run %OUTPUT% to play the game.
) else (
    echo.
    echo Build failed. Please check error messages above.
)

endlocal
