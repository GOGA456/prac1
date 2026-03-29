#pragma once
#include "data_access.h"
#include <string>
#include <map>

using namespace std;

class BusinessLogic {
private:
    DataAccess dataAccess;

public:
    BusinessLogic();

    // Авторизация
    bool login(string name, string password);

    // Операции с пассажирами
    void registerPassenger(string name, string baggage);
    string performSecurityScan(int id, string employeeName);
    map<int, Passenger> getPassengerReport();

    // Операции с сотрудниками
    string changeShiftStatus(string requestedBy, string targetName, string newStatus);
    string addEmployee(string requestedBy, string name, string password, string position);
    map<string, Employee> getEmployeeReport();
};
