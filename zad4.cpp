#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

// Функция для получения количества дней в месяце
int getDaysInMonth(int month, int year) {
    if (month == 2) { // Февраль
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            return 29; // Високосный год
        } else {
            return 28; // Невисокосный год
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30; // Апрель, июнь, сентябрь, ноябрь
    } else {
        return 31; // Остальные месяцы
    }
}

// Функция для корректировки дня при переносе
int adjustDay(int day, int targetMonth, int targetYear) {
    int daysInTargetMonth = getDaysInMonth(targetMonth, targetYear);
    
    // Если день больше, чем дней в целевом месяце, ставим предпоследний день
    if (day > daysInTargetMonth) {
        return daysInTargetMonth - 1;  // Предпоследний день
    }
    return day;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    system("chcp 65001 > nul");
    
    vector<pair<int, string>> schedule;
    
    // Текущие месяц и год
    int currentMonth = 1;  // Январь
    int currentYear = 2024;
    
    cout << "========================================" << endl;
    cout << "СИСТЕМА УПРАВЛЕНИЯ РАСПИСАНИЕМ" << endl;
    cout << "========================================" << endl;
    cout << "Текущий месяц: Январь 2024" << endl;
    cout << "Правила переноса:" << endl;
    cout << "  - Если число существует в следующем месяце - переносится на то же число" << endl;
    cout << "  - Если числа нет - переносится на предпоследний день месяца" << endl;
    cout << "========================================\n" << endl;

    while (true) {
        int N;
        cout << "Введите число операций: ";
        
        if (!(cin >> N)) {
            cout << "Ошибка: введите корректное число!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        
        cin.ignore();

        string operation;
        for (int i = 0; i < N; ++i) {
            cout << "Введите операцию: ";
            cin >> operation;

            if (operation == "CLASS") {
                string discipline;
                int day;
                cout << "Введите номер дня и название предмета: ";
                cin >> day >> discipline;
                
                // Проверка корректности дня
                int daysInMonth = getDaysInMonth(currentMonth, currentYear);
                if (day < 1 || day > daysInMonth) {
                    cout << "Ошибка: в этом месяце только " << daysInMonth << " дней!" << endl;
                    cin.ignore();
                    continue;
                }
                
                schedule.push_back(make_pair(day, discipline));
                cout << "Добавлено: " << day << "." << currentMonth << "." << currentYear << " - " << discipline << endl;
                cin.ignore();
            } 
            else if (operation == "NEXT") {
                if (schedule.empty()) {
                    cout << "Расписание пусто!" << endl;
                    continue;
                }
                
                // Переходим на следующий месяц
                int nextMonth = currentMonth + 1;
                int nextYear = currentYear;
                if (nextMonth > 12) {
                    nextMonth = 1;
                    nextYear++;
                }
                
                cout << "\n=== ПЕРНОС ЗАНЯТИЙ ===" << endl;
                
                // Переносим каждое занятие
                for (auto& cls : schedule) {
                    int oldDay = cls.first;
                    int newDay = adjustDay(oldDay, nextMonth, nextYear);
                    int daysInNextMonth = getDaysInMonth(nextMonth, nextYear);
                    
                    // Выводим информацию о переносе
                    if (oldDay > daysInNextMonth) {
                        cout << "  " << oldDay << "." << currentMonth << "." << currentYear 
                             << " -> " << newDay << "." << nextMonth << "." << nextYear 
                             << " (числа " << oldDay << " нет в следующем месяце, перенос на предпоследний день)" << endl;
                    } else {
                        cout << "  " << oldDay << "." << currentMonth << "." << currentYear 
                             << " -> " << newDay << "." << nextMonth << "." << nextYear << endl;
                    }
                    
                    cls.first = newDay;
                }
                
                // Обновляем текущий месяц и год
                currentMonth = nextMonth;
                currentYear = nextYear;
                
                cout << "\nПеренос всех занятий на следующий месяц (" 
                     << currentMonth << "." << currentYear << ") выполнен." << endl;
            } 
            else if (operation == "VIEW") {
                int day;
                cout << "Введите номер дня: ";
                cin >> day;
                
                if (cin.fail()) {
                    cout << "Ошибка: введите корректный номер дня!" << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    continue;
                }
                
                // Проверка корректности дня
                int daysInMonth = getDaysInMonth(currentMonth, currentYear);
                if (day < 1 || day > daysInMonth) {
                    cout << "Ошибка: в этом месяце только " << daysInMonth << " дней!" << endl;
                    cin.ignore();
                    continue;
                }

                // Собираем все предметы на указанный день
                vector<string> subjects;
                for (const auto& item : schedule) {
                    if (item.first == day) {
                        subjects.push_back(item.second);
                    }
                }

                cout << day << "." << currentMonth << "." << currentYear << ": ";
                if (!subjects.empty()) {
                    for (size_t j = 0; j < subjects.size(); ++j) {
                        cout << subjects[j];
                        if (j < subjects.size() - 1) {
                            cout << ", ";
                        }
                    }
                } else {
                    cout << "Нет занятий";
                }
                cout << endl;
                cin.ignore();
            } 
            else if (operation == "MONTH") {
                const char* months[] = {"Январь", "Февраль", "Март", "Апрель", "Май", "Июнь",
                                        "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};
                cout << "Текущий месяц: " << months[currentMonth-1] << " " << currentYear << endl;
                cout << "Дней в месяце: " << getDaysInMonth(currentMonth, currentYear) << endl;
            }
            else if (operation == "EXIT") {
                cout << "Программа завершает работу." << endl;
                return 0;
            }
            else {
                cout << "Неизвестная операция! Доступные: CLASS, VIEW, NEXT, MONTH, EXIT" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
    }

    return 0;
}
