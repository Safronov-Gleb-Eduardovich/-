#include "DialogueSystem.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

void DialogueSystem::loadDialogues(const std::string& filePath) {
    std::ifstream file(filePath);
    nlohmann::json data = nlohmann::json::parse(file);
    dialogues = data.get<std::map<std::string, std::vector<std::string>>>();
}

void DialogueSystem::startDialogue(const std::string& npcName) {
    if (dialogues.count(npcName)) {
        for (const auto& line : dialogues[npcName]) {
            std::cout << line << "\n";
        }
    }
}