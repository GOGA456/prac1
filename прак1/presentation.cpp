#include "presentation.h"
#include <iostream>
#include <map>

using namespace std;

bool Presentation::authorize() {
    cout << "===== Система безопасности аэропорта =====\n";
    int attempts = 3;
    while (attempts > 0) {
        string name, password;
        cout << "Введите имя: ";
        cin >> name;
        cout << "Введите пароль: ";
        cin >> password;

        if (logic.login(name, password)) {
            currentUser = name;
            cout << "Добро пожаловать, " << currentUser << "!\n";
            return true;
        } else {
            attempts--;
            if (attempts > 0)
                cout << "Неверное имя или пароль. Осталось попыток: " << attempts << "\n";
            else
                cout << "Доступ заблокирован.\n";
        }
    }
    return false;
}

void Presentation::run() {
    if (!authorize())
        return;

    int choice = -1;
    while (choice != 0) {
        cout << "\n--- Меню ---\n";
        cout << "1. Зарегистрировать пассажира\n";
        cout << "2. Провести досмотр багажа\n";
        cout << "3. Отчёт по пассажирам\n";
        cout << "4. Сменить статус смены сотрудника (только начальник)\n";
        cout << "5. Добавить сотрудника (только начальник)\n";
        cout << "6. Список сотрудников\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        if (choice == 1) {
            string name, baggage;
            cout << "Введите имя пассажира: ";
            cin >> name;
            cout << "Введите предмет в багаже: ";
            cin >> baggage;
            logic.registerPassenger(name, baggage);
            cout << "Пассажир успешно добавлен.\n";
        }
        else if (choice == 2) {
            int id;
            cout << "Введите номер пассажира: ";
            cin >> id;
            cout << logic.performSecurityScan(id, currentUser) << "\n";
        }
        else if (choice == 3) {
            map<int, Passenger> passengers = logic.getPassengerReport();
            cout << "\nОтчёт по пассажирам:\n";
            for (auto& p : passengers) {
                cout << "[" << p.first << "] "
                     << p.second.name
                     << " | Багаж: " << p.second.baggage
                     << " | Статус: " << p.second.securityStatus;
                if (!p.second.assignedEmployee.empty())
                    cout << " | Досмотрел: " << p.second.assignedEmployee;
                cout << "\n";
            }
        }
        else if (choice == 4) {
            string target, status;
            cout << "Имя сотрудника: ";
            cin >> target;
            cout << "Новый статус (на смене / выходной): ";
            cin >> status;
            cout << logic.changeShiftStatus(currentUser, target, status) << "\n";
        }
        else if (choice == 5) {
            string name, password, position;
            cout << "Имя нового сотрудника: ";
            cin >> name;
            cout << "Пароль: ";
            cin >> password;
            cout << "Должность (оператор / начальник смены): ";
            cin >> position;
            cout << logic.addEmployee(currentUser, name, password, position) << "\n";
        }
        else if (choice == 6) {
            map<string, Employee> employees = logic.getEmployeeReport();
            cout << "\nСписок сотрудников:\n";
            for (auto& e : employees) {
                cout << "- " << e.second.name
                     << " | Должность: " << e.second.position
                     << " | Статус: " << e.second.shiftStatus << "\n";
            }
        }
    }
}
