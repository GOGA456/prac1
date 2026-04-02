#ifndef BUSINESS_LOGIC_H
#define BUSINESS_LOGIC_H

#include "data_access.h"

class AuthModule {
    DataAccess& db;
public:
    AuthModule(DataAccess& d) : db(d) {}
    bool authenticate(string n, string p);
};

class AccessController {
    DataAccess& db;
public:
    AccessController(DataAccess& d) : db(d) {}
    void registerEmployee(string n, string p, string pos);
    void updateWorkStatus(string n);
    void removeEmployee(string n);
    string getRole(string n);
    string getStatus(string n);
};

class PassengerManager {
    DataAccess& db;
public:
    PassengerManager(DataAccess& d) : db(d) {}
    void addPassenger(string n, string b);
    string processInspection(int id);
    void generateReport();
};

#endif
