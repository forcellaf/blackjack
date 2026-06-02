# Blackjack Game - MVC Framework with Raylib

A fully functional Blackjack game built with C++ using the MVC (Model-View-Controller) architectural pattern and Object-Oriented Programming principles.

## Features

- **MVC Architecture**: Clean separation of concerns with Models, Views, and Controllers
- **Object-Oriented Design**: Full OOP implementation with inheritance, polymorphism, and encapsulation
- **Raylib Graphics**: Smooth rendering with raylib game library
- **Complete Blackjack Rules**:
  - Hit and Stand actions
  - Blackjack detection
  - Dealer AI (hits on 16 or less, stands on 17+)
  - Automatic shuffling when deck is low
  - Push detection for ties

## Project Structure

```
blackjack_cpp/
├── CMakeLists.txt           # CMake build configuration
├── README.md                # This file
├── include/
│   ├── core/
│   │   ├── Entity.hpp      # Base class for all game entities
│   │   └── Game.hpp        # Main game class managing game loop
│   ├── models/
│   │   ├── Model.hpp       # Base class for all models
│   │   ├── Card.hpp        # Playing card representation
│   │   ├── Deck.hpp        # Card deck management
│   │   ├── Hand.hpp        # Player/dealer hand
│   │   └── GameModel.hpp   # Main game model
│   ├── views/
│   │   ├── View.hpp        # Base class for all views
│   │   └── GameView.hpp    # Game rendering view
│   └── controllers/
│       ├── Controller.hpp  # Base class for all controllers
│       └── GameController.hpp # Input handling controller
└── src/
    ├── core/
    │   ├── Game.cpp        # Game implementation
    │   └── Entity.cpp      # Entity static member initialization
    ├── models/
    │   ├── Card.cpp        # Card implementation
    │   ├── Deck.cpp        # Deck implementation
    │   ├── Hand.cpp        # Hand implementation
    │   └── GameModel.cpp   # Game model implementation
    ├── views/
    │   └── GameView.cpp    # Game view implementation
    ├── controllers/
    │   └── GameController.cpp # Controller implementation
    └── main.cpp            # Entry point
```

## Setup Instructions

### Prerequisites

- CMake 3.10 or higher
- C++17 compatible compiler (GCC, Clang, or MSVC)
- Git (for cloning raylib)

### Building on Windows

1. Clone raylib into the external directory:
```bash
cd external
git clone https://github.com/raysan5/raylib.git
```

2. Create a build directory:
```bash
cd ..
mkdir build
cd build
```

3. Generate build files with CMake:
```bash
cmake ..
```

4. Build the project:
```bash
cmake --build . --config Release
```

5. Run the game:
```bash
cd Release
raylib_game.exe
```

### Building on Linux/macOS

1. Clone raylib into the external directory:
```bash
cd external
git clone https://github.com/raysan5/raylib.git
```

2. Create and enter build directory:
```bash
cd ..
mkdir build
cd build
```

3. Generate and build:
```bash
cmake ..
make
```

4. Run the game:
```bash
./RaylibGame
```

## Game Controls

- **SPACE** - Start a new round / Continue after game over
- **H** - Hit (draw another card)
- **S** - Stand (end your turn)
- **ESC** - Exit game

## MVC Architecture Explanation

### Model (models/)
- **Entity**: Base class for all game objects with unique IDs and active states
- **Card**: Represents a playing card with suit and rank
- **Deck**: Manages a 52-card deck with shuffling
- **Hand**: Represents a player's or dealer's hand with Blackjack value calculation
- **GameModel**: Main game state manager handling game logic

### View (views/)
- **View**: Base class for all rendering components
- **GameView**: Renders the game table, cards, UI elements, and messages

### Controller (controllers/)
- **Controller**: Base class for input handling
- **GameController**: Manages keyboard input and game state transitions

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

## Extending the Framework

This framework is designed for easy extension. To add new features:

1. **New Game Elements**: Create new Model classes inheriting from `Model`
2. **New Visual Elements**: Create new View classes inheriting from `View`
3. **New Interactions**: Create new Controller classes or extend existing ones

## License

This project is for educational purposes. Raylib is licensed under the zlib/libpng license.
