#ifndef DECK_HPP
#define DECK_HPP

#include "models/Card.hpp"
#include "models/Model.hpp"
#include <vector>
#include <memory>
#include <random>

namespace game {
    namespace models {

        /**
         * @brief Represents a deck of playing cards
         *
         * Manages a standard 52-card deck with shuffling functionality.
         */
        class Deck : public Model {
        public:
            Deck();
            explicit Deck(const std::string& name);

            /**
             * @brief Initialize the deck with all 52 cards
             */
            void init() override;

            /**
             * @brief Shuffle the deck using Fisher-Yates algorithm
             */
            void shuffle();

            /**
             * @brief Draw a card from the deck
             * @return Pointer to the drawn card, or nullptr if deck is empty
             */
            std::shared_ptr<Card> drawCard();

            /**
             * @brief Get the number of cards remaining in the deck
             */
            size_t getCardCount() const { return m_cards.size(); }

            /**
             * @brief Check if the deck is empty
             */
            bool isEmpty() const { return m_cards.empty(); }

            /**
             * @brief Reset the deck to a full 52-card deck
             */
            void reset();

        private:
            std::vector<std::shared_ptr<Card>> m_cards;
            std::random_device m_randomDevice;
            std::mt19937 m_randomGenerator;
        };

    } // namespace models
} // namespace game

#endif // DECK_HPP
