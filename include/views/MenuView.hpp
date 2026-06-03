#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include "views/View.hpp"
#include "models/MenuModel.hpp"
#include <memory>

namespace game {
    namespace views {

        /**
         * @brief View for rendering the main menu
         *
         * Handles the visual presentation of the menu system.
         */
        class MenuView : public View {
        public:
            explicit MenuView(std::shared_ptr<models::MenuModel> model);

            /**
             * @brief Initialize the view
             */
            void init() override;

            /**
             * @brief Render the menu
             */
            void render() override;

            /**
             * @brief Update view animations
             */
            void update(float deltaTime) override;

        private:
            std::shared_ptr<models::MenuModel> m_model;

            /**
             * @brief Render the menu background
             */
            void renderBackground();

            /**
             * @brief Render the menu title
             */
            void renderTitle();

            /**
             * @brief Render the menu options
             */
            void renderOptions();

            /**
             * @brief Render a single menu option
             */
            void renderOption(const std::string& text, int y, bool selected);

            /**
             * @brief Render save slot information
             */
            void renderSaveSlotInfo();

            /**
             * @brief Render footer with controls
             */
            void renderFooter();

            // Constants
            static constexpr int TITLE_Y = 100;
            static constexpr int OPTIONS_START_Y = 250;
            static constexpr int OPTION_HEIGHT = 50;
            static constexpr int TITLE_FONT_SIZE = 60;
            static constexpr int OPTION_FONT_SIZE = 30;
            static constexpr int FOOTER_Y = 700;
        };

    } // namespace views
} // namespace game

#endif // MENUVIEW_HPP
