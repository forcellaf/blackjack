#include "core/Game.hpp"
#include "models/GameModel.hpp"
#include "views/GameView.hpp"
#include "controllers/GameController.hpp"
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

        // Create MVC components
        auto gameModel = std::make_shared<models::GameModel>();
        gameModel->init();

        auto gameView = std::make_shared<views::GameView>(gameModel);
        gameView->init();

        auto gameController = std::make_shared<controllers::GameController>(gameModel);
        gameController->init();

        // Add components to game
        game.addModel(gameModel);
        game.addView(gameView);
        game.addController(gameController);

        // Run the game loop
        game.run();

        // Cleanup
        game.shutdown();

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }
}
