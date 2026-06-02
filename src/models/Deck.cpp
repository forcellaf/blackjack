#include "models/Deck.hpp"
#include <algorithm>

namespace game {
    namespace models {

        Deck::Deck()
            : Model("Deck"), m_randomGenerator(m_randomDevice()) {
        }

        Deck::Deck(const std::string& name)
            : Model(name), m_randomGenerator(m_randomDevice()) {
        }

        void Deck::init() {
            reset();
        }

        void Deck::shuffle() {
            std::shuffle(m_cards.begin(), m_cards.end(), m_randomGenerator);
        }

        std::shared_ptr<Card> Deck::drawCard() {
            if (isEmpty()) {
                return nullptr;
            }

            auto card = m_cards.back();
            m_cards.pop_back();
            return card;
        }

        void Deck::reset() {
            m_cards.clear();

            // Create all 52 cards
            for (int suit = 0; suit < 4; ++suit) {
                for (int rank = 2; rank <= 14; ++rank) {
                    Suit s = static_cast<Suit>(suit);
                    Rank r = static_cast<Rank>(rank);
                    m_cards.push_back(std::make_shared<Card>(s, r));
                }
            }

            // Shuffle the deck
            shuffle();
        }

    } // namespace models
} // namespace game
