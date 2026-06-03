#ifndef MENUMODEL_HPP
#define MENUMODEL_HPP

#include "models/Model.hpp"
#include "models/SaveManager.hpp"
#include <string>
#include <vector>
#include <memory>

namespace game {
    namespace models {

        /**
         * @brief Enum representing menu options
         */
        enum class MenuOption {
            NEW_GAME,
            LOAD_GAME,
            SAVE_GAME,
            SETTINGS,
            QUIT
        };

        /**
         * @brief Enum representing menu states
         */
        enum class MenuState {
            MAIN_MENU,
            SAVE_SLOT_SELECT,
            LOAD_SLOT_SELECT,
            SETTINGS,
            NONE
        };

        /**
         * @brief Main menu model
         *
         * Manages the main menu state and options.
         */
        class MenuModel : public Model {
        public:
            MenuModel();

            /**
             * @brief Initialize the menu
             */
            void init() override;

            /**
             * @brief Update menu logic
             */
            void update(float deltaTime) override;

            /**
             * @brief Navigate up in the menu
             */
            void navigateUp();

            /**
             * @brief Navigate down in the menu
             */
            void navigateDown();

            /**
             * @brief Select the current menu option
             */
            void selectOption();

            /**
             * @brief Go back to the previous state
             */
            void goBack();

            /**
             * @brief Get current menu state
             */
            MenuState getMenuState() const { return m_state; }

            /**
             * @brief Set menu state
             */
            void setMenuState(MenuState state) { m_state = state; }

            /**
             * @brief Get currently selected option index
             */
            int getSelectedIndex() const { return m_selectedIndex; }

            /**
             * @brief Set selected index
             */
            void setSelectedIndex(int index) { m_selectedIndex = index; }

            /**
             * @brief Get menu title
             */
            std::string getTitle() const;

            /**
             * @brief Get available menu options for current state
             */
            std::vector<std::string> getOptions() const;

            /**
             * @brief Get the last selected option for main menu
             */
            MenuOption getLastSelectedOption() const { return m_lastSelectedOption; }

            /**
             * @brief Set the save manager
             */
            void setSaveManager(std::shared_ptr<SaveManager> saveManager) {
                m_saveManager = saveManager;
            }

            /**
             * @brief Get save slot information
             */
            std::vector<SaveData> getSaveSlotInfo() const;

            /**
             * @brief Get selected save slot
             */
            int getSelectedSlot() const { return m_selectedSlot; }

            /**
             * @brief Set selected save slot
             */
            void setSelectedSlot(int slot) { m_selectedSlot = slot; }

            /**
             * @brief Reset the menu
             */
            void reset() override;

        private:
            MenuState m_state;
            int m_selectedIndex;
            int m_selectedSlot;
            MenuOption m_lastSelectedOption;
            std::shared_ptr<SaveManager> m_saveManager;

            /**
             * @brief Get main menu options
             */
            std::vector<std::string> getMainMenuOptions() const;

            /**
             * @brief Get save slot options
             */
            std::vector<std::string> getSaveSlotOptions() const;

            /**
             * @brief Get settings options
             */
            std::vector<std::string> getSettingsOptions() const;
        };

    } // namespace models
} // namespace game

#endif // MENUMODEL_HPP
