#include "presentation.h"


int main() {

    DataAccess db;
    AuthModule auth(db);
    AccessController access(db);
    PassengerManager pm(db);
    Presentation app(auth, access, pm);

    if (app.loginForm()) app.mainMenu();
    return 0;
}
