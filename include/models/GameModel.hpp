#ifndef GAMEMODEL_HPP
#define GAMEMODEL_HPP

#include "models/Deck.hpp"
#include "models/Hand.hpp"
#include "models/Model.hpp"
#include "models/SaveData.hpp"
#include "models/SaveManager.hpp"
#include <string>
#include <memory>

namespace game {
    namespace models {

        /**
         * @brief Enum representing game states
         */
        enum class GameState {
            BETTING,        // Player is placing bets
            PLAYER_TURN,    // Player is hitting or standing
            DEALER_TURN,    // Dealer is playing
            GAME_OVER,      // Round is over, showing results
            PLAYER_BLACKJACK, // Player got blackjack
            DEALER_BLACKJACK, // Dealer got blackjack
            PUSH,           // Tie game
            PLAYER_WIN,     // Player wins
            DEALER_WIN,     // Dealer wins
            BUSTED          // Player busted
        };

        /**
         * @brief Main game model for Blackjack
         *
         * Manages the game state, deck, player hands, and game logic.
         */
        class GameModel : public Model {
        public:
            GameModel();

            /**
             * @brief Initialize the game
             */
            void init() override;

            /**
             * @brief Update the game logic
             */
            void update(float deltaTime) override;

            /**
             * @brief Start a new round
             */
            void startNewRound();

            /**
             * @brief Deal initial cards
             */
            void dealInitialCards();

            /**
             * @brief Player hits (draws a card)
             */
            void playerHit();

            /**
             * @brief Player stands (ends turn)
             */
            void playerStand();

            /**
             * @brief Dealer plays (hits until 17 or more)
             */
            void dealerPlay();

            /**
             * @brief Determine the winner of the round
             */
            void determineWinner();

            /**
             * @brief Reset the game to initial state
             */
            void reset() override;

            // Getters
            GameState getState() const { return m_state; }
            void setState(GameState state) { m_state = state; }

            std::shared_ptr<Deck> getDeck() { return m_deck; }
            std::shared_ptr<Hand> getPlayerHand() { return m_playerHand; }
            std::shared_ptr<Hand> getDealerHand() { return m_dealerHand; }

            int getPlayerScore() const { return m_playerScore; }
            int getDealerScore() const { return m_dealerScore; }

            std::string getMessage() const { return m_message; }
            void setMessage(const std::string& message) { m_message = message; }

            // Statistics getters
            int getWins() const { return m_wins; }
            int getLosses() const { return m_losses; }
            int getPushes() const { return m_pushes; }
            int getGamesPlayed() const { return m_wins + m_losses + m_pushes; }
            float getWinRate() const {
                int total = getGamesPlayed();
                return total > 0 ? static_cast<float>(m_wins) / total : 0.0f;
            }

            // Save/Load functionality
            bool saveGame(int slot = 1);
            bool loadGame(int slot = 1);
            std::shared_ptr<SaveManager> getSaveManager() { return m_saveManager; }

        private:
            std::shared_ptr<SaveManager> m_saveManager;

            GameState m_state;
            std::shared_ptr<Deck> m_deck;
            std::shared_ptr<Hand> m_playerHand;
            std::shared_ptr<Hand> m_dealerHand;

            int m_playerScore;
            int m_dealerScore;
            int m_wins;
            int m_losses;
            int m_pushes;

            std::string m_message;

            void updateScores();
            void checkDeckAndReshuffle();
        };

    } // namespace models
} // namespace game

#endif // GAMEMODEL_HPP
