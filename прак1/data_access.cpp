#include "data_access.h"

int DataAccess::savePassenger(string name, string baggage) {
    passengers_db[nextPassengerId] = {name, baggage, "Ожидает досмотра", ""};
    return nextPassengerId++;
}

void DataAccess::updatePassengerStatus(int id, string newStatus) {
    if (passengers_db.count(id))
        passengers_db[id].securityStatus = newStatus;
}

void DataAccess::assignEmployee(int id, string employeeName) {
    if (passengers_db.count(id))
        passengers_db[id].assignedEmployee = employeeName;
}

map<int, Passenger> DataAccess::getAllPassengers() {
    return passengers_db;
}

void DataAccess::saveEmployee(string name, string password, string position) {
    employees_db[name] = {name, password, position, "на смене"};
}

void DataAccess::updateShiftStatus(string name, string shiftStatus) {
    if (employees_db.count(name))
        employees_db[name].shiftStatus = shiftStatus;
}

map<string, Employee> DataAccess::getAllEmployees() {
    return employees_db;
}

bool DataAccess::employeeExists(string name) {
    return employees_db.count(name) > 0;
}

string DataAccess::getEmployeePosition(string name) {
    if (employees_db.count(name))
        return employees_db[name].position;
    return "";
}

bool DataAccess::checkPassword(string name, string password) {
    if (employees_db.count(name))
        return employees_db[name].password == password;
    return false;
}
