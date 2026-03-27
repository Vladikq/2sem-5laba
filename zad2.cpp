#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

void queuePeoples(vector<pair<int, int>>& visitors, int numWindows) {
    vector<int> windowTimes(numWindows, 0);
    vector<int> windowNumbers(numWindows);
    vector<vector<int>> WINDOWS(numWindows);
    
    // Работа с номерами окон
    for (int i = 0; i < numWindows; ++i) {
        windowNumbers[i] = i + 1;
    }

    int numNextPeople = 0; // Номер следующего посетителя

    while (!visitors.empty()) {
        // Находим посетителя с самым большим временем посещения
        auto maxPeopleIndex = max_element(visitors.begin(), visitors.end()) - visitors.begin();

        // Находим индекс окна с минимальным временем работы
        auto minWindowIndex = min_element(windowTimes.begin(), windowTimes.end()) - windowTimes.begin();

        WINDOWS[minWindowIndex].push_back(visitors[maxPeopleIndex].second);

        // Увеличиваем время работы окна на время обслуживания посетителя
        windowTimes[minWindowIndex] += visitors[maxPeopleIndex].first; 

        visitors.erase(visitors.begin() + maxPeopleIndex); // Удаляем посетителя из очереди

        numNextPeople++;
    }

    for (int i = 0; i < WINDOWS.size(); ++i) {
        cout << "Окно " << i+1 << " (" << windowTimes[i] << " минут): ";
        for (auto elem : WINDOWS[i]) {
            cout << "T" << elem << " ";
        }
        cout << endl;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    system("chcp 65001 > nul");
    
    vector<pair<int, int>> Peoples;

    cout << ">>> Введите кол-во рабочих окон:" << endl;
    cout << "<<< ";

    int NumsWindows;
    cin >> NumsWindows;
    cin.ignore(); // Очищаем буфер после ввода числа

    cout << ">>> Для получения талона введите: ENQUEUE и время посещения" << endl;
    cout << "    Для формирования очереди введите: DISTRIBUTE" << endl;
    cout << "    Для выхода введите: EXIT" << endl;

    string command;
    bool k = true;
    int time;
    int talon = 100;

    while (k) {
        cout << "<<< ";
        cin >> command;

        if (command == "ENQUEUE") {
            cin >> time;
            talon += 10;
            cout << ">>> T" << talon << endl;
            Peoples.push_back({time, talon});

        } else if (command == "DISTRIBUTE") {
            if (Peoples.empty()) {
                cout << ">>> Очередь пуста!" << endl;
            } else {
                queuePeoples(Peoples, NumsWindows);
            }

        } else if (command == "EXIT") {
            cout << ">>> Выход..." << endl;
            k = false;

        } else {
            cout << ">>> Команда введена неверно" << endl;
            // Очищаем буфер при ошибке
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    return 0;
}
