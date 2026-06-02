# Blackjack Game Makefile

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
RAYLIB_PATH = external/raylib
RAYLIB_LIB = $(RAYLIB_PATH)/raylib/libraylib.a

# Platform-specific flags
ifeq ($(OS),Windows_NT)
    LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm
    TARGET = RaylibGame.exe
    RAYLIB_INCLUDE = -I$(RAYLIB_PATH)/raylib/external/glfw/include
else
    LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    TARGET = RaylibGame
    RAYLIB_INCLUDE =
endif

# Source files
SOURCES = $(wildcard src/**/*.cpp src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

INCLUDE = -Iinclude -I$(RAYLIB_PATH)/raylib/src

# Default target
all: $(TARGET)

# Build raylib library first
$(RAYLIB_LIB):
	$(MAKE) -C $(RAYLIB_PATH)/raylib PLATFORM=Desktop PLATFORM_OS=WINDOWS BUILD_MODE=Release

# Link the executable
$(TARGET): $(RAYLIB_LIB) $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(RAYLIB_LIB) $(LDFLAGS)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)

# Clean and rebuild
rebuild: clean all

# Run the game
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean rebuild run
