#pragma once
#include <map>
#include <vector>
#include <string>

class DialogueSystem {
private:
    std::map<std::string, std::vector<std::string>> dialogues;
public:
    void loadDialogues(const std::string& filePath);
    void startDialogue(const std::string& npcName);
};