#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <windows.h>
#include <algorithm>
#include <sstream>

using namespace std;

// Структура для хранения товара
struct item {
    string name;      
    int quantity;     
};

// Класс склад
class sklad {
private:
    map<string, item> storage;  
    vector<char> zonees;        
    
public:
    // Функция добавления товара на склад
    void add(string address, string name, int quantity) {
        if (storage.count(address) != 0) {
            if (storage[address].name != name && storage[address].name != "") {
                cout << "Ошибка, ячейка занята!" << endl;
            } else {
                // Проверяем, хватает ли места в ячейке (максимум 10)
                if (storage[address].quantity + quantity <= 10) {
                    // Добавляем товар
                    storage[address] = {name, storage[address].quantity + quantity};
                    cout << "Добавлено " << quantity << " '" << name << "' в " << address << endl;
                } else {
                    cout << "Ошибка, не хватает места в ячейке!" << endl;
                }
            }
        } else {
            cout << "Ошибка, нет такой ячейки!" << endl;
        }
    }

    // Функция удаления товара со склада
    void remove(string address, int quantity) {
        if (storage.count(address) != 0) {
            if (storage[address].quantity - quantity == 0) {
                storage[address] = {"", 0};
                cout << "Удалено " << quantity << " из " << address << endl;
            } else if (storage[address].quantity - quantity > 0) {
                storage[address].quantity -= quantity;
                cout << "Удалено " << quantity << " из " << address << endl;
            } else {

                cout << "Ошибка, не хватает продуктов для удаления!" << endl;
            }
        } else {
            cout << "Ошибка, нет такой ячейки!" << endl;
        }
    }

    // Функция вывода информации о складе
    void info() {
        cout << "\n========================================" << endl;
        cout << "ИНФОРМАЦИЯ О СКЛАДЕ" << endl;
        cout << "========================================" << endl;
        cout << "Адрес\tТовар\t\tКоличество" << endl;
        cout << "----------------------------------------" << endl;
        
        float занято = 0.0;  // Счетчик занятых ячеек
        
        // Выводим только непустые ячейки
        for (auto i : storage) {
            if (i.second.quantity != 0) {
                cout << i.first << "\t" << i.second.name << "\t\t" << i.second.quantity << endl;
                занято++;
            }
        }

        float всего = storage.size();  // Общее количество ячеек
        
        // Выводим общую загруженность склада
        cout << "----------------------------------------" << endl;
        cout << "Загруженность склада: ";
        cout << fixed << setprecision(2) << (занято/всего)*100 << "%" << endl;

        // Вычисляем загруженность по зонам
        float ячеекВЗоне = всего / zonees.size();  
        vector<float> занятоВЗоне(zonees.size(), 0);  
        
        // Подсчитываем занятые ячейки в каждой зоне
        cout << "\nЗагруженность по зонам:" << endl;
        for (int i = 0; i < zonees.size(); ++i) {
            for (auto j : storage) {
                // Проверяем, принадлежит ли ячейка текущей зоне и не пуста ли она
                if(j.first[0] == zonees[i] && j.second.quantity > 0) {
                    занятоВЗоне[i]++;
                }
            }
        }
        
        // Выводим загруженность каждой зоны
        for (int i = 0; i < занятоВЗоне.size(); ++i) {
            cout << "  Зона " << zonees[i] << ": ";
            cout << fixed << setprecision(2) << (занятоВЗоне[i]/ячеекВЗоне)*100 << "%" << endl;
        }

        // Выводим список пустых ячеек
        cout << "\nПустые ячейки: ";
        bool первый = true;
        for (auto i : storage) {
            if (i.second.quantity == 0) {
                if (!первый) cout << ", ";
                cout << i.first;
                первый = false;
            }
        }
        if (первый) cout << "нет";
        cout << "\n========================================\n" << endl;
    }

    // Функция генерации всех адресов склада
    void GenerationAddress() {
        vector<char> zones = {'A', 'B', 'C'};  
        zonees = zones;  
        
        // Генерируем адреса: зона + стеллаж + секция + полка
        for (auto i : zones) {
            for (int полка = 1; полка <= 5; ++полка) {      
                for (int секция = 1; секция <= 5; ++секция) {  
                    for (int стеллаж = 1; стеллаж <= 3; ++стеллаж) {  
                        // Создаем адрес (например: A111)
                        stringstream s;
                        s << i << стеллаж << секция << полка;
                        storage[s.str()] = {"", 0};  
                    }
                }
            }
        }
    }
};

int main() {

    SetConsoleCP(65001);      
    SetConsoleOutputCP(65001); 
    system("chcp 65001");     
    
    sklad warehouse;          
    warehouse.GenerationAddress();  

    cout << "========================================" << endl;
    cout << "СИСТЕМА УПРАВЛЕНИЯ СКЛАДОМ" << endl;
    cout << "========================================" << endl;
    cout << "Команды:" << endl;
    cout << "  ADD <адрес> <товар> <количество> - добавить товар" << endl;
    cout << "  REMOVE <адрес> <количество> - удалить товар" << endl;
    cout << "  INFO - показать информацию" << endl;
    cout << "  EXIT - выход" << endl;
    cout << "========================================" << endl;
    cout << "Пример: ADD A111 Молоко 5" << endl;
    cout << "Формат адреса: A111 (зона A, стеллаж 1, секция 1, полка 1)" << endl;
    cout << "Максимум в ячейке: 10 единиц" << endl;
    cout << "========================================\n" << endl;

    string command;  // Переменная для хранения команды
    
    // Основной цикл программы
    while (true) {
        cout << "> ";  
        cin >> command;  
        
        // Обработка команды ADD (добавление товара)
        if (command == "ADD") {
            string address, product;
            int quantity;
            cin >> address >> product >> quantity;
            warehouse.add(address, product, quantity);
        } 
        else if (command == "REMOVE") {
            string address;
            int quantity;
            cin >> address >> quantity;
            warehouse.remove(address, quantity);
        } 
        else if (command == "EXIT") {
            cout << "Выход из программы..." << endl;
            break;
        } 
        else if (command == "INFO") {
            warehouse.info();
        } 
        else {
            cout << "Ошибка! Доступные команды: ADD, REMOVE, INFO, EXIT" << endl;
            cin.clear();  // Сбрасываем флаг ошибки
            cin.ignore(10000, '\n');  // Очищаем буфер ввода
        }
    }

    return 0;  
}
