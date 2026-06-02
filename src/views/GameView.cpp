#include "views/GameView.hpp"
#include "raylib.h"
#include <sstream>
#include <iomanip>

namespace game {
    namespace views {

        GameView::GameView(std::shared_ptr<models::GameModel> model)
            : View("GameView"), m_model(model) {
        }

        void GameView::init() {
            // Initialize any view-specific resources
        }

        void GameView::render() {
            renderTable();
            renderHand(m_model->getDealerHand(), "DEALER", 100, true);
            renderHand(m_model->getPlayerHand(), "PLAYER", 350, false);
            renderUI();
            renderMessage();
            renderControls();
        }

        void GameView::renderTable() {
            // Draw table background (felt green)
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                         Color{34, 139, 34, 255});

            // Draw table border
            DrawRectangleLines(10, 10, GetScreenWidth() - 20, GetScreenHeight() - 20,
                              Color{139, 69, 19, 255});
            DrawRectangleLines(15, 15, GetScreenWidth() - 30, GetScreenHeight() - 30,
                              Color{205, 133, 63, 255});
        }

        void GameView::renderHand(std::shared_ptr<models::Hand> hand,
                                 const std::string& label, int y, bool hideFirstCard) {
            // Draw label
            int labelX = GetScreenWidth() / 2 - 50;
            DrawText(label.c_str(), labelX, y, 30, WHITE);

            // Calculate starting x position to center cards
            int totalWidth = (int)hand->getCardCount() * (CARD_WIDTH + CARD_SPACING);
            int startX = (GetScreenWidth() - totalWidth) / 2;

            // Draw cards
            const auto& cards = hand->getCards();
            for (size_t i = 0; i < cards.size(); ++i) {
                bool hidden = hideFirstCard && i == 0;
                renderCard(cards[i], startX + (int)i * (CARD_WIDTH + CARD_SPACING),
                          y + 50, hidden);
            }

            // Draw hand value (unless hiding first card)
            if (!hideFirstCard) {
                std::ostringstream oss;
                oss << "Value: " << hand->getValue();
                std::string valueStr = oss.str();
                int valueX = GetScreenWidth() / 2 - MeasureText(valueStr.c_str(), 24) / 2;
                DrawText(valueStr.c_str(), valueX, y + 50 + CARD_HEIGHT + 10, 24, WHITE);
            }
        }

        void GameView::renderCard(std::shared_ptr<models::Card> card, int x, int y, bool hidden) {
            if (hidden) {
                // Draw card back
                DrawRectangle(x, y, CARD_WIDTH, CARD_HEIGHT, Color{178, 34, 34, 255});
                DrawRectangleLines(x, y, CARD_WIDTH, CARD_HEIGHT, BLACK);

                // Draw pattern on back
                for (int i = 10; i < CARD_WIDTH - 10; i += 20) {
                    for (int j = 10; j < CARD_HEIGHT - 10; j += 20) {
                        DrawCircle(x + i, y + j, 5, Color{139, 0, 0, 255});
                    }
                }
            } else {
                // Draw card front
                DrawRectangle(x, y, CARD_WIDTH, CARD_HEIGHT, WHITE);
                DrawRectangleLines(x, y, CARD_WIDTH, CARD_HEIGHT, BLACK);

                // Determine card color
                Color cardColor = card->isRed() ? RED : BLACK;

                // Draw rank in top-left corner
                std::string rank = card->getRankString();
                DrawText(rank.c_str(), x + 5, y + 5, 20, cardColor);

                // Draw suit symbol in top-right corner
                std::string suit = card->getSuitSymbol();
                int suitX = x + CARD_WIDTH - 25;
                DrawText(suit.c_str(), suitX, y + 5, 20, cardColor);

                // Draw large suit in center
                int centerX = x + CARD_WIDTH / 2 - 10;
                int centerY = y + CARD_HEIGHT / 2 - 10;
                DrawText(suit.c_str(), centerX, centerY, 30, cardColor);

                // Draw rank in bottom-right corner
                DrawText(rank.c_str(), x + CARD_WIDTH - 20, y + CARD_HEIGHT - 25, 20, cardColor);
            }
        }

        void GameView::renderUI() {
            // Draw score panel
            int panelX = 20;
            int panelY = GetScreenHeight() - 80;
            int panelWidth = 200;
            int panelHeight = 60;

            DrawRectangle(panelX, panelY, panelWidth, panelHeight,
                         Color{0, 0, 0, 150});
            DrawRectangleLines(panelX, panelY, panelWidth, panelHeight, WHITE);

            // Draw scores
            std::ostringstream oss;
            oss << "Player: " << m_model->getPlayerScore();
            DrawText(oss.str().c_str(), panelX + 10, panelY + 10, 18, WHITE);

            oss.str("");
            oss << "Dealer: " << m_model->getDealerScore();
            DrawText(oss.str().c_str(), panelX + 10, panelY + 35, 18, WHITE);
        }

        void GameView::renderMessage() {
            std::string message = m_model->getMessage();
            int messageX = GetScreenWidth() / 2 - MeasureText(message.c_str(), 28) / 2;
            int messageY = 250;

            // Draw message background
            int bgWidth = MeasureText(message.c_str(), 28) + 40;
            DrawRectangle(messageX - 20, messageY - 10, bgWidth, 50,
                         Color{0, 0, 0, 180});

            // Draw message text
            DrawText(message.c_str(), messageX, messageY, 28, YELLOW);
        }

        void GameView::renderControls() {
            // Draw controls panel
            int panelX = GetScreenWidth() - 250;
            int panelY = GetScreenHeight() - 100;
            int panelWidth = 230;
            int panelHeight = 80;

            DrawRectangle(panelX, panelY, panelWidth, panelHeight,
                         Color{0, 0, 0, 150});
            DrawRectangleLines(panelX, panelY, panelWidth, panelHeight, WHITE);

            // Draw controls text
            DrawText("CONTROLS:", panelX + 10, panelY + 10, 16, WHITE);
            DrawText("H - Hit", panelX + 10, panelY + 30, 14, LIGHTGRAY);
            DrawText("S - Stand", panelX + 10, panelY + 50, 14, LIGHTGRAY);
            DrawText("SPACE - New Game", panelX + 10, panelY + 70, 14, LIGHTGRAY);
        }

    } // namespace views
} // namespace game
