#include "business_logic.h"

BusinessLogic::BusinessLogic() {
    dataAccess.saveEmployee("Иванов", "1234", "начальник смены");
    dataAccess.saveEmployee("Петров", "5678", "оператор");
    dataAccess.saveEmployee("Сидорова", "9999", "оператор");
}

bool BusinessLogic::login(string name, string password) {
    if (!dataAccess.employeeExists(name))
        return false;
    return dataAccess.checkPassword(name, password);
}

void BusinessLogic::registerPassenger(string name, string baggage) {
    dataAccess.savePassenger(name, baggage);
}

string BusinessLogic::performSecurityScan(int id, string employeeName) {
    map<int, Passenger> passengers = dataAccess.getAllPassengers();
    if (!passengers.count(id))
        return "Ошибка: пассажир с таким номером не найден.";

    string item = passengers[id].baggage;
    dataAccess.assignEmployee(id, employeeName);

    if (item == "оружие" || item == "нож" || item == "взрывчатка") {
        dataAccess.updatePassengerStatus(id, "ЗАДЕРЖАН");
        return "Тревога! Обнаружен запрещённый предмет. Досмотр провёл: " + employeeName;
    } else {
        dataAccess.updatePassengerStatus(id, "ДОПУЩЕН НА РЕЙС");
        return "Досмотр пройден успешно. Досмотр провёл: " + employeeName;
    }
}

map<int, Passenger> BusinessLogic::getPassengerReport() {
    return dataAccess.getAllPassengers();
}

string BusinessLogic::changeShiftStatus(string requestedBy, string targetName, string newStatus) {
    if (dataAccess.getEmployeePosition(requestedBy) != "начальник смены")
        return "Ошибка: недостаточно прав. Только начальник смены может менять статус.";
    if (!dataAccess.employeeExists(targetName))
        return "Ошибка: сотрудник не найден.";
    dataAccess.updateShiftStatus(targetName, newStatus);
    return "Статус сотрудника " + targetName + " обновлён: " + newStatus;
}

string BusinessLogic::addEmployee(string requestedBy, string name, string password, string position) {
    if (dataAccess.getEmployeePosition(requestedBy) != "начальник смены")
        return "Ошибка: недостаточно прав. Только начальник смены может добавлять сотрудников.";
    dataAccess.saveEmployee(name, password, position);
    return "Сотрудник " + name + " добавлен.";
}

map<string, Employee> BusinessLogic::getEmployeeReport() {
    return dataAccess.getAllEmployees();
}
