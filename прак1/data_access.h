#pragma once
#include <string>
#include <map>

using namespace std;

struct Passenger {
    string name;
    string baggage;
    string securityStatus;
    string assignedEmployee;
};

struct Employee {
    string name;
    string password;
    string position;    // "оператор" или "начальник смены"
    string shiftStatus; // "на смене" или "выходной"
};

class DataAccess {
private:
    map<int, Passenger> passengers_db;
    map<string, Employee> employees_db;
    int nextPassengerId = 0;

public:
    int savePassenger(string name, string baggage);
    void updatePassengerStatus(int id, string newStatus);
    void assignEmployee(int id, string employeeName);
    map<int, Passenger> getAllPassengers();

    void saveEmployee(string name, string password, string position);
    void updateShiftStatus(string name, string shiftStatus);
    map<string, Employee> getAllEmployees();
    bool employeeExists(string name);
    string getEmployeePosition(string name);
    bool checkPassword(string name, string password);
};
