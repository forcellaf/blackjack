#ifndef SAVEDATA_HPP
#define SAVEDATA_HPP

#include <string>
#include <vector>
#include <ctime>

namespace game {
    namespace models {

        /**
         * @brief Structure representing a single card for serialization
         */
        struct SerializedCard {
            int suit;   // Suit enum value
            int rank;   // Rank enum value

            SerializedCard() : suit(0), rank(0) {}
            SerializedCard(int s, int r) : suit(s), rank(r) {}
        };

        /**
         * @brief Structure representing a hand for serialization
         */
        struct SerializedHand {
            std::vector<SerializedCard> cards;

            SerializedHand() = default;
        };

        /**
         * @brief Structure representing the complete game save data
         */
        struct SaveData {
            // Version info
            int version;

            // Timestamp
            std::time_t saveTime;

            // Game statistics
            int wins;
            int losses;
            int pushes;

            // Current game state (if in progress)
            bool inProgress;

            // Current hands (if game is in progress)
            SerializedHand playerHand;
            SerializedHand dealerHand;

            // Deck state (simplified - just card count for reshuffling)
            int deckCardCount;

            /**
             * @brief Default constructor - initializes with default values
             */
            SaveData()
                : version(1),
                  saveTime(std::time(nullptr)),
                  wins(0),
                  losses(0),
                  pushes(0),
                  inProgress(false),
                  deckCardCount(52) {}

            /**
             * @brief Convert SaveData to JSON string
             */
            std::string toJSON() const;

            /**
             * @brief Parse SaveData from JSON string
             */
            static SaveData fromJSON(const std::string& json);

            /**
             * @brief Get formatted timestamp string
             */
            std::string getTimestamp() const;
        };

    } // namespace models
} // namespace game

#endif // SAVEDATA_HPP
