#include "models/Hand.hpp"
#include <algorithm>

namespace game {
    namespace models {

        Hand::Hand()
            : Model("Hand") {
        }

        Hand::Hand(const std::string& name)
            : Model(name) {
        }

        void Hand::addCard(std::shared_ptr<Card> card) {
            if (card) {
                m_cards.push_back(card);
            }
        }

        int Hand::getValue() const {
            int value = 0;
            int aceCount = 0;

            // Sum all cards, counting aces as 11
            for (const auto& card : m_cards) {
                value += card->getValue();
                if (card->isAce()) {
                    aceCount++;
                }
            }

            // Adjust for aces if busting
            while (value > 21 && aceCount > 0) {
                value -= 10; // Count an Ace as 1 instead of 11
                aceCount--;
            }

            return value;
        }

        bool Hand::isBlackjack() const {
            return m_cards.size() == 2 && getValue() == 21;
        }

        bool Hand::isSoft() const {
            int value = 0;
            int aceCount = 0;

            for (const auto& card : m_cards) {
                value += card->getValue();
                if (card->isAce()) {
                    aceCount++;
                }
            }

            // If we have an ace that could be counted as 11 without busting, it's soft
            return (aceCount > 0 && value <= 21) &&
                   (value + 10 > 21 || aceCount > 1);
        }

        void Hand::clear() {
            m_cards.clear();
        }

    } // namespace models
} // namespace game
