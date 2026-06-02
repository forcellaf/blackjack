#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include "controllers/Controller.hpp"
#include "models/GameModel.hpp"
#include <memory>

namespace game {
    namespace controllers {

        /**
         * @brief Controller for handling game input
         *
         * Manages user input and coordinates between model and view.
         */
        class GameController : public Controller {
        public:
            GameController(std::shared_ptr<models::GameModel> model);
            ~GameController() override = default;

            /**
             * @brief Initialize the controller
             */
            void init() override;

            /**
             * @brief Handle input events
             */
            void handleInput() override;

            /**
             * @brief Update the controller
             */
            void update(float deltaTime) override;

        private:
            std::shared_ptr<models::GameModel> m_model;

            // Input handlers
            void handleKeyPress(int key);
            void processBettingState(int key);
            void processPlayerTurn(int key);
            void processGameOver(int key);
        };

    } // namespace controllers
} // namespace game

#endif // GAMECONTROLLER_HPP
