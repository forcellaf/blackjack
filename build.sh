#!/bin/bash

# Blackjack Game Build Script

set -e

echo "Building Blackjack Game with Raylib..."

# Create object directories
mkdir -p obj_raylib
mkdir -p obj_game

# Compile raylib C files with gcc (as C code)
echo "Compiling raylib..."
RAYLIB_SOURCES=$(ls external/raylib/src/*.c)
for src in $RAYLIB_SOURCES; do
    basename=$(basename "$src" .c)
    echo "  Compiling $basename.c..."
    gcc -c -std=c11 -w -O2 -Iexternal/raylib/src "$src" -o "obj_raylib/${basename}.o"
done

# Combine raylib objects into a static library
echo "Creating raylib library..."
ar rcs libraylib.a obj_raylib/*.o

# Compile game C++ files with g++
echo "Compiling game sources..."
GAME_SOURCES="src/core/Game.cpp src/core/Entity.cpp"
GAME_SOURCES="$GAME_SOURCES src/models/Card.cpp"
GAME_SOURCES="$GAME_SOURCES src/models/Deck.cpp"
GAME_SOURCES="$GAME_SOURCES src/models/Hand.cpp"
GAME_SOURCES="$GAME_SOURCES src/models/GameModel.cpp"
GAME_SOURCES="$GAME_SOURCES src/views/GameView.cpp"
GAME_SOURCES="$GAME_SOURCES src/controllers/GameController.cpp"
GAME_SOURCES="$GAME_SOURCES src/main.cpp"

for src in $GAME_SOURCES; do
    basename=$(basename "$src" .cpp)
    dirname=$(dirname "$src" | sed 's|src/||')
    echo "  Compiling $basename.cpp..."
    mkdir -p "obj_game/$dirname"
    g++ -c -std=c++17 -w -O2 -Iinclude -Iexternal/raylib/src "$src" -o "obj_game/${dirname}${basename}.o"
done

# Link everything together
echo "Linking..."
g++ -std=c++17 -o RaylibGame.exe obj_game/**/*.o libraylib.a -lopengl32 -lgdi32 -lwinmm

echo "Build complete!"
echo "Run: ./RaylibGame.exe"
