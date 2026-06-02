#include "models/Card.hpp"
#include <sstream>

namespace game {
    namespace models {

        Card::Card(Suit suit, Rank rank)
            : core::Entity("Card"), m_suit(suit), m_rank(rank) {
        }

        std::string Card::toString() const {
            std::ostringstream oss;
            oss << getRankString() << getSuitSymbol();
            return oss.str();
        }

        std::string Card::getSuitSymbol() const {
            switch (m_suit) {
                case Suit::HEARTS:   return "♥";
                case Suit::DIAMONDS: return "♦";
                case Suit::CLUBS:    return "♣";
                case Suit::SPADES:   return "♠";
                default: return "?";
            }
        }

        bool Card::isRed() const {
            return m_suit == Suit::HEARTS || m_suit == Suit::DIAMONDS;
        }

        int Card::getValue() const {
            // Face cards (J, Q, K) are worth 10
            if (m_rank == Rank::JACK || m_rank == Rank::QUEEN || m_rank == Rank::KING) {
                return 10;
            }
            // Ace is worth 11
            if (m_rank == Rank::ACE) {
                return 11;
            }
            // Number cards are worth their face value
            return static_cast<int>(m_rank);
        }

        std::string Card::getRankString() const {
            switch (m_rank) {
                case Rank::TWO:   return "2";
                case Rank::THREE: return "3";
                case Rank::FOUR:  return "4";
                case Rank::FIVE:  return "5";
                case Rank::SIX:   return "6";
                case Rank::SEVEN: return "7";
                case Rank::EIGHT: return "8";
                case Rank::NINE:  return "9";
                case Rank::TEN:   return "10";
                case Rank::JACK:  return "J";
                case Rank::QUEEN: return "Q";
                case Rank::KING:  return "K";
                case Rank::ACE:   return "A";
                default: return "?";
            }
        }

    } // namespace models
} // namespace game
