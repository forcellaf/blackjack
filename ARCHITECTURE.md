# Blackjack Game - Architecture Documentation

## Table of Contents

1. [Overview](#overview)
2. [MVC Architecture](#mvc-architecture)
3. [Object-Oriented Design](#object-oriented-design)
4. [Component Breakdown](#component-breakdown)
5. [Class Hierarchy](#class-hierarchy)
6. [Design Patterns](#design-patterns)
7. [Game Flow](#game-flow)
8. [Extension Guidelines](#extension-guidelines)

---

## Overview

This Blackjack game is built using C++ with the **Model-View-Controller (MVC)** architectural pattern and **Object-Oriented Programming (OOP)** principles. The game uses the **raylib** library for graphics and input handling.

### Key Features

- **Clean Separation of Concerns**: MVC pattern ensures models, views, and controllers are decoupled
- **Reusable Components**: Base classes provide common functionality for extensibility
- **Type Safety**: Strong typing with enums for game states and card properties
- **Memory Management**: Smart pointers (`std::shared_ptr`) for automatic memory management
- **Single Responsibility**: Each class has a single, well-defined purpose

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
│  ┌───────────────┐  ┌───────────────┐  ┌───────────────┐  │
│  │    Model      │  │     View      │  │  Controller    │  │
│  │  (GameModel)  │  │  (GameView)   │  │(GameController)│  │
│  └───────────────┘  └───────────────┘  └───────────────┘  │
└─────────────────────────────────────────────────────────────┘
```

### Data Flow

```
User Input → Controller → Model Updates → View Renders → Display
     ↑                                                        │
     └────────────────────────────────────────────────────────┘
                    (Loop continues)
```

1. **Controller** receives keyboard input (H, S, SPACE)
2. **Controller** calls appropriate **Model** methods (`playerHit()`, `playerStand()`)
3. **Model** updates game state (card values, game status)
4. **Game** loop triggers **View** to render current state
5. **View** draws cards, UI, and messages to screen

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
    │   └── GameModel
    ├── View (abstract base)
    │   └── GameView
    └── Controller (abstract base)
        └── GameController
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
- Delta time calculation

**Key Methods**:
- `init()` - Initialize window and all components
- `run()` - Main game loop
- `update()` - Update all components
- `render()` - Render all views
- `shutdown()` - Clean up resources

**Usage**:
```cpp
auto& game = Game::getInstance();
game.init(1024, 768, "Blackjack");
game.addModel(gameModel);
game.addView(gameView);
game.addController(gameController);
game.run();
```

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

**Special Behavior**:
- Face cards (J, Q, K) return value 10
- Ace returns value 11 (Hand class handles 1/11 adjustment)

#### Deck (`include/models/Deck.hpp`)

**Purpose**: Manage a standard 52-card deck

**Responsibilities**:
- Create full 52-card deck
- Shuffle using Fisher-Yates algorithm
- Deal cards
- Track remaining cards

**Key Methods**:
```cpp
void shuffle();                       // Randomize card order
std::shared_ptr<Card> drawCard();    // Remove and return top card
void reset();                         // Rebuild and reshuffle
```

#### Hand (`include/models/Hand.hpp`)

**Purpose**: Manage a player's or dealer's hand

**Responsibilities**:
- Store collection of cards
- Calculate hand value following Blackjack rules
- Detect Blackjack and bust conditions

**Blackjack Rules Implemented**:
```cpp
int getValue() const {
    int value = sumAllCards();        // Sum card values
    int aceCount = countAces();

    // Adjust for aces: count as 1 instead of 11 if busting
    while (value > 21 && aceCount > 0) {
        value -= 10;                  // Convert Ace from 11 to 1
        aceCount--;
    }
    return value;
}
```

**Detection Methods**:
- `isBusted()` - Value exceeds 21
- `isBlackjack()` - Exactly 21 with 2 cards
- `isSoft()` - Hand contains an Ace counted as 11

#### GameModel (`include/models/GameModel.hpp`)

**Purpose**: Manage overall game state and logic

**Responsibilities**:
- Track game state (betting, playing, game over)
- Manage player and dealer hands
- Implement Blackjack game rules
- Determine winners

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

### View Components

#### View (`include/views/View.hpp`)

**Purpose**: Abstract base for all views

**Responsibilities**:
- Define view interface
- Provide update hook for animations

#### GameView (`include/views/GameView.hpp`)

**Purpose**: Render the Blackjack game

**Responsibilities**:
- Draw game table (felt green background)
- Render cards with suits and colors
- Display player/dealer hands
- Show scores and messages
- Draw controls panel

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

**Card Rendering**:
- Red cards: Hearts (♥) and Diamonds (♦)
- Black cards: Clubs (♣) and Spades (♠)
- Hidden card: Show back pattern

### Controller Components

#### Controller (`include/controllers/Controller.hpp`)

**Purpose**: Abstract base for all controllers

**Responsibilities**:
- Define controller interface
- Provide update hook

#### GameController (`include/controllers/GameController.hpp`)

**Purpose**: Handle keyboard input

**Responsibilities**:
- Process key presses based on game state
- Call appropriate Model methods
- Manage state transitions

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

---

## Class Hierarchy

```
Entity
│
├── Model
│   ├── Deck
│   ├── Hand
│   └── GameModel
│
├── View
│   └── GameView
│
└── Controller
    └── GameController

Card (independent class, used by Deck and Hand)
```

### Class Relationships

```
┌─────────────┐       uses        ┌─────────────┐
│ GameModel   │──────────────────>│     Deck    │
└─────────────┘                   └─────────────┘
       │                                  │
       │ contains                         │ contains
       ▼                                  ▼
┌─────────────┐                   ┌─────────────┐
│    Hand     │<──────────────────│    Card     │
└─────────────┘   (shared_ptr)    └─────────────┘
       ▲
       │           observes
       │                   ┌─────────────┐
       └──────────────────│  GameView   │
                           └─────────────┘
                                  ▲
                                  │
                    ┌─────────────┴─────────────┐
                    │       GameController       │
                    └───────────────────────────┘
```

---

## Design Patterns

### 1. Singleton Pattern

**Game** class uses singleton pattern to ensure only one game instance exists:

```cpp
class Game {
public:
    static Game& getInstance() {
        static Game instance;
        return instance;
    }
private:
    Game() = default;
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
};
```

**Benefits**:
- Single point of access for game functionality
- Prevents multiple window creation
- Simplifies global state management

### 2. Observer Pattern (Implicit)

Views observe Models through the Game loop:

```cpp
void Game::render() {
    for (auto& view : m_views) {
        if (view->isActive()) {
            view->render();  // View reads current Model state
        }
    }
}
```

### 3. Strategy Pattern (Implicit)

Different strategies for different game states:

```cpp
void GameController::handleKeyPress(int key) {
    switch (m_model->getState()) {
        case GameState::BETTING:
            processBettingState(key);
            break;
        case GameState::PLAYER_TURN:
            processPlayerTurn(key);
            break;
        // ...
    }
}
```

### 4. Template Method Pattern

Base classes define algorithm structure, derived classes implement specifics:

```cpp
// Base class defines template
class View {
public:
    virtual void init() {}     // Hook for subclasses
    virtual void render() = 0; // Must implement
};

// Derived class implements
class GameView : public View {
public:
    void init() override {
        // Setup view resources
    }
    void render() override {
        // Render specific content
    }
};
```

---

## Game Flow

### Initialization Sequence

```
1. main() starts
   ↓
2. Game::getInstance() called
   ↓
3. game.init(width, height, title)
   ├── InitWindow() (raylib)
   ├── Create GameModel
   ├── Create GameView
   ├── Create GameController
   └── Call init() on each component
   ↓
4. game.run() enters main loop
```

### Main Game Loop

```
while (!WindowShouldClose() && running) {
    deltaTime = GetFrameTime();

    // 1. Handle Input
    for each controller:
        controller.handleInput()
        controller.update(deltaTime)

    // 2. Update Models
    for each model:
        model.update(deltaTime)

    // 3. Update Views (animations)
    for each view:
        view.update(deltaTime)

    // 4. Render
    BeginDrawing()
    ClearBackground()
    for each view:
        view.render()
    EndDrawing()
}
```

### Round Sequence

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
      Wait for SPACE
```

---

## Extension Guidelines

### Adding New Card Games

1. **Create new Model classes**:
```cpp
class PokerModel : public Model {
    // Poker-specific game logic
};
```

2. **Create new View classes**:
```cpp
class PokerView : public View {
    void render() override {
        // Poker-specific rendering
    }
};
```

3. **Create new Controller classes**:
```cpp
class PokerController : public Controller {
    void handleInput() override {
        // Poker-specific input handling
    }
};
```

4. **Register with Game**:
```cpp
auto pokerModel = std::make_shared<PokerModel>();
auto pokerView = std::make_shared<PokerView>(pokerModel);
auto pokerController = std::make_shared<PokerController>(pokerModel);

game.addModel(pokerModel);
game.addView(pokerView);
game.addController(pokerController);
```

### Adding Features to Blackjack

**Add betting system:**
```cpp
class GameModel {
private:
    int m_balance;
    int m_currentBet;

public:
    void placeBet(int amount);
    void payout(GameState result);
};
```

**Add card counting statistics:**
```cpp
class GameModel {
private:
    std::map<Rank, int> m_cardsSeen;

public:
    float getTrueCount();
    float getRunningCount();
};
```

**Add animations:**
```cpp
class GameView : public View {
private:
    float m_cardAnimationProgress;

public:
    void update(float deltaTime) override {
        m_cardAnimationProgress += deltaTime * 2.0f;
    }

    void renderCard(std::shared_ptr<Card> card, int x, int y) {
        int animatedX = lerp(startX, endX, m_cardAnimationProgress);
        // Render at animated position
    }
};
```

### Adding Sound Effects

1. **Create SoundManager class**:
```cpp
class SoundManager : public Entity {
private:
    Sound m_cardFlipSound;
    Sound m_chipSound;

public:
    void init() override;
    void playCardFlip();
    void playChipSound();
};
```

2. **Integrate with Game**:
```cpp
class GameModel {
    void playerHit() {
        m_soundManager->playCardFlip();
        m_playerHand->addCard(m_deck->drawCard());
    }
};
```

### Adding Multiplayer

1. **Create NetworkManager**:
```cpp
class NetworkManager : public Entity {
public:
    void sendGameState(const GameState& state);
    GameState receiveOpponentMove();
};
```

2. **Extend GameModel**:
```cpp
class GameModel {
private:
    bool m_isMultiplayer;
    std::shared_ptr<NetworkManager> m_network;

public:
    void playerHit() {
        // Local game
        if (!m_isMultiplayer) {
            m_playerHand->addCard(m_deck->drawCard());
        }
        // Network game
        else {
            m_network->sendMove(HIT);
        }
    }
};
```

---

## Technical Details

### Memory Management

**Smart Pointers Used**:
```cpp
std::shared_ptr<Deck> m_deck;           // Shared ownership
std::shared_ptr<Card> drawCard();       // Transfer ownership
```

**Benefits**:
- Automatic memory cleanup
- No manual delete needed
- Reference counting for shared resources

### Thread Safety

**Current Implementation**: Single-threaded

**Future Enhancement**:
```cpp
class Game {
private:
    std::mutex m_stateMutex;

public:
    void update() {
        std::lock_guard<std::mutex> lock(m_stateMutex);
        // Update game state
    }
};
```

### Performance Considerations

**Optimization Techniques Used**:
1. **Object Pooling** (potential enhancement):
```cpp
class CardPool {
    std::vector<std::shared_ptr<Card>> m_availableCards;
public:
    std::shared_ptr<Card> acquire();
    void release(std::shared_ptr<Card> card);
};
```

2. **Batch Rendering** (potential enhancement):
```cpp
void GameView::render() {
    // Collect all draw commands
    // Sort by texture/depth
    // Batch similar draws
}
```

---

## Build System

### Compilation Structure

```
external/raylib/src/*.c     → obj_raylib/*.o     (C files)
src/**/*.cpp                → obj_game/*.o       (C++ files)
                             ↓
                         Linking
                             ↓
                      RaylibGame.exe
```

### Compiler Flags

**Raylib (C)**:
```bash
gcc -c -std=c11 -w -O2 \
    -Iexternal/raylib/src \
    -Iexternal/raylib/src/external/glfw/include \
    -DPLATFORM_DESKTOP -DPLATFORM_WINDOWS
```

**Game (C++)**:
```bash
g++ -c -std=c++17 -w -O2 \
    -Iinclude -Iexternal/raylib/src
```

**Linking**:
```bash
g++ -std=c++17 -o RaylibGame.exe \
    obj_game/*.o obj_raylib/*.o \
    -lopengl32 -lgdi32 -lwinmm
```

---

## Conclusion

This Blackjack game demonstrates a clean, maintainable architecture using:

- **MVC Pattern**: Clear separation of concerns
- **OOP Principles**: Encapsulation, inheritance, polymorphism
- **Design Patterns**: Singleton, Template Method, Strategy
- **Modern C++**: Smart pointers, enums, standard library

The architecture is designed to be:
1. **Understandable**: Clear naming and organization
2. **Extensible**: Easy to add new features
3. **Maintainable**: Modular and loosely coupled
4. **Reusable**: Base classes can be used for other games

---

**Document Version**: 1.0
**Last Updated**: June 2, 2026
**Project**: Blackjack Game with Raylib
**Language**: C++17
