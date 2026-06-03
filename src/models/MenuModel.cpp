#include "models/MenuModel.hpp"
#include <algorithm>

namespace game {
    namespace models {

        MenuModel::MenuModel()
            : Model("MenuModel"),
              m_state(MenuState::MAIN_MENU),
              m_selectedIndex(0),
              m_selectedSlot(1),
              m_lastSelectedOption(MenuOption::NEW_GAME) {
        }

        void MenuModel::init() {
            m_state = MenuState::MAIN_MENU;
            m_selectedIndex = 0;
            m_selectedSlot = 1;
        }

        void MenuModel::update(float deltaTime) {
            // Menu updates happen through action methods
        }

        void MenuModel::navigateUp() {
            auto options = getOptions();
            if (options.empty()) return;

            m_selectedIndex--;
            if (m_selectedIndex < 0) {
                m_selectedIndex = static_cast<int>(options.size()) - 1;
            }
        }

        void MenuModel::navigateDown() {
            auto options = getOptions();
            if (options.empty()) return;

            m_selectedIndex++;
            if (m_selectedIndex >= static_cast<int>(options.size())) {
                m_selectedIndex = 0;
            }
        }

        void MenuModel::selectOption() {
            switch (m_state) {
                case MenuState::MAIN_MENU:
                    switch (static_cast<MenuOption>(m_selectedIndex)) {
                        case MenuOption::NEW_GAME:
                            m_lastSelectedOption = MenuOption::NEW_GAME;
                            // Game will handle transition
                            break;
                        case MenuOption::LOAD_GAME:
                            m_state = MenuState::LOAD_SLOT_SELECT;
                            m_selectedIndex = 0;
                            m_selectedSlot = 1;
                            break;
                        case MenuOption::SAVE_GAME:
                            m_state = MenuState::SAVE_SLOT_SELECT;
                            m_selectedIndex = 0;
                            m_selectedSlot = 1;
                            break;
                        case MenuOption::SETTINGS:
                            m_state = MenuState::SETTINGS;
                            m_selectedIndex = 0;
                            break;
                        case MenuOption::QUIT:
                            m_lastSelectedOption = MenuOption::QUIT;
                            break;
                    }
                    break;

                case MenuState::SAVE_SLOT_SELECT:
                case MenuState::LOAD_SLOT_SELECT:
                    // Slot selection handled by controller
                    m_selectedSlot = m_selectedIndex + 1;
                    break;

                case MenuState::SETTINGS:
                    // Settings options would be handled here
                    break;

                default:
                    break;
            }
        }

        void MenuModel::goBack() {
            switch (m_state) {
                case MenuState::SAVE_SLOT_SELECT:
                case MenuState::LOAD_SLOT_SELECT:
                case MenuState::SETTINGS:
                    m_state = MenuState::MAIN_MENU;
                    m_selectedIndex = 0;
                    break;
                default:
                    break;
            }
        }

        std::string MenuModel::getTitle() const {
            switch (m_state) {
                case MenuState::MAIN_MENU:
                    return "BLACKJACK";
                case MenuState::SAVE_SLOT_SELECT:
                    return "SELECT SAVE SLOT";
                case MenuState::LOAD_SLOT_SELECT:
                    return "LOAD GAME";
                case MenuState::SETTINGS:
                    return "SETTINGS";
                default:
                    return "MENU";
            }
        }

        std::vector<std::string> MenuModel::getOptions() const {
            switch (m_state) {
                case MenuState::MAIN_MENU:
                    return getMainMenuOptions();
                case MenuState::SAVE_SLOT_SELECT:
                case MenuState::LOAD_SLOT_SELECT:
                    return getSaveSlotOptions();
                case MenuState::SETTINGS:
                    return getSettingsOptions();
                default:
                    return {};
            }
        }

        std::vector<std::string> MenuModel::getMainMenuOptions() const {
            return {
                "New Game",
                "Load Game",
                "Save Game",
                "Settings",
                "Quit"
            };
        }

        std::vector<std::string> MenuModel::getSaveSlotOptions() const {
            std::vector<std::string> options;
            for (int i = 1; i <= SaveManager::MAX_SAVE_SLOTS; ++i) {
                std::string slotText = "Slot " + std::to_string(i);

                if (m_saveManager && m_saveManager->slotExists(i)) {
                    auto info = m_saveManager->getSlotInfo(i);
                    slotText += " - " + info.getTimestamp();
                    if (info.inProgress) {
                        slotText += " (In Progress)";
                    }
                } else {
                    slotText += " - Empty";
                }

                options.push_back(slotText);
            }

            options.push_back("Back");
            return options;
        }

        std::vector<std::string> MenuModel::getSettingsOptions() const {
            return {
                "Sound: ON",
                "Music: ON",
                "Back"
            };
        }

        std::vector<SaveData> MenuModel::getSaveSlotInfo() const {
            if (m_saveManager) {
                return m_saveManager->getAllSlotInfo();
            }
            return {};
        }

        void MenuModel::reset() {
            m_state = MenuState::MAIN_MENU;
            m_selectedIndex = 0;
            m_selectedSlot = 1;
            m_lastSelectedOption = MenuOption::NEW_GAME;
        }

    } // namespace models
} // namespace game
