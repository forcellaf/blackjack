#include "models/SaveData.hpp"
#include <sstream>
#include <iomanip>
#include <ctime>

namespace game {
    namespace models {

        std::string SaveData::toJSON() const {
            std::ostringstream json;

            json << "{\n";
            json << "  \"version\": " << version << ",\n";
            json << "  \"saveTime\": " << saveTime << ",\n";
            json << "  \"wins\": " << wins << ",\n";
            json << "  \"losses\": " << losses << ",\n";
            json << "  \"pushes\": " << pushes << ",\n";
            json << "  \"inProgress\": " << (inProgress ? "true" : "false") << ",\n";
            json << "  \"deckCardCount\": " << deckCardCount << ",\n";

            // Player hand
            json << "  \"playerHand\": {\n";
            json << "    \"cards\": [";
            for (size_t i = 0; i < playerHand.cards.size(); ++i) {
                if (i > 0) json << ", ";
                json << "[" << playerHand.cards[i].suit << ", " << playerHand.cards[i].rank << "]";
            }
            json << "]\n";
            json << "  },\n";

            // Dealer hand
            json << "  \"dealerHand\": {\n";
            json << "    \"cards\": [";
            for (size_t i = 0; i < dealerHand.cards.size(); ++i) {
                if (i > 0) json << ", ";
                json << "[" << dealerHand.cards[i].suit << ", " << dealerHand.cards[i].rank << "]";
            }
            json << "]\n";
            json << "  }\n";

            json << "}";
            return json.str();
        }

        SaveData SaveData::fromJSON(const std::string& json) {
            SaveData data;

            // Simple JSON parser for our specific format
            // This is a basic implementation - in production, use a proper JSON library

            // Helper lambda to find next value after a key
            auto findValue = [&json](const std::string& key) -> std::string {
                size_t keyPos = json.find("\"" + key + "\"");
                if (keyPos == std::string::npos) return "";
                size_t colonPos = json.find(":", keyPos);
                if (colonPos == std::string::npos) return "";

                size_t valueStart = colonPos + 1;
                while (valueStart < json.size() && (json[valueStart] == ' ' || json[valueStart] == '\t'))
                    valueStart++;

                if (json[valueStart] == '"') {
                    // String value
                    size_t valueEnd = json.find("\"", valueStart + 1);
                    return json.substr(valueStart + 1, valueEnd - valueStart - 1);
                } else if (json[valueStart] == '[') {
                    // Array value - find matching bracket
                    int bracketCount = 1;
                    size_t valueEnd = valueStart + 1;
                    while (valueEnd < json.size() && bracketCount > 0) {
                        if (json[valueEnd] == '[') bracketCount++;
                        else if (json[valueEnd] == ']') bracketCount--;
                        valueEnd++;
                    }
                    return json.substr(valueStart, valueEnd - valueStart);
                } else if (json[valueStart] == 't' || json[valueStart] == 'f') {
                    // Boolean value
                    size_t valueEnd = json.find_first_of(",}\n", valueStart);
                    return json.substr(valueStart, valueEnd - valueStart);
                } else {
                    // Numeric value
                    size_t valueEnd = json.find_first_of(",}\n", valueStart);
                    return json.substr(valueStart, valueEnd - valueStart);
                }
            };

            // Parse values
            std::string versionStr = findValue("version");
            if (!versionStr.empty()) data.version = std::stoi(versionStr);

            std::string saveTimeStr = findValue("saveTime");
            if (!saveTimeStr.empty()) data.saveTime = std::stol(saveTimeStr);

            std::string winsStr = findValue("wins");
            if (!winsStr.empty()) data.wins = std::stoi(winsStr);

            std::string lossesStr = findValue("losses");
            if (!lossesStr.empty()) data.losses = std::stoi(lossesStr);

            std::string pushesStr = findValue("pushes");
            if (!pushesStr.empty()) data.pushes = std::stoi(pushesStr);

            std::string inProgressStr = findValue("inProgress");
            data.inProgress = (inProgressStr == "true");

            std::string deckCountStr = findValue("deckCardCount");
            if (!deckCountStr.empty()) data.deckCardCount = std::stoi(deckCountStr);

            // Parse hands (simplified - would need proper parsing for nested structures)
            // For now, we'll just initialize empty hands
            // A proper implementation would use a JSON library

            return data;
        }

        std::string SaveData::getTimestamp() const {
            std::tm* tm = std::localtime(&saveTime);
            std::ostringstream oss;
            oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
            return oss.str();
        }

    } // namespace models
} // namespace game
