#include "controllers/MenuController.hpp"
#include "raylib.h"

namespace game {
    namespace controllers {

        MenuController::MenuController(std::shared_ptr<models::MenuModel> menuModel,
                                       std::shared_ptr<models::GameModel> gameModel)
            : Controller("MenuController"),
              m_menuModel(menuModel),
              m_gameModel(gameModel),
              m_shouldStartNewGame(false),
              m_shouldQuit(false),
              m_shouldLoadGame(false),
              m_shouldSaveGame(false),
              m_shouldReturnToMenu(false),
              m_selectedSlot(1) {
        }

        void MenuController::init() {
            // Initialize controller-specific resources
        }

        void MenuController::handleInput() {
            // Check for key presses
            int key = GetKeyPressed();
            if (key != 0) {
                // Handle common navigation keys
                switch (key) {
                    case KEY_UP:
                        m_menuModel->navigateUp();
                        break;

                    case KEY_DOWN:
                        m_menuModel->navigateDown();
                        break;

                    case KEY_ESCAPE:
                        m_menuModel->goBack();
                        break;

                    case KEY_ENTER:
                    case KEY_KP_ENTER:
                        m_menuModel->selectOption();
                        // Handle the selection based on current state
                        executeMainMenuSelection();
                        break;

                    default:
                        break;
                }

                // State-specific input handling
                switch (m_menuModel->getMenuState()) {
                    case models::MenuState::MAIN_MENU:
                        // Already handled by executeMainMenuSelection
                        break;

                    case models::MenuState::SAVE_SLOT_SELECT:
                        handleSaveSlotInput(key);
                        break;

                    case models::MenuState::LOAD_SLOT_SELECT:
                        handleLoadSlotInput(key);
                        break;

                    case models::MenuState::SETTINGS:
                        handleSettingsInput(key);
                        break;

                    default:
                        break;
                }
            }
        }

        void MenuController::update(float deltaTime) {
            // Controller updates (if needed)
        }

        bool MenuController::shouldStartNewGame() const {
            return m_shouldStartNewGame;
        }

        bool MenuController::shouldQuit() const {
            return m_shouldQuit;
        }

        void MenuController::resetFlags() {
            m_shouldStartNewGame = false;
            m_shouldQuit = false;
            m_shouldLoadGame = false;
            m_shouldSaveGame = false;
            m_shouldReturnToMenu = false;
        }

        void MenuController::executeMainMenuSelection() {
            if (m_menuModel->getMenuState() != models::MenuState::MAIN_MENU) {
                return;
            }

            auto selectedOption = m_menuModel->getLastSelectedOption();

            switch (selectedOption) {
                case models::MenuOption::NEW_GAME:
                    m_shouldStartNewGame = true;
                    break;

                case models::MenuOption::QUIT:
                    m_shouldQuit = true;
                    break;

                case models::MenuOption::LOAD_GAME:
                case models::MenuOption::SAVE_GAME:
                case models::MenuOption::SETTINGS:
                    // These options transition to sub-menus, handled by state change
                    break;

                default:
                    break;
            }
        }

        void MenuController::handleSaveSlotInput(int key) {
            if (key != KEY_ENTER && key != KEY_KP_ENTER) {
                return;
            }

            auto options = m_menuModel->getOptions();
            int selectedIndex = m_menuModel->getSelectedIndex();

            // Check if "Back" was selected (last option)
            if (selectedIndex >= static_cast<int>(options.size()) - 1) {
                m_menuModel->goBack();
                return;
            }

            // Save game to selected slot
            m_selectedSlot = selectedIndex + 1;
            if (m_gameModel) {
                m_gameModel->saveGame(m_selectedSlot);
            }

            m_shouldSaveGame = true;
            m_menuModel->setMenuState(models::MenuState::MAIN_MENU);
            m_menuModel->setSelectedIndex(0);
        }

        void MenuController::handleLoadSlotInput(int key) {
            if (key != KEY_ENTER && key != KEY_KP_ENTER) {
                return;
            }

            auto options = m_menuModel->getOptions();
            int selectedIndex = m_menuModel->getSelectedIndex();

            // Check if "Back" was selected (last option)
            if (selectedIndex >= static_cast<int>(options.size()) - 1) {
                m_menuModel->goBack();
                return;
            }

            // Load game from selected slot
            m_selectedSlot = selectedIndex + 1;
            if (m_gameModel) {
                if (m_gameModel->loadGame(m_selectedSlot)) {
                    m_shouldLoadGame = true;
                } else {
                    // Failed to load - stay in menu
                    // Could show error message here
                }
            }
        }

        void MenuController::handleSettingsInput(int key) {
            // Settings would be handled here
            // For now, just allow going back
        }

    } // namespace controllers
} // namespace game
