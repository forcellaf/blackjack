# Blackjack Game - Architecture Documentation

## Table of Contents

1. [Overview](#overview)
2. [MVC Architecture](#mvc-architecture)
3. [Application State Management](#application-state-management)
4. [Object-Oriented Design](#object-oriented-design)
5. [Component Breakdown](#component-breakdown)
6. [Class Hierarchy](#class-hierarchy)
7. [Design Patterns](#design-patterns)
8. [Game Flow](#game-flow)
9. [Save/Load System](#saveload-system)
10. [Menu System](#menu-system)
11. [Extension Guidelines](#extension-guidelines)

---

## Overview

This Blackjack game is built using C++ with the **Model-View-Controller (MVC)** architectural pattern and **Object-Oriented Programming (OOP)** principles. The game uses the **raylib** library for graphics and input handling.

### Key Features

- **Clean Separation of Concerns**: MVC pattern ensures models, views, and controllers are decoupled
- **Reusable Components**: Base classes provide common functionality for extensibility
- **Type Safety**: Strong typing with enums for game states and card properties
- **Memory Management**: Smart pointers (`std::shared_ptr`) for automatic memory management
- **Single Responsibility**: Each class has a single, well-defined purpose
- **Persistent State**: Save/load system with multiple save slots
- **Main Menu**: User-friendly menu navigation system

---

## MVC Architecture

### What is MVC?

The Model-View-Controller pattern divides an application into three interconnected components:

1. **Model**: Manages data, state, and business logic
2. **View**: Handles rendering and visual presentation
3. **Controller**: Processes user input and coordinates Model and View

### MVC in This Application

```
┌─────────────────────────────────────────────────────────────┐
│                         Game (Singleton)                     │
│                                                              │
│  ┌──────────────────┐  ┌──────────────────┐  ┌───────────┐ │
│  │ MenuModel        │  │   MenuView       │  │MenuCtrlr  │ │
│  ├──────────────────┤  ├──────────────────┤  ├───────────┤ │
│  │ GameModel        │  │   GameView       │  │GameCtrlr  │ │
│  └──────────────────┘  └──────────────────┘  └───────────┘ │
└─────────────────────────────────────────────────────────────┘
```

### Data Flow

```
User Input → Controller → Model Updates → View Renders → Display
     ↑                                                        │
     └────────────────────────────────────────────────────────┘
                    (Loop continues)
```

1. **Controller** receives keyboard input (Menu: arrows, Enter; Game: H, S, SPACE)
2. **Controller** calls appropriate **Model** methods
3. **Model** updates game state
4. **Game** loop triggers **View** to render current state
5. **View** draws UI elements to screen

---

## Application State Management

The game manages two distinct application states through the `AppState` enum:

```cpp
enum class AppState {
    MENU,   // Main menu navigation
    GAME,   // Active gameplay
    QUIT    // Application exit
};
```

### State Transitions

- **MENU → GAME**: User selects "New Game" or loads a saved game
- **GAME → MENU**: User presses ESC during gameplay
- **MENU/GAME → QUIT**: User selects "Quit" from menu

The `Game` class provides `switchToMenu()` and `switchToGame()` methods to handle component activation/deactivation during state transitions.

---

## Object-Oriented Design

### Core OOP Concepts Used

#### 1. Encapsulation

Each class encapsulates its data and provides controlled access through methods:

```cpp
class Card : public core::Entity {
private:
    Suit m_suit;      // Encapsulated suit data
    Rank m_rank;      // Encapsulated rank data

public:
    Suit getSuit() const { return m_suit; }  // Controlled access
    int getValue() const;                    // Computed value
};
```

#### 2. Inheritance

Base classes provide common functionality inherited by derived classes:

```
Entity (base)
    ├── Model (abstract base)
    │   ├── Deck
    │   ├── Hand
    │   ├── GameModel
    │   ├── MenuModel
    │   ├── SaveManager
    │   └── SaveData (struct)
    ├── View (abstract base)
    │   ├── GameView
    │   └── MenuView
    └── Controller (abstract base)
        ├── GameController
        └── MenuController
```

#### 3. Polymorphism

Virtual functions allow derived classes to provide specific implementations:

```cpp
class Model : public core::Entity {
public:
    virtual void init() {}           // Base implementation
    virtual void update(float deltaTime) override {}
};

class GameModel : public Model {
public:
    void init() override {           // Custom implementation
        m_deck->init();
        reset();
    }
};
```

#### 4. Abstraction

Abstract base classes define interfaces without implementation details:

```cpp
class View : public core::Entity {
public:
    virtual void render() = 0;       // Pure virtual - must be implemented
};
```

---

## Component Breakdown

### Core Components

#### Entity (`include/core/Entity.hpp`)

**Purpose**: Base class for all game objects

**Responsibilities**:
- Unique identification (ID generation)
- Name management
- Active state tracking

**Key Features**:
```cpp
class Entity {
    unsigned int m_id;        // Unique identifier
    std::string m_name;      // Descriptive name
    bool m_active;           // Enable/disable state
};
```

#### Game (`include/core/Game.hpp`)

**Purpose**: Singleton managing the main game loop

**Responsibilities**:
- Window initialization and management
- Component registration (models, views, controllers)
- Main game loop coordination
- Application state management
- Delta time calculation

**Key Methods**:
- `init()` - Initialize window and all components
- `run()` - Main game loop
- `update()` - Update all components
- `render()` - Render all views
- `shutdown()` - Clean up resources
- `switchToMenu()` - Switch to menu state
- `switchToGame()` - Switch to game state

---

### Model Components

#### Model (`include/models/Model.hpp`)

**Purpose**: Abstract base for all models

**Responsibilities**:
- Define model interface
- Provide default implementations

#### Card (`include/models/Card.hpp`)

**Purpose**: Represent a single playing card

**Responsibilities**:
- Store suit and rank
- Calculate card value (face cards = 10, Ace = 11)
- Provide display strings

**Enums**:
```cpp
enum class Suit { HEARTS, DIAMONDS, CLUBS, SPADES };
enum class Rank {
    TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
    JACK = 11, QUEEN = 12, KING = 13, ACE = 14
};
```

#### Deck (`include/models/Deck.hpp`)

**Purpose**: Manage a standard 52-card deck

**Key Methods**:
```cpp
void shuffle();                       // Randomize card order
std::shared_ptr<Card> drawCard();    // Remove and return top card
void reset();                         // Rebuild and reshuffle
```

#### Hand (`include/models/Hand.hpp`)

**Purpose**: Manage a player's or dealer's hand

**Detection Methods**:
- `isBusted()` - Value exceeds 21
- `isBlackjack()` - Exactly 21 with 2 cards
- `isSoft()` - Hand contains an Ace counted as 11

#### GameModel (`include/models/GameModel.hpp`)

**Purpose**: Manage overall game state and logic

**Game States**:
```cpp
enum class GameState {
    BETTING,            // Waiting to start
    PLAYER_TURN,        // Player choosing hit/stand
    DEALER_TURN,        // Dealer playing
    BUSTED,             // Player exceeded 21
    PLAYER_BLACKJACK,   // Player has 21 with 2 cards
    DEALER_BLACKJACK,   // Dealer has 21 with 2 cards
    PLAYER_WIN,         // Player wins
    DEALER_WIN,         // Dealer wins
    PUSH                // Tie game
};
```

**Key Methods**:
- `startNewRound()` - Deal initial cards
- `playerHit()` - Add card to player's hand
- `playerStand()` - End player's turn
- `dealerPlay()` - Dealer plays (hits to 17)
- `determineWinner()` - Calculate round result
- `saveGame(int slot)` - Save current game state
- `loadGame(int slot)` - Load game from slot
- `getWins()`, `getLosses()`, `getPushes()` - Statistics getters
- `getWinRate()` - Calculate win percentage

#### MenuModel (`include/models/MenuModel.hpp`)

**Purpose**: Manage main menu state and navigation

**Menu States**:
```cpp
enum class MenuState {
    MAIN_MENU,         // Main menu options
    SAVE_SLOT_SELECT,  // Selecting save slot
    LOAD_SLOT_SELECT,  // Selecting load slot
    SETTINGS,          // Settings menu
    NONE               // No active menu
};
```

**Menu Options**:
```cpp
enum class MenuOption {
    NEW_GAME,
    LOAD_GAME,
    SAVE_GAME,
    SETTINGS,
    QUIT
};
```

**Key Methods**:
- `navigateUp()`, `navigateDown()` - Move selection
- `selectOption()` - Process selection
- `goBack()` - Return to previous menu
- `getSaveSlotInfo()` - Get save slot metadata

#### SaveManager (`include/models/SaveManager.hpp`)

**Purpose**: Handle file I/O for save/load operations

**Key Features**:
- Support for 5 save slots
- Auto-save functionality
- Save slot validation
- Timestamp tracking

**Key Methods**:
```cpp
bool saveToSlot(int slot, const SaveData& data);
bool loadFromSlot(int slot, SaveData& data);
bool slotExists(int slot) const;
bool autoSave(const SaveData& data);
std::vector<SaveData> getAllSlotInfo() const;
```

#### SaveData (`include/models/SaveData.hpp`)

**Purpose**: Structure for serializing game state

**Data Structure**:
```cpp
struct SaveData {
    int version;              // Save format version
    std::time_t saveTime;     // Timestamp
    int wins, losses, pushes; // Statistics
    bool inProgress;          // Game in progress flag
    SerializedHand playerHand; // Player's cards
    SerializedHand dealerHand; // Dealer's cards
    int deckCardCount;         // Remaining cards

    std::string toJSON() const;
    static SaveData fromJSON(const std::string& json);
};
```

---

### View Components

#### View (`include/views/View.hpp`)

**Purpose**: Abstract base for all views

**Responsibilities**:
- Define view interface
- Provide update hook for animations

#### GameView (`include/views/GameView.hpp`)

**Purpose**: Render the Blackjack game

**Rendering Hierarchy**:
```
render()
├── renderTable()           // Background and border
├── renderHand(dealer)      // Dealer's cards (first card hidden)
├── renderHand(player)      // Player's cards
├── renderUI()              // Score panel
├── renderMessage()         // Game status message
└── renderControls()        // Controls help
```

#### MenuView (`include/views/MenuView.hpp`)

**Purpose**: Render the main menu

**Rendering Hierarchy**:
```
render()
├── renderBackground()      // Felt green with decorative cards
├── renderTitle()           // "BLACKJACK" title with gold effect
├── renderOptions()         // Menu options with selection
└── renderFooter()          // Control hints
```

---

### Controller Components

#### Controller (`include/controllers/Controller.hpp`)

**Purpose**: Abstract base for all controllers

**Responsibilities**:
- Define controller interface
- Provide update hook

#### GameController (`include/controllers/GameController.hpp`)

**Purpose**: Handle keyboard input during gameplay

**Input Mapping**:
```
┌─────────────────┬──────────────────────────────┐
│ Game State      │ Valid Keys                   │
├─────────────────┼──────────────────────────────┤
│ BETTING         │ SPACE → Start new round      │
│ PLAYER_TURN     │ H → Hit, S → Stand           │
│ GAME_OVER       │ SPACE → New round            │
└─────────────────┴──────────────────────────────┘
```

#### MenuController (`include/controllers/MenuController.hpp`)

**Purpose**: Handle menu navigation input

**Input Mapping**:
```
┌─────────────────┬──────────────────────────────┐
│ Action          │ Keys                         │
├─────────────────┼──────────────────────────────┤
│ Navigate        │ Arrow Up/Down                │
│ Select          │ Enter                        │
│ Go Back         │ ESC                          │
│ Return to Menu  │ ESC (during game)            │
└─────────────────┴──────────────────────────────┘
```

**Key Methods**:
- `shouldStartNewGame()` - Check if new game requested
- `shouldQuit()` - Check if exit requested
- `shouldLoadGame()` - Check if load requested
- `getSelectedSlot()` - Get selected save slot

---

## Class Hierarchy

```
Entity
│
├── Model
│   ├── Deck
│   ├── Hand
│   ├── GameModel
│   ├── MenuModel
│   └── SaveManager
│
├── View
│   ├── GameView
│   └── MenuView
│
└── Controller
    ├── GameController
    └── MenuController

Card (independent class, used by Deck and Hand)
SaveData (independent struct, used by SaveManager)
```

---

## Design Patterns

### 1. Singleton Pattern

**Game** class uses singleton pattern to ensure only one game instance exists.

### 2. Observer Pattern (Implicit)

Views observe Models through the Game loop.

### 3. State Pattern

**Application States**: MENU, GAME, QUIT
**Game States**: BETTING, PLAYER_TURN, DEALER_TURN, etc.
**Menu States**: MAIN_MENU, SAVE_SLOT_SELECT, etc.

### 4. Strategy Pattern (Implicit)

Different controllers handle input differently based on application state.

### 5. Template Method Pattern

Base classes define algorithm structure, derived classes implement specifics.

---

## Game Flow

### Application Startup Sequence

```
1. main() starts
   ↓
2. Create all MVC components (menu and game)
   ↓
3. Initialize game with Game::getInstance()
   ↓
4. Switch to MENU state
   ↓
5. Enter main loop
```

### Main Menu Flow

```
┌─────────────────────────────────────┐
│           MAIN MENU                 │
│  ┌───────────────────────────────┐ │
│  │  New Game  ←──────────────────│ │
│  │  Load Game                    │ │
│  │  Save Game                    │ │
│  │  Settings                     │ │
│  │  Quit                         │ │
│  └───────────────────────────────┘ │
└─────────────────────────────────────┘
           │
    ┌──────┴──────┐
    ▼             ▼
New Game      Load Game
    │             │
    ▼             ▼
Reset &    Load from
  Start     Save Slot
    │             │
    └──────┬──────┘
           ▼
      GAME STATE
```

### Gameplay Sequence

```
┌─────────────────────────────────────────────────────────┐
│                    BETTING STATE                        │
│  User presses SPACE                                     │
└──────────────────────┬──────────────────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────────────────┐
│              DEAL INITIAL CARDS                         │
│  Player: 2 cards  Dealer: 2 cards (1 hidden)           │
│  Check for Blackjacks                                   │
└──────────────────────┬──────────────────────────────────┘
                       │
            ┌──────────┴──────────┐
            ▼                     ▼
    No Blackjack          Blackjack Detected
            │                     │
            ▼                     ▼
┌─────────────────────┐   ┌─────────────────────┐
│   PLAYER_TURN       │   │   GAME_OVER         │
│  User: H or S       │   │  Show result        │
└──────────┬──────────┘   └─────────────────────┘
           │
    ┌──────┴──────┐
    ▼             ▼
┌─────────┐  ┌─────────┐
│  HIT    │  │ STAND   │
└────┬────┘  └────┬────┘
     │            │
     ▼            ▼
  Add card    End turn
     │            │
     └────┬───────┘
          │
          ▼
  Check for bust
     │
  ┌───┴───┐
  ▼       ▼
Bust    Continue
 │         │
 ▼         ▼
GAME_OVER DEALER_TURN
 │         │
 │         Dealer plays to 17+
 │         │
 └─────────┼───────────┐
           ▼           ▼
     determineWinner()
           │
           ▼
      GAME_OVER
      Show result
      Auto-save
```

### Return to Menu

```
┌─────────────────┐
│  Playing Game   │
│                 │
│  Press ESC      │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│  Switch to      │
│  MENU state     │
│                 │
│  Show Main Menu │
└─────────────────┘
```

---

## Save/Load System

### Save Data Structure

Each save file contains:
- **Version**: Save format version for compatibility
- **Timestamp**: When the save was created
- **Statistics**: Wins, losses, pushes
- **Game State**: Whether a game is in progress
- **Player Hand**: Serialized card data
- **Dealer Hand**: Serialized card data
- **Deck State**: Number of remaining cards

### Save Operations

1. **Manual Save**: User selects "Save Game" from menu
2. **Auto-Save**: Automatically saves after each completed round to slot 1
3. **Quick Save**: Can be bound to a key (future enhancement)

### Load Operations

1. **Menu Load**: User selects "Load Game" from menu
2. **Slot Selection**: User chooses which save slot to load
3. **State Restoration**: Game restores cards, statistics, and deck state

### File Format

Saves are stored as JSON files in the `saves/` directory:
```
saves/
├── save_slot_1.json
├── save_slot_2.json
├── save_slot_3.json
├── save_slot_4.json
└── save_slot_5.json
```

---

## Menu System

### Menu Navigation

The menu system supports nested navigation:

```
Main Menu
├── New Game → Starts game
├── Load Game → Save Slot Select → Load from slot
├── Save Game → Save Slot Select → Save to slot
├── Settings → Settings Menu (future)
└── Quit → Exit application
```

### Visual Design

- **Background**: Felt green with decorative card patterns
- **Title**: Gold "BLACKJACK" with shadow effect
- **Selection**: Highlighted with golden border and glow
- **Indicators**: Arrow pointer for selected item
- **Footer**: Control hints at bottom

---

## Extension Guidelines

### Adding New Menu Options

1. **Update MenuOption enum**:
```cpp
enum class MenuOption {
    NEW_GAME,
    LOAD_GAME,
    SAVE_GAME,
    SETTINGS,
    MY_NEW_FEATURE,  // Add here
    QUIT
};
```

2. **Update MenuModel**:
```cpp
std::vector<std::string> MenuModel::getMainMenuOptions() const {
    return {
        "New Game",
        "Load Game",
        "Save Game",
        "Settings",
        "My New Feature",  // Add here
        "Quit"
    };
}
```

3. **Handle in MenuController**:
```cpp
void MenuController::executeMainMenuSelection() {
    switch (selectedOption) {
        // ... existing cases ...
        case MenuOption::MY_NEW_FEATURE:
            // Handle new feature
            break;
    }
}
```

### Adding New Save Data

1. **Add to SaveData structure**:
```cpp
struct SaveData {
    // ... existing fields ...
    int myNewData;  // Add here
};
```

2. **Update serialization**:
```cpp
std::string SaveData::toJSON() const {
    // ... existing code ...
    json << "  \"myNewData\": " << myNewData << ",\n";
}
```

3. **Load from save**:
```cpp
SaveData SaveData::fromJSON(const std::string& json) {
    // Parse myNewData from JSON
}
```

---

## Technical Details

### Build System

**Windows (build.bat)**:
```batch
1. Build raylib library with gcc (C99)
2. Compile game sources with g++ (C++17)
3. Link with raylib static library
```

**Linux/macOS (build.sh)**:
```bash
1. Compile raylib C files
2. Create static library
3. Compile and link game
```

### Compiler Flags

**Raylib (C)**:
```bash
gcc -c -std=c99 -w -O2 -DPLATFORM_DESKTOP
```

**Game (C++)**:
```bash
g++ -c -std=c++17 -w -O2
```

### Memory Management

**Smart Pointers Used**:
```cpp
std::shared_ptr<Deck> m_deck;           // Shared ownership
std::shared_ptr<Card> drawCard();       // Transfer ownership
```

### Thread Safety

**Current Implementation**: Single-threaded

---

## Conclusion

This Blackjack game demonstrates a clean, maintainable architecture using:

- **MVC Pattern**: Clear separation of concerns
- **OOP Principles**: Encapsulation, inheritance, polymorphism
- **Design Patterns**: Singleton, State, Strategy, Template Method
- **Modern C++**: Smart pointers, enums, standard library
- **Persistent State**: Save/load system with file I/O
- **User Interface**: Main menu with navigation

The architecture is designed to be:
1. **Understandable**: Clear naming and organization
2. **Extensible**: Easy to add new features
3. **Maintainable**: Modular and loosely coupled
4. **Reusable**: Base classes can be used for other games

---

**Document Version**: 2.0
**Last Updated**: June 3, 2026
**Project**: Blackjack Game with Raylib
**Language**: C++17
