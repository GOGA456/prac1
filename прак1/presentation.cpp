#include "presentation.h"
#include <iostream>

using namespace std;

Presentation::Presentation(AuthModule& a, AccessController& ac, PassengerManager& p) : auth(a), access(ac), pm(p) {}

bool Presentation::loginForm() {
    string n, p;
    cout << "Логин: "; cin >> n;
    cout << "Пароль: "; cin >> p;
    if (auth.authenticate(n, p)) { currentUser = n; return true; }
    return false;
}

void Presentation::mainMenu() {
    int v = -1;
    while (v != 0) {
        cout << "\n1. Регистрация сотрудника\n2. Сменить статус (На смене/Выходной)\n3. Удалить сотрудника\n4. Оформить багаж\n5. Провести досмотр\n6. Отчет\n0. Выход\n> ";
        cin >> v;
        if (v == 1) regForm();
        else if (v == 2) statusForm();
        else if (v == 3) delForm();
        else if (v == 4) baggageForm();
        else if (v == 5) inspectForm();
        else if (v == 6) pm.generateReport();
    }
}

void Presentation::regForm() {
    if (access.getRole(currentUser) != "Начальник смены") { cout << "Нет прав!" << endl; return; }
    string n, p, pos;
    cout << "Логин: "; cin >> n; cout << "Пароль: "; cin >> p; cout << "Должность: "; cin >> pos;
    access.registerEmployee(n, p, pos);
}

void Presentation::statusForm() {
    if (access.getRole(currentUser) != "Начальник смены") { cout << "Нет прав!" << endl; return; }
    string n;
    cout << "Логин сотрудника: "; cin >> n;
    access.updateWorkStatus(n);
    cout << "Новый статус: " << access.getStatus(n) << endl;
}

void Presentation::delForm() {
    if (access.getRole(currentUser) != "Начальник смены") { cout << "Нет прав!" << endl; return; }
    string n; cout << "Логин: "; cin >> n;
    access.removeEmployee(n);
}

void Presentation::baggageForm() {
    string n, b;
    cout << "Пассажир: "; cin >> n; cout << "Багаж: "; cin >> b;
    pm.addPassenger(n, b);
}

void Presentation::inspectForm() {
    int id; cout << "ID: "; cin >> id;
    cout << "Результат: " << pm.processInspection(id) << endl;
}
