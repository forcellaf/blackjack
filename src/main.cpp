#include "core/Game.hpp"
#include "models/GameModel.hpp"
#include "models/MenuModel.hpp"
#include "views/GameView.hpp"
#include "views/MenuView.hpp"
#include "controllers/GameController.hpp"
#include "controllers/MenuController.hpp"
#include "raylib.h"
#include <memory>
#include <iostream>

using namespace game;

int main() {
    try {
        // Get game instance
        auto& game = core::Game::getInstance();

        // Initialize the game
        const int screenWidth = 1024;
        const int screenHeight = 768;
        const std::string gameTitle = "Blackjack - MVC Framework";

        if (!game.init(screenWidth, screenHeight, gameTitle, 60)) {
            std::cerr << "Failed to initialize game!" << std::endl;
            return 1;
        }

        // Create MVC components for the menu
        auto menuModel = std::make_shared<models::MenuModel>();
        menuModel->init();

        auto menuView = std::make_shared<views::MenuView>(menuModel);
        menuView->init();

        // Create MVC components for the game
        auto gameModel = std::make_shared<models::GameModel>();
        gameModel->init();
        // Give menuModel access to the save manager
        menuModel->setSaveManager(gameModel->getSaveManager());

        auto gameView = std::make_shared<views::GameView>(gameModel);
        gameView->init();

        auto gameController = std::make_shared<controllers::GameController>(gameModel);
        gameController->init();

        // Create menu controller (needs both menu and game models)
        auto menuController = std::make_shared<controllers::MenuController>(menuModel, gameModel);
        menuController->init();

        // Add components to game
        game.addModel(menuModel);
        game.addView(menuView);
        game.addController(menuController);

        game.addModel(gameModel);
        game.addView(gameView);
        game.addController(gameController);

        // Start in menu state
        game.switchToMenu();

        // Run the game loop
        bool running = true;
        while (running && !WindowShouldClose()) {
            // Handle state transitions
            switch (game.getAppState()) {
                case core::AppState::MENU: {
                    // Process menu input
                    menuController->handleInput();
                    menuController->update(game.getDeltaTime());

                    // Update menu
                    menuModel->update(game.getDeltaTime());
                    menuView->update(game.getDeltaTime());

                    // Render menu
                    BeginDrawing();
                    menuView->render();
                    EndDrawing();

                    // Check for menu actions
                    if (menuController->shouldQuit()) {
                        running = false;
                        menuController->resetFlags();
                    } else if (menuController->shouldStartNewGame()) {
                        // Reset game for new game
                        gameModel->reset();
                        gameModel->init();
                        game.switchToGame();
                        menuController->resetFlags();
                    } else if (menuController->shouldLoadGame()) {
                        // Load the selected game (already loaded by controller)
                        game.switchToGame();
                        menuController->resetFlags();
                    } else if (menuController->shouldSaveGame()) {
                        // Game was saved, stay in menu
                        menuController->resetFlags();
                    }
                    break;
                }

                case core::AppState::GAME: {
                    // Check for ESC key to return to menu
                    if (IsKeyPressed(KEY_ESCAPE)) {
                        game.switchToMenu();
                        break;
                    }

                    // Update game
                    gameController->handleInput();
                    gameController->update(game.getDeltaTime());

                    gameModel->update(game.getDeltaTime());
                    gameView->update(game.getDeltaTime());

                    // Render game
                    BeginDrawing();
                    gameView->render();
                    EndDrawing();

                    // Auto-save after each round
                    auto gameState = gameModel->getState();
                    static auto lastGameState = gameState;
                    if ((gameState == models::GameState::PLAYER_WIN ||
                         gameState == models::GameState::DEALER_WIN ||
                         gameState == models::GameState::PUSH ||
                         gameState == models::GameState::BUSTED ||
                         gameState == models::GameState::PLAYER_BLACKJACK ||
                         gameState == models::GameState::DEALER_BLACKJACK) &&
                        lastGameState != gameState) {
                        gameModel->saveGame(1); // Auto-save to slot 1
                    }
                    lastGameState = gameState;

                    break;
                }

                case core::AppState::QUIT:
                    running = false;
                    break;
            }
        }

        // Cleanup
        game.shutdown();

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }
}
