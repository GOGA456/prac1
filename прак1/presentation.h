#ifndef PRESENTATION_H
#define PRESENTATION_H

#include "business_logic.h"

class Presentation {
    AuthModule& auth;
    AccessController& access;
    PassengerManager& pm;
    string currentUser;
public:
    Presentation(AuthModule& a, AccessController& ac, PassengerManager& p);
    bool loginForm();
    void mainMenu();
    void regForm();
    void statusForm();
    void delForm();
    void baggageForm();
    void inspectForm();
};

#endif
