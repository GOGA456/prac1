#ifndef DATA_ACCESS_H
#define DATA_ACCESS_H

#include <string>
#include <map>

using namespace std;

struct Employee {
    string name, password, position, workStatus;
};

struct Passenger {
    string name, baggage, status = "В ожидании";
};

class DataAccess {
public:
    map<string, Employee> employeeDB;
    map<int, Passenger> passengerDB;
    int nextId;
    DataAccess();
};

#endif

