#include "business_logic.h"
#include <iostream>

bool AuthModule::authenticate(string n, string p) {
    return db.employeeDB.count(n) && db.employeeDB[n].password == p;
}

void AccessController::registerEmployee(string n, string p, string pos) {
    db.employeeDB[n] = {n, p, pos, "Выходной"};
}

void AccessController::updateWorkStatus(string n) {
    if (db.employeeDB.count(n)) {
        db.employeeDB[n].workStatus = (db.employeeDB[n].workStatus == "На смене") ? "Выходной" : "На смене";
    }
}

void AccessController::removeEmployee(string n) {
    db.employeeDB.erase(n);
}

string AccessController::getRole(string n) {
    return db.employeeDB.count(n) ? db.employeeDB[n].position : "";
}

string AccessController::getStatus(string n) {
    return db.employeeDB.count(n) ? db.employeeDB[n].workStatus : "";
}

void PassengerManager::addPassenger(string n, string b) {
    db.passengerDB[db.nextId++] = {n, b};
}

string PassengerManager::processInspection(int id) {
    if (!db.passengerDB.count(id)) return "Не найден";
    if (db.passengerDB[id].baggage == "нож" || db.passengerDB[id].baggage == "оружие")
        db.passengerDB[id].status = "ЗАДЕРЖАН";
    else
        db.passengerDB[id].status = "ДОПУЩЕН";
    return db.passengerDB[id].status;
}

void PassengerManager::generateReport() {
    cout << "\n--- ОТЧЕТ ДОСМОТРА ---" << endl;
    for (auto const& [id, p] : db.passengerDB)
        cout << "ID: " << id << " | " << p.name << " | Статус: " << p.status << endl;
}

