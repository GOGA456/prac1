#pragma once
#include "business_logic.h"
#include <string>

using namespace std;

class Presentation {
private:
    BusinessLogic logic;
    string currentUser;

    bool authorize();
    void showMenu();

public:
    void run();
};
