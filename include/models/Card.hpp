#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include "core/Entity.hpp"

namespace game {
    namespace models {

        /**
         * @brief Enum representing card suits
         */
        enum class Suit {
            HEARTS,
            DIAMONDS,
            CLUBS,
            SPADES
        };

        /**
         * @brief Enum representing card ranks
         */
        enum class Rank {
            TWO = 2,
            THREE = 3,
            FOUR = 4,
            FIVE = 5,
            SIX = 6,
            SEVEN = 7,
            EIGHT = 8,
            NINE = 9,
            TEN = 10,
            JACK = 11,
            QUEEN = 12,
            KING = 13,
            ACE = 14
        };

        /**
         * @brief Represents a playing card
         */
        class Card : public core::Entity {
        public:
            Card(Suit suit, Rank rank);

            /**
             * @brief Get the card's suit
             */
            Suit getSuit() const { return m_suit; }

            /**
             * @brief Get the card's rank
             */
            Rank getRank() const { return m_rank; }

            /**
             * @brief Get the numeric value of the card
             * Face cards (J, Q, K) are worth 10, Ace is worth 11
             */
            int getValue() const;

            /**
             * @brief Check if the card is an Ace
             */
            bool isAce() const { return m_rank == Rank::ACE; }

            /**
             * @brief Get the card's display name
             */
            std::string toString() const;

            /**
             * @brief Get the suit symbol
             */
            std::string getSuitSymbol() const;

            /**
             * @brief Check if the suit is red (hearts or diamonds)
             */
            bool isRed() const;

            /**
             * @brief Get the rank as a string
             */
            std::string getRankString() const;

        private:
            Suit m_suit;
            Rank m_rank;
        };

    } // namespace models
} // namespace game

#endif // CARD_HPP
