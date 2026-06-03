#ifndef SAVEMANAGER_HPP
#define SAVEMANAGER_HPP

#include "models/SaveData.hpp"
#include "core/Entity.hpp"
#include <string>
#include <vector>

namespace game {
    namespace models {

        /**
         * @brief Manages game save/load operations
         *
         * Handles file I/O for saving and loading game state.
         * Supports multiple save slots and auto-save functionality.
         */
        class SaveManager : public core::Entity {
        public:
            static const int MAX_SAVE_SLOTS = 5;

            SaveManager();
            explicit SaveManager(const std::string& saveDirectory);

            /**
             * @brief Initialize the save manager
             */
            void init();

            /**
             * @brief Save game data to a specific slot
             * @param slot The save slot number (1-5)
             * @param data The save data to write
             * @return true if save was successful
             */
            bool saveToSlot(int slot, const SaveData& data);

            /**
             * @brief Load game data from a specific slot
             * @param slot The save slot number (1-5)
             * @param data Output parameter for loaded data
             * @return true if load was successful
             */
            bool loadFromSlot(int slot, SaveData& data);

            /**
             * @brief Check if a save slot has valid data
             * @param slot The save slot number (1-5)
             * @return true if the slot contains valid save data
             */
            bool slotExists(int slot) const;

            /**
             * @brief Delete a save slot
             * @param slot The save slot number (1-5)
             * @return true if deletion was successful
             */
            bool deleteSlot(int slot);

            /**
             * @brief Get save data metadata for a slot
             * @param slot The save slot number (1-5)
             * @return SaveData with metadata, or empty if slot doesn't exist
             */
            SaveData getSlotInfo(int slot) const;

            /**
             * @brief Get all save slot information
             * @return Vector of save data for all slots (empty slots return default SaveData)
             */
            std::vector<SaveData> getAllSlotInfo() const;

            /**
             * @brief Perform auto-save to slot 1
             * @param data The save data to write
             * @return true if save was successful
             */
            bool autoSave(const SaveData& data);

            /**
             * @brief Load most recent auto-save
             * @param data Output parameter for loaded data
             * @return true if load was successful
             */
            bool loadAutoSave(SaveData& data);

            /**
             * @brief Get the save directory path
             */
            std::string getSaveDirectory() const { return m_saveDirectory; }

        private:
            std::string m_saveDirectory;

            /**
             * @brief Get the file path for a save slot
             */
            std::string getSlotFilePath(int slot) const;

            /**
             * @brief Create save directory if it doesn't exist
             */
            void ensureSaveDirectoryExists();

            /**
             * @brief Write data to file
             */
            bool writeToFile(const std::string& filePath, const std::string& content);

            /**
             * @brief Read data from file
             */
            bool readFromFile(const std::string& filePath, std::string& content);
        };

    } // namespace models
} // namespace game

#endif // SAVEMANAGER_HPP
