#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include "views/View.hpp"
#include "models/GameModel.hpp"
#include "models/Hand.hpp"
#include <memory>

namespace game {
    namespace views {

        /**
         * @brief View for rendering the Blackjack game
         *
         * Handles all visual rendering of the game state including cards,
         * UI elements, and game information.
         */
        class GameView : public View {
        public:
            GameView(std::shared_ptr<models::GameModel> model);
            ~GameView() override = default;

            /**
             * @brief Initialize the view
             */
            void init() override;

            /**
             * @brief Render the game
             */
            void render() override;

        private:
            std::shared_ptr<models::GameModel> m_model;

            // Render methods
            void renderTable();
            void renderHand(std::shared_ptr<models::Hand> hand, const std::string& label,
                          int y, bool hideFirstCard = false);
            void renderCard(std::shared_ptr<models::Card> card, int x, int y, bool hidden = false);
            void renderUI();
            void renderMessage();
            void renderControls();

            // Colors
            static constexpr int CARD_WIDTH = 80;
            static constexpr int CARD_HEIGHT = 120;
            static constexpr int CARD_SPACING = 20;
        };

    } // namespace views
} // namespace game

#endif // GAMEVIEW_HPP
