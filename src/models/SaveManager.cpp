#include "models/SaveManager.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>

#ifdef _WIN32
#include <direct.h>
#include <stdlib.h>
#define mkdir_recursive(path, mode) _mkdir(path)
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

namespace game {
    namespace models {

        SaveManager::SaveManager()
            : Entity("SaveManager"), m_saveDirectory("saves") {
        }

        SaveManager::SaveManager(const std::string& saveDirectory)
            : Entity("SaveManager"), m_saveDirectory(saveDirectory) {
        }

        void SaveManager::init() {
            ensureSaveDirectoryExists();
        }

        std::string SaveManager::getSlotFilePath(int slot) const {
            return m_saveDirectory + "/save_slot_" + std::to_string(slot) + ".json";
        }

        void SaveManager::ensureSaveDirectoryExists() {
            // Try to create the directory
            #ifdef _WIN32
            _mkdir(m_saveDirectory.c_str());
            #else
            mkdir(m_saveDirectory.c_str(), 0755);
            #endif
        }

        bool SaveManager::writeToFile(const std::string& filePath, const std::string& content) {
            std::ofstream file(filePath);
            if (!file.is_open()) {
                return false;
            }

            file << content;
            file.close();
            return file.good();
        }

        bool SaveManager::readFromFile(const std::string& filePath, std::string& content) {
            std::ifstream file(filePath);
            if (!file.is_open()) {
                return false;
            }

            std::stringstream buffer;
            buffer << file.rdbuf();
            content = buffer.str();
            file.close();

            return true;
        }

        bool SaveManager::saveToSlot(int slot, const SaveData& data) {
            if (slot < 1 || slot > MAX_SAVE_SLOTS) {
                return false;
            }

            ensureSaveDirectoryExists();
            std::string filePath = getSlotFilePath(slot);
            std::string json = data.toJSON();

            return writeToFile(filePath, json);
        }

        bool SaveManager::loadFromSlot(int slot, SaveData& data) {
            if (slot < 1 || slot > MAX_SAVE_SLOTS) {
                return false;
            }

            std::string filePath = getSlotFilePath(slot);
            std::string json;

            if (!readFromFile(filePath, json)) {
                return false;
            }

            data = SaveData::fromJSON(json);
            return true;
        }

        bool SaveManager::slotExists(int slot) const {
            if (slot < 1 || slot > MAX_SAVE_SLOTS) {
                return false;
            }

            std::string filePath = getSlotFilePath(slot);
            std::ifstream file(filePath);
            return file.good();
        }

        bool SaveManager::deleteSlot(int slot) {
            if (slot < 1 || slot > MAX_SAVE_SLOTS) {
                return false;
            }

            std::string filePath = getSlotFilePath(slot);
            return std::remove(filePath.c_str()) == 0;
        }

        SaveData SaveManager::getSlotInfo(int slot) const {
            SaveData info;

            if (!slotExists(slot)) {
                return info; // Return default (empty) SaveData
            }

            std::string filePath = getSlotFilePath(slot);
            std::string json;

            // We need to cast away const to use readFromFile
            SaveManager* nonConstThis = const_cast<SaveManager*>(this);
            if (nonConstThis->readFromFile(filePath, json)) {
                info = SaveData::fromJSON(json);
            }

            return info;
        }

        std::vector<SaveData> SaveManager::getAllSlotInfo() const {
            std::vector<SaveData> allInfo;

            for (int i = 1; i <= MAX_SAVE_SLOTS; ++i) {
                allInfo.push_back(getSlotInfo(i));
            }

            return allInfo;
        }

        bool SaveManager::autoSave(const SaveData& data) {
            return saveToSlot(1, data);
        }

        bool SaveManager::loadAutoSave(SaveData& data) {
            return loadFromSlot(1, data);
        }

    } // namespace models
} // namespace game
