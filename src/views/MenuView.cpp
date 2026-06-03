#include "views/MenuView.hpp"
#include "raylib.h"
#include <sstream>

namespace game {
    namespace views {

        MenuView::MenuView(std::shared_ptr<models::MenuModel> model)
            : View("MenuView"), m_model(model) {
        }

        void MenuView::init() {
            // Initialize view-specific resources
        }

        void MenuView::update(float deltaTime) {
            // Update animations if needed
        }

        void MenuView::render() {
            renderBackground();
            renderTitle();
            renderOptions();
            renderFooter();
        }

        void MenuView::renderBackground() {
            // Draw felt green background
            ClearBackground(Color{20, 100, 20, 255});

            // Draw decorative card pattern
            int cardWidth = 60;
            int cardHeight = 90;
            Color cardColor = Color{255, 255, 255, 30};

            // Draw some cards in the background
            for (int i = 0; i < 5; ++i) {
                int x = 100 + i * 150;
                int y = 150;
                DrawRectangle(x, y, cardWidth, cardHeight, cardColor);
                DrawRectangleLines(x, y, cardWidth, cardHeight, Color{255, 255, 255, 50});
            }
        }

        void MenuView::renderTitle() {
            std::string title = m_model->getTitle();

            int titleWidth = MeasureText(title.c_str(), TITLE_FONT_SIZE);
            int titleX = (GetScreenWidth() - titleWidth) / 2;

            // Draw title shadow
            DrawText(title.c_str(), titleX + 3, TITLE_Y + 3, TITLE_FONT_SIZE, Color{0, 0, 0, 150});

            // Draw title with gold color
            DrawText(title.c_str(), titleX, TITLE_Y, TITLE_FONT_SIZE, Color{255, 215, 0, 255});

            // Draw subtitle for main menu
            if (m_model->getMenuState() == models::MenuState::MAIN_MENU) {
                std::string subtitle = "The Classic Card Game";
                int subWidth = MeasureText(subtitle.c_str(), 24);
                int subX = (GetScreenWidth() - subWidth) / 2;
                DrawText(subtitle.c_str(), subX, TITLE_Y + TITLE_FONT_SIZE + 10, 24, WHITE);
            }
        }

        void MenuView::renderOptions() {
            auto options = m_model->getOptions();
            int selectedIndex = m_model->getSelectedIndex();

            for (size_t i = 0; i < options.size(); ++i) {
                int y = OPTIONS_START_Y + static_cast<int>(i) * OPTION_HEIGHT;
                bool selected = (i == static_cast<size_t>(selectedIndex));
                renderOption(options[i], y, selected);
            }
        }

        void MenuView::renderOption(const std::string& text, int y, bool selected) {
            int textWidth = MeasureText(text.c_str(), OPTION_FONT_SIZE);
            int x = (GetScreenWidth() - textWidth) / 2;

            if (selected) {
                // Draw selection indicator
                int boxWidth = textWidth + 40;
                int boxHeight = OPTION_HEIGHT - 10;
                int boxX = (GetScreenWidth() - boxWidth) / 2;
                int boxY = y - 5;

                // Draw glowing effect
                DrawRectangle(boxX - 5, boxY - 5, boxWidth + 10, boxHeight + 10, Color{255, 215, 0, 50});
                DrawRectangle(boxX, boxY, boxWidth, boxHeight, Color{255, 215, 0, 100});
                DrawRectangleLines(boxX, boxY, boxWidth, boxHeight, Color{255, 215, 0, 255});

                // Draw arrow indicator
                DrawText(">", boxX - 30, y, OPTION_FONT_SIZE, Color{255, 215, 0, 255});
            }

            // Draw text
            Color textColor = selected ? WHITE : Color{200, 200, 200, 255};
            DrawText(text.c_str(), x, y, OPTION_FONT_SIZE, textColor);
        }

        void MenuView::renderSaveSlotInfo() {
            if (m_model->getMenuState() != models::MenuState::LOAD_SLOT_SELECT &&
                m_model->getMenuState() != models::MenuState::SAVE_SLOT_SELECT) {
                return;
            }

            auto slotInfo = m_model->getSaveSlotInfo();
            // Additional slot info rendering if needed
        }

        void MenuView::renderFooter() {
            // Draw controls panel at the bottom
            int panelY = FOOTER_Y;
            int panelHeight = 50;

            // Draw panel background
            DrawRectangle(0, panelY, GetScreenWidth(), panelHeight, Color{0, 0, 0, 100});

            // Draw controls text
            const char* controlsText = "ARROW UP/DOWN - Navigate  |  ENTER - Select  |  ESC - Back";
            int controlsWidth = MeasureText(controlsText, 18);
            int controlsX = (GetScreenWidth() - controlsWidth) / 2;

            DrawText(controlsText, controlsX, panelY + 15, 18, WHITE);
        }

    } // namespace views
} // namespace game
