# Blackjack Game - MVC Framework with Raylib

A fully functional Blackjack game built with C++ using the MVC (Model-View-Controller) architectural pattern and Object-Oriented Programming principles.

## Features

- **MVC Architecture**: Clean separation of concerns with Models, Views, and Controllers
- **Object-Oriented Design**: Full OOP implementation with inheritance, polymorphism, and encapsulation
- **Raylib Graphics**: Smooth rendering with raylib game library
- **Main Menu System**: Beautiful main menu with save/load functionality
- **Save/Load System**: Persistent game state with 5 save slots
- **Auto-save**: Automatically saves after each round
- **Complete Blackjack Rules**:
  - Hit and Stand actions
  - Blackjack detection
  - Dealer AI (hits on 16 or less, stands on 17+)
  - Automatic shuffling when deck is low
  - Push detection for ties
  - Statistics tracking (wins, losses, pushes)

## Project Structure

```
blackjack_cpp/
├── CMakeLists.txt           # CMake build configuration
├── README.md                # This file
├── ARCHITECTURE.md          # Detailed architecture documentation
├── include/
│   ├── core/
│   │   ├── Entity.hpp      # Base class for all game entities
│   │   └── Game.hpp        # Main game class managing game loop
│   ├── models/
│   │   ├── Model.hpp       # Base class for all models
│   │   ├── Card.hpp        # Playing card representation
│   │   ├── Deck.hpp        # Card deck management
│   │   ├── Hand.hpp        # Player/dealer hand
│   │   ├── GameModel.hpp   # Main game model
│   │   ├── MenuModel.hpp   # Main menu model
│   │   ├── SaveData.hpp    # Save data serialization
│   │   └── SaveManager.hpp # File I/O for save/load
│   ├── views/
│   │   ├── View.hpp        # Base class for all views
│   │   ├── GameView.hpp    # Game rendering view
│   │   └── MenuView.hpp    # Main menu rendering
│   └── controllers/
│       ├── Controller.hpp  # Base class for all controllers
│       ├── GameController.hpp # Game input handling
│       └── MenuController.hpp # Menu input handling
├── src/
│   ├── core/
│   │   ├── Game.cpp        # Game implementation
│   │   └── Entity.cpp      # Entity static member initialization
│   ├── models/
│   │   ├── Card.cpp        # Card implementation
│   │   ├── Deck.cpp        # Deck implementation
│   │   ├── Hand.cpp        # Hand implementation
│   │   ├── GameModel.cpp   # Game model implementation
│   │   ├── MenuModel.cpp   # Menu model implementation
│   │   ├── SaveData.cpp    # Save data implementation
│   │   └── SaveManager.cpp # Save manager implementation
│   ├── views/
│   │   ├── GameView.cpp    # Game view implementation
│   │   └── MenuView.cpp    # Menu view implementation
│   ├── controllers/
│   │   ├── GameController.cpp # Controller implementation
│   │   └── MenuController.cpp # Menu controller implementation
│   └── main.cpp            # Entry point
├── build.bat               # Windows build script
├── build-raylib.bat        # Raylib library build script
└── build.sh                # Linux/macOS build script
```

## Setup Instructions

### Prerequisites

- GCC with C++17 support (or compatible compiler)
- Make (optional, for using build.sh)

### Building on Windows

1. Build the raylib library first:
```bash
build-raylib.bat
```

2. Build the game:
```bash
build.bat
```

3. Run the game:
```bash
RaylibGame.exe
```

### Building on Linux/macOS

1. Build raylib:
```bash
mkdir -p obj_raylib
gcc -c -std=c99 -O2 -w -DPLATFORM_DESKTOP -Iexternal/raylib/src -Iexternal/raylib/src/external/glfw/include \
    external/raylib/src/rcore.c -o obj_raylib/rcore.o
gcc -c -std=c99 -O2 -w -DPLATFORM_DESKTOP -Iexternal/raylib/src -Iexternal/raylib/src/external/glfw/include \
    external/raylib/src/rshapes.c -o obj_raylib/rshapes.o
gcc -c -std=c99 -O2 -w -DPLATFORM_DESKTOP -Iexternal/raylib/src -Iexternal/raylib/src/external/glfw/include \
    external/raylib/src/rtextures.c -o obj_raylib/rtextures.o
gcc -c -std=c99 -O2 -w -DPLATFORM_DESKTOP -Iexternal/raylib/src -Iexternal/raylib/src/external/glfw/include \
    external/raylib/src/rtext.c -o obj_raylib/rtext.o
gcc -c -std=c99 -O2 -w -DPLATFORM_DESKTOP -Iexternal/raylib/src -Iexternal/raylib/src/external/glfw/include \
    external/raylib/src/rmodels.c -o obj_raylib/rmodels.o
gcc -c -std=c99 -O2 -w -DPLATFORM_DESKTOP -Iexternal/raylib/src -Iexternal/raylib/src/external/glfw/include \
    external/raylib/src/raudio.c -o obj_raylib/raudio.o

ar rcs libraylib.a obj_raylib/*.o
```

2. Build the game:
```bash
build.sh
```

3. Run the game:
```bash
./RaylibGame
```

## Game Controls

### Main Menu
- **Arrow Up/Down** - Navigate menu options
- **Enter** - Select option
- **ESC** - Go back/Exit

### During Game
- **H** - Hit (draw another card)
- **S** - Stand (end your turn)
- **Space** - Start new round
- **ESC** - Return to main menu

## MVC Architecture Explanation

### Model (models/)
- **Entity**: Base class for all game objects with unique IDs and active states
- **Card**: Represents a playing card with suit and rank
- **Deck**: Manages a 52-card deck with shuffling
- **Hand**: Represents a player's or dealer's hand with Blackjack value calculation
- **GameModel**: Main game state manager handling game logic
- **MenuModel**: Manages main menu state and navigation
- **SaveData**: Structure for serializing game state
- **SaveManager**: Handles file I/O for save/load operations

### View (views/)
- **View**: Base class for all rendering components
- **GameView**: Renders the game table, cards, UI elements, and messages
- **MenuView**: Renders the main menu with selection highlighting

### Controller (controllers/)
- **Controller**: Base class for input handling
- **GameController**: Manages keyboard input during gameplay
- **MenuController**: Manages menu navigation and selection

### Core (core/)
- **Game**: Singleton managing the main game loop and coordinating all components
- **Entity**: Base class providing common functionality

## Game Rules Implemented

1. **Card Values**: Number cards (2-10) face value, Face cards (J, Q, K) = 10, Ace = 1 or 11
2. **Blackjack**: Ace + 10-value card on initial deal = automatic win (unless dealer also has Blackjack)
3. **Dealer Rules**: Dealer must hit on 16 or less, stand on 17 or more
4. **Bust**: Exceeding 21 results in automatic loss
5. **Push**: Tie game results in bet return (no wins/losses)
6. **Deck Management**: Automatic reshuffle when cards remaining < 15

## Save System

The game features a comprehensive save system:

- **5 Save Slots**: Each game state can be saved to any of 5 slots
- **Auto-save**: Automatically saves after each completed round to slot 1
- **Timestamp Display**: Each save slot shows when it was last saved
- **Progress Saving**: Saves in-progress games with current hands
- **Statistics**: Tracks wins, losses, and pushes across sessions

## Extending the Framework

This framework is designed for easy extension. To add new features:

1. **New Game Elements**: Create new Model classes inheriting from `Model`
2. **New Visual Elements**: Create new View classes inheriting from `View`
3. **New Interactions**: Create new Controller classes or extend existing ones

## License

This project is for educational purposes. Raylib is licensed under the zlib/libpng license.
