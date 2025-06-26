#include <iostream>
#include <locale>
#include "World.h"
#include "Player.h"
#include "CombatSystem.h"
#include "DialogueSystem.h"
#include <conio.h> 
#include <vector>
#include <Windows.h>

class StaticMenu {
private:
    std::vector<std::string> items;
    int selected = 0;
    HANDLE hConsole;

    void showMenu() {
        COORD pos = { 0, 2 };
        SetConsoleCursorPosition(hConsole, pos);
        DWORD written;
        FillConsoleOutputCharacter(hConsole, ' ', 80 * 25, pos, &written);

        for (int i = 0; i < items.size(); ++i) {
            SetConsoleCursorPosition(hConsole, { 0, (SHORT)(2 + i) });
            std::cout << (i == selected ? "> " : "  ") << items[i];
        }
    }

public:
    StaticMenu(const std::vector<std::string>& options) : items(options) {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };
        SetConsoleCursorInfo(hConsole, &cursorInfo);

        SetConsoleCursorPosition(hConsole, { 0, 0 });
        std::cout << "--> Меню <--";
    }

    int run() {
        showMenu();

        while (true) {
            if (GetAsyncKeyState(VK_UP) & 0x8000) {
                if (selected > 0) {
                    selected--;
                    showMenu();
                    while (GetAsyncKeyState(VK_UP) & 0x8000);
                }
            }
            else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
                if (selected < items.size() - 1) {
                    selected++;
                    showMenu();
                    while (GetAsyncKeyState(VK_DOWN) & 0x8000);
                }
            }
            else if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
                return selected;
            }

            Sleep(10);
        }
    }
};

int main() {
    setlocale(LC_ALL, "RUS");

    std::vector<std::string> options = {
        "1. Зайти в универ.",
        "2. Не сегодня! Пары? Их я сегодня для себя отменил."
    };

    StaticMenu menu(options);
    int choice = menu.run();
    system("cls");
    std::cout << "\n";

    if (choice == 0) {
        std::locale::global(std::locale{ ".UTF-8" });
        std::cout.imbue(std::locale("ru_RU.UTF-8"));
        try {
            World world("university_map.json");
            Player player(world.getStartRoom());

            DialogueSystem dialogues;
            try {
                dialogues.loadDialogues("dialogues.json");
            }
            catch (const std::exception& e) {
                std::cerr << "Ошибка загрузки диалогов: " << e.what() << std::endl;
            }

            // Добавляем стартовые предметы
            player.addItem(Item("ultrasonic_remote", 5));
            player.addItem(Item("flamethrower", 10));
            player.addItem(Item("battery", 3));

            while (true) {
                // Отображение текущей комнаты
                std::cout << "--- " << player.getCurrentRoom()->name << " ---\n";
                std::cout << player.getCurrentRoom()->description << "\n";

                // Проверка на врагов
                if (!player.getCurrentRoom()->enemies.empty()) {
                    Enemy enemy(player.getCurrentRoom()->enemies[0], "flamethrower", 30);
                    CombatSystem::fight(player, enemy);
                }

                // Ввод команды
                std::string command;
                std::cout << "> ";
                std::cin >> command;

                if (command == "идти") {
                    std::string direction;
                    std::cin >> direction;
                    player.move(direction);
                }
                else if (command == "инвентарь") {
                    player.showInventory();
                }
                else if (command == "перезарядить") {
                    std::string itemName;
                    int amount;
                    std::cin >> itemName >> amount;
                    player.rechargeItem(itemName, amount);
                }
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Критическая ошибка: " << e.what() << std::endl;
            return 1;
        }
        return 0;
    }
    else {
        return 0;
    }
}
    