#include "models/GameModel.hpp"
#include <sstream>
#include <iomanip>

namespace game {
    namespace models {

        GameModel::GameModel()
            : Model("GameModel"),
              m_state(GameState::BETTING),
              m_playerScore(0),
              m_dealerScore(0),
              m_wins(0),
              m_losses(0),
              m_pushes(0),
              m_message("Press SPACE to start") {

            m_deck = std::make_shared<Deck>("MainDeck");
            m_playerHand = std::make_shared<Hand>("PlayerHand");
            m_dealerHand = std::make_shared<Hand>("DealerHand");
        }

        void GameModel::init() {
            m_deck->init();
            reset();
        }

        void GameModel::update(float deltaTime) {
            // Game logic updates happen through action methods
        }

        void GameModel::startNewRound() {
            // Clear hands
            m_playerHand->clear();
            m_dealerHand->clear();

            // Check if deck needs reshuffling (less than 15 cards)
            checkDeckAndReshuffle();

            // Deal initial cards
            dealInitialCards();

            // Check for blackjacks
            if (m_playerHand->isBlackjack()) {
                if (m_dealerHand->isBlackjack()) {
                    m_state = GameState::PUSH;
                    m_message = "Both Blackjack! Push!";
                    m_pushes++;
                } else {
                    m_state = GameState::PLAYER_BLACKJACK;
                    m_message = "BLACKJACK! You win!";
                    m_wins++;
                }
            } else if (m_dealerHand->isBlackjack()) {
                m_state = GameState::DEALER_BLACKJACK;
                m_message = "Dealer Blackjack! You lose!";
                m_losses++;
            } else {
                m_state = GameState::PLAYER_TURN;
                m_message = "Hit (H) or Stand (S)?";
            }
        }

        void GameModel::dealInitialCards() {
            // Deal two cards to player
            m_playerHand->addCard(m_deck->drawCard());
            m_playerHand->addCard(m_deck->drawCard());

            // Deal two cards to dealer
            m_dealerHand->addCard(m_deck->drawCard());
            m_dealerHand->addCard(m_deck->drawCard());

            updateScores();
        }

        void GameModel::playerHit() {
            if (m_state != GameState::PLAYER_TURN) {
                return;
            }

            m_playerHand->addCard(m_deck->drawCard());
            updateScores();

            if (m_playerHand->isBusted()) {
                m_state = GameState::BUSTED;
                m_message = "Busted! You lose!";
                m_losses++;
            } else if (m_playerHand->getValue() == 21) {
                // Auto-stand on 21
                playerStand();
            }
        }

        void GameModel::playerStand() {
            if (m_state != GameState::PLAYER_TURN) {
                return;
            }

            m_state = GameState::DEALER_TURN;
            m_message = "Dealer's turn...";
            dealerPlay();
        }

        void GameModel::dealerPlay() {
            // Dealer hits on 16 or less, stands on 17 or more
            while (m_dealerHand->getValue() < 17) {
                m_dealerHand->addCard(m_deck->drawCard());
            }

            updateScores();
            determineWinner();
        }

        void GameModel::determineWinner() {
            int playerValue = m_playerHand->getValue();
            int dealerValue = m_dealerHand->getValue();

            if (m_dealerHand->isBusted()) {
                m_state = GameState::PLAYER_WIN;
                m_message = "Dealer busted! You win!";
                m_wins++;
            } else if (playerValue > dealerValue) {
                m_state = GameState::PLAYER_WIN;
                m_message = "You win!";
                m_wins++;
            } else if (dealerValue > playerValue) {
                m_state = GameState::DEALER_WIN;
                m_message = "Dealer wins!";
                m_losses++;
            } else {
                m_state = GameState::PUSH;
                m_message = "Push! It's a tie!";
                m_pushes++;
            }

            // Add instructions for next round
            m_message += " Press SPACE for new round";
        }

        void GameModel::reset() {
            m_playerHand->clear();
            m_dealerHand->clear();
            m_state = GameState::BETTING;
            m_playerScore = 0;
            m_dealerScore = 0;
            m_wins = 0;
            m_losses = 0;
            m_pushes = 0;
            m_message = "Press SPACE to start";
        }

        void GameModel::updateScores() {
            m_playerScore = m_playerHand->getValue();
            m_dealerScore = m_dealerHand->getValue();
        }

        void GameModel::checkDeckAndReshuffle() {
            if (m_deck->getCardCount() < 15) {
                m_deck->reset();
                m_message = "Deck reshuffled!";
            }
        }

    } // namespace models
} // namespace game
