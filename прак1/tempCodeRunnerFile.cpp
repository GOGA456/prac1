#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Passenger {
    string name;         
    string baggage;       
    string securityStatus;    
};

class DataAccess {
private:
    vector<Passenger> passengerInformation; 

public:
    void savePassengerInformation(string name, string item) {
        passengerInformation.push_back({name, item, "Ожидает досмотра"});
    }
    void updateSecurityStatus(int recordIndex, string newStatus) {
        passengerInformation[recordIndex].securityStatus = newStatus;
    }
    vector<Passenger> findAllPassengers() {
        return passengerInformation;
    }
};

class BusinessLogic {
private:
    DataAccess dataAccessModule;
public:
    void registerNewPassenger(string name, string item) {
        dataAccessModule.savePassengerInformation(name, item);
    }
    string makeSecurityScan(int passengerIndex) {
        vector<Passenger> allPassengers = dataAccessModule.findAllPassengers();
        
        if (passengerIndex < 0 || passengerIndex >= allPassengers.size()) {
            return "Ошибка: Пассажир с таким номером не найден!";
        }

        string checkedItem = allPassengers[passengerIndex].baggage;

        if (checkedItem == "оружие" || checkedItem == "нож" || checkedItem == "взрывчатка") {
            dataAccessModule.updateSecurityStatus(passengerIndex, "ЗАДЕРЖАН");
            return "Тревога! Обнаружен запрещенный предмет.";
        } else {
            dataAccessModule.updateSecurityStatus(passengerIndex, "ДОПУЩЕН НА РЕЙС");
            return "Досмотр пройден успешно.";
        }
    }
    vector<Passenger> generateSecurityReport() {
        return dataAccessModule.findAllPassengers();
    }
};

class Presentation {
private:
    BusinessLogic securityLogicModule; 

public:
    void runApplicationMenu() {
        int userChoice = -1;
        
        while (userChoice != 0) {
            cout << "1. Зарегистрировать пассажира\n";
            cout << "2. Провести досмотр багажа\n";
            cout << "3. Показать отчет по всем пассажирам\n";
            cout << "0. Выход\n";
            cout << "Выберите действие: ";
            cin >> userChoice;

            if (userChoice == 1) {
                string inputName, inputBaggage;
                cout << "Введите имя пассажира: "; 
                cin >> inputName;
                cout << "Введите предмет в багаже: "; 
                cin >> inputBaggage;
                
                securityLogicModule.registerNewPassenger(inputName, inputBaggage);
                cout << "Пассажир успешно добавлен в систему контроля.\n";
            } 
            else if (userChoice == 2) {
                int inputIndex;
                cout << "Введите номер пассажира для досмотра (начиная с 0): "; 
                cin >> inputIndex;
                
                string scanResult = securityLogicModule.makeSecurityScan(inputIndex);
                cout << scanResult << "\n";
            } 
            else if (userChoice == 3) {
                vector<Passenger> passengerList = securityLogicModule.generateSecurityReport();
                
                cout << "\nОтчет службы безопасности:\n";
                for (int i = 0; i < passengerList.size(); i++) {
                    cout << "[" << i << "] Пассажир: " << passengerList[i].name 
                         << " | Багаж: " << passengerList[i].baggage 
                         << " | Статус: " << passengerList[i].securityStatus << "\n";
                }
            }
        }
    }
};

int main() {    
    Presentation airportSecurityApp;
    airportSecurityApp.runApplicationMenu();
    return 0;
}
