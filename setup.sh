#!/bin/bash

# Blackjack Game Setup Script

echo "Setting up Blackjack Game with Raylib..."

# Create external directory if it doesn't exist
mkdir -p external

# Clone raylib if it doesn't exist
if [ ! -d "external/raylib" ]; then
    echo "Cloning raylib..."
    cd external
    git clone https://github.com/raysan5/raylib.git
    cd ..
else
    echo "Raylib already exists in external/raylib"
fi

# Create build directory
mkdir -p build
cd build

# Generate build files
echo "Generating CMake build files..."
cmake ..

# Build the project
echo "Building project..."
cmake --build . --config Release

echo ""
echo "Build complete!"
echo ""
echo "To run the game:"
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "win32" ]]; then
    echo "  cd build/Release"
    echo "  ./RaylibGame.exe"
else
    echo "  cd build"
    echo "  ./RaylibGame"
fi
