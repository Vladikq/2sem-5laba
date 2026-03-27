#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

// Функция для создания самолета и его маршрута
void createPlane(map<string, vector<string>>& kal) {
    string plane;
    cout << "Введите название самолета: ";
    cin >> plane;
    
    // Проверка на существование самолета
    while (kal.find(plane) != kal.end()) {
        cout << "Номер самолета уже занят, выберите другой: ";
        cin >> plane;
    }
    
    string numtown;
    cout << "Введите число городов: ";
    cin >> numtown;
    
    // Проверка на корректность ввода числа
    while (true) {
        bool isDigit = true;
        for (char c : numtown) {
            if (!isdigit(c)) {
                isDigit = false;
                break;
            }
        }
        if (!isDigit) {
            cout << "Ошибка. Нельзя использовать буквы. Введите число городов: ";
            cin >> numtown;
        } else {
            break;
        }
    }
    
    int numtown_int = stoi(numtown);
    vector<string> towns;
    
    cout << "Введите названия городов:" << endl;
    for (int i = 0; i < numtown_int; i++) {
        string town;
        cout << "Город " << i + 1 << ": ";
        cin >> town;
        towns.push_back(town);
    }
    
    kal[plane] = towns;
    cout << "Самолет " << plane << " успешно добавлен!" << endl;
}

// Функция для вывода самолетов, пролетающих через указанный город
void planesForTown(const map<string, vector<string>>& kal, const string& town) {
    cout << "Самолеты летающие через " << town << ":" << endl;
    bool found = false;
    
    for (const auto& pair : kal) {
        const vector<string>& towns = pair.second;
        if (find(towns.begin(), towns.end(), town) != towns.end()) {
            cout << "Самолет " << pair.first << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "Нет пролетающих самолетов через " << town << endl;
    }
}

// Функция для вывода городов, которые посещает указанный самолет
// И дополнительно показывает, какие еще самолеты летают через эти города
void townsForPlane(const map<string, vector<string>>& kal, const string& plane) {
    auto it = kal.find(plane);
    if (it != kal.end()) {
        const vector<string>& towns = it->second;
        cout << "Города, через которые пролетает самолет " << plane << ":" << endl;
        cout << "========================================" << endl;
        
        for (const string& town : towns) {
            cout << "\nГород: " << town << endl;
            cout << "Самолеты, пролетающие через " << town << ":" << endl;
            
            bool found = false;
            for (const auto& pair : kal) {
                const vector<string>& planeTowns = pair.second;
                if (find(planeTowns.begin(), planeTowns.end(), town) != planeTowns.end()) {
                    cout << "  - " << pair.first;
                    if (pair.first == plane) {
                        cout << " (текущий самолет)";
                    }
                    cout << endl;
                    found = true;
                }
            }
            
            if (!found) {
                cout << "  - Нет других самолетов" << endl;
            }
        }
        cout << "\n========================================" << endl;
    } else {
        cout << "Самолет " << plane << " не найден." << endl;
    }
}

// Функция для вывода всех самолетов и их маршрутов
void planes(const map<string, vector<string>>& kal) {
    if (kal.empty()) {
        cout << "Список самолетов пуст!" << endl;
        return;
    }
    
    for (const auto& pair : kal) {
        cout << "Самолет " << pair.first << " останавливается в этих городах:" << endl;
        for (const string& town : pair.second) {
            cout << "  - " << town << endl;
        }
        cout << endl;
    }
}

int main() {
    // Настройка кодировки для русского языка
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    system("chcp 65001 > nul");
    
    map<string, vector<string>> kal;  // Словарь: самолет -> список городов
    
    cout << "========================================" << endl;
    cout << "СИСТЕМА УПРАВЛЕНИЯ АВИАПЕРЕВОЗКАМИ" << endl;
    cout << "========================================" << endl;
    cout << "Все команды: CREATE_PLANE, PLANES_FOR_TOWN, TOWNS_FOR_PLANE, PLANES, EXIT" << endl;
    cout << "========================================\n" << endl;
    
    string command;
    while (true) {
        cout << "Введите команду: ";
        cin >> command;
        
        if (command == "CREATE_PLANE") {
            createPlane(kal);
        } 
        else if (command == "PLANES") {
            planes(kal);
        } 
        else if (command == "PLANES_FOR_TOWN") {
            string town;
            cout << "Введите название города: ";
            cin >> town;
            planesForTown(kal, town);
        } 
        else if (command == "TOWNS_FOR_PLANE") {
            string plane;
            cout << "Введите номер самолета: ";
            cin >> plane;
            townsForPlane(kal, plane);
        } 
        else if (command == "EXIT") {
            cout << "Выход из программы..." << endl;
            break;
        } 
        else {
            cout << "Неверный ввод" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    
    return 0;
}
