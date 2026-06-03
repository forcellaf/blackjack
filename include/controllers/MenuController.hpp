#ifndef MENUCONTROLLER_HPP
#define MENUCONTROLLER_HPP

#include "controllers/Controller.hpp"
#include "models/MenuModel.hpp"
#include "models/GameModel.hpp"
#include <memory>

namespace game {
    namespace controllers {

        /**
         * @brief Controller for handling menu input
         *
         * Processes keyboard input and coordinates menu navigation.
         */
        class MenuController : public Controller {
        public:
            MenuController(std::shared_ptr<models::MenuModel> menuModel,
                          std::shared_ptr<models::GameModel> gameModel);

            /**
             * @brief Initialize the controller
             */
            void init() override;

            /**
             * @brief Handle input
             */
            void handleInput() override;

            /**
             * @brief Update controller logic
             */
            void update(float deltaTime) override;

            /**
             * @brief Check if we should start a new game
             */
            bool shouldStartNewGame() const;

            /**
             * @brief Check if we should quit the game
             */
            bool shouldQuit() const;

            /**
             * @brief Get the selected save slot (for load/save operations)
             */
            int getSelectedSlot() const { return m_selectedSlot; }

            /**
             * @brief Check if a load operation was requested
             */
            bool shouldLoadGame() const { return m_shouldLoadGame; }

            /**
             * @brief Check if a save operation was requested
             */
            bool shouldSaveGame() const { return m_shouldSaveGame; }

            /**
             * @brief Reset the controller flags
             */
            void resetFlags();

            /**
             * @brief Check if we should return to menu from game
             */
            bool shouldReturnToMenu() const { return m_shouldReturnToMenu; }

            /**
             * @brief Set the return to menu flag
             */
            void setShouldReturnToMenu(bool value) { m_shouldReturnToMenu = value; }

        private:
            std::shared_ptr<models::MenuModel> m_menuModel;
            std::shared_ptr<models::GameModel> m_gameModel;

            bool m_shouldStartNewGame;
            bool m_shouldQuit;
            bool m_shouldLoadGame;
            bool m_shouldSaveGame;
            bool m_shouldReturnToMenu;
            int m_selectedSlot;

            /**
             * @brief Handle main menu input
             */
            void handleMainMenuInput(int key);

            /**
             * @brief Handle save slot selection input
             */
            void handleSaveSlotInput(int key);

            /**
             * @brief Handle load slot selection input
             */
            void handleLoadSlotInput(int key);

            /**
             * @brief Handle settings input
             */
            void handleSettingsInput(int key);

            /**
             * @brief Execute the selected menu option
             */
            void executeMainMenuSelection();
        };

    } // namespace controllers
} // namespace game

#endif // MENUCONTROLLER_HPP
