#include "controllers/GameController.hpp"
#include "raylib.h"

namespace game {
    namespace controllers {

        GameController::GameController(std::shared_ptr<models::GameModel> model)
            : Controller("GameController"), m_model(model) {
        }

        void GameController::init() {
            // Initialize controller-specific resources
        }

        void GameController::handleInput() {
            // Check for key presses
            int key = GetKeyPressed();
            if (key != 0) {
                handleKeyPress(key);
            }
        }

        void GameController::update(float deltaTime) {
            // Controller updates (if needed)
        }

        void GameController::handleKeyPress(int key) {
            using namespace models;

            // Handle input based on current game state
            switch (m_model->getState()) {
                case GameState::BETTING:
                    processBettingState(key);
                    break;

                case GameState::PLAYER_TURN:
                    processPlayerTurn(key);
                    break;

                case GameState::GAME_OVER:
                case GameState::PLAYER_BLACKJACK:
                case GameState::DEALER_BLACKJACK:
                case GameState::PLAYER_WIN:
                case GameState::DEALER_WIN:
                case GameState::PUSH:
                case GameState::BUSTED:
                case GameState::DEALER_TURN:
                    processGameOver(key);
                    break;

                default:
                    break;
            }
        }

        void GameController::processBettingState(int key) {
            if (key == KEY_SPACE) {
                m_model->startNewRound();
            }
        }

        void GameController::processPlayerTurn(int key) {
            switch (key) {
                case KEY_H:
                case KEY_H | 0x20: // Lowercase h
                    m_model->playerHit();
                    break;

                case KEY_S:
                case KEY_S | 0x20: // Lowercase s
                    m_model->playerStand();
                    break;

                default:
                    break;
            }
        }

        void GameController::processGameOver(int key) {
            if (key == KEY_SPACE) {
                m_model->startNewRound();
            }
        }

    } // namespace controllers
} // namespace game
