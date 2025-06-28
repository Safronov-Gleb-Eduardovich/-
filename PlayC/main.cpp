#include <iostream>
#include <locale>
#include<fstream>
#include <conio.h> 
#include <vector>
#include <Windows.h>


class StaticMenu {
private:

    std::vector<std::string> items;
    int selected = 0;
    HANDLE hConsole;

    void showMenu() {

        COORD pos = { 0, 18 };
        SetConsoleCursorPosition(hConsole, pos);
        DWORD written;
        FillConsoleOutputCharacter(hConsole, ' ', 80 * (25 - 18), pos, &written);

        for (int i = 0; i < items.size(); ++i) {
            SetConsoleCursorPosition(hConsole, { 45, (SHORT)(8 + i) });
            std::cout << (i == selected ? "> " : "  ") << items[i];
        }
    }

public:
    StaticMenu(const std::vector<std::string>& options) : items(options) {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };
        SetConsoleCursorInfo(hConsole, &cursorInfo);

        SetConsoleCursorPosition(hConsole, { 0, 18 });
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
    SetConsoleOutputCP(CP_UTF8);  // Устанавливаем UTF-8 для вывода
    SetConsoleCP(CP_UTF8);       // Устанавливаем UTF-8 для ввода
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Получаем хэндл консоли
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Меняем цвет текста на зелёный
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

    std::ifstream file("C:\\Users\\User\\Downloads\\sec.txt", std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл!" << std::endl;
        return 1;
    }

    // Перемещаем указатель в конец файла, чтобы узнать его размер
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Читаем весь файл в строку
    std::string buffer(size, '\0');
    if (file.read(&buffer[0], size)) {
        // Выводим всё содержимое сразу
        std::cout << buffer;
    }

    file.close();

    //Явно прописана кодировка utf-8  
    std::vector<std::string> options = {
        u8"1. Зайти в универ.",
        u8"2. Не сегодня. Пары? Сегодня я их для себя отменил."
    };

    StaticMenu menu(options);
    int choice = menu.run();
    system("cls");

    SetConsoleCursorPosition(hConsole, { 0, 0 });  // Устанавливаем курсор в начало

    if (choice == 0) {

        std::cout << u8"Привет\n";
    }

    return 0;
}