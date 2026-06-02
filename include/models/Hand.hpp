#ifndef HAND_HPP
#define HAND_HPP

#include "models/Card.hpp"
#include "models/Model.hpp"
#include <vector>
#include <memory>

namespace game {
    namespace models {

        /**
         * @brief Represents a hand of cards in Blackjack
         *
         * Manages a collection of cards and calculates the hand value
         * according to Blackjack rules (Aces can be 1 or 11).
         */
        class Hand : public Model {
        public:
            Hand();
            explicit Hand(const std::string& name);

            /**
             * @brief Add a card to the hand
             */
            void addCard(std::shared_ptr<Card> card);

            /**
             * @brief Get all cards in the hand
             */
            const std::vector<std::shared_ptr<Card>>& getCards() const { return m_cards; }

            /**
             * @brief Calculate the hand value following Blackjack rules
             * @return The optimal hand value (Aces count as 1 or 11 to maximize value without busting)
             */
            int getValue() const;

            /**
             * @brief Check if the hand has busted (value over 21)
             */
            bool isBusted() const { return getValue() > 21; }

            /**
             * @brief Check if the hand is a Blackjack (Ace + 10-value card)
             */
            bool isBlackjack() const;

            /**
             * @brief Check if the hand is soft (contains an Ace counted as 11)
             */
            bool isSoft() const;

            /**
             * @brief Clear all cards from the hand
             */
            void clear();

            /**
             * @brief Get the number of cards in the hand
             */
            size_t getCardCount() const { return m_cards.size(); }

        private:
            std::vector<std::shared_ptr<Card>> m_cards;
        };

    } // namespace models
} // namespace game

#endif // HAND_HPP
