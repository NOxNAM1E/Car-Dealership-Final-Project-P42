#include <iostream>
#include <conio.h>
#include "ConsoleUtils.h"
#include "Company.h"
using namespace std;

int main() {
    CarDealership dealer;
    string currentFile = "Dealership_01-List"; // поточний файл
    dealer.loadFromFile(currentFile);

    const string menuItems[] = {
        "Add employee",
        "Remove employee",
        "Show employees",
        "Add car",
        "Remove car",
        "Show cars",
        "Add sale",
        "Remove sale",
        "Show sales",
        "Show all information",
        "Save to current file",
        "Save to new file",
        "Load from file",
        "Exit"
    };
    const int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);

    int choice = 0;
    bool running = true;

    ShowConsoleCursor(false);

    while (running) {
        system("cls");
        cout << "===== Car Dealership Menu =====\n";
        cout << "Current file: " << currentFile << "\n\n";

        for (int i = 0; i < menuSize; i++) {
            if (i == choice) {
                SetColor(BLACK, YELLOW);
                cout << "> " << menuItems[i] << endl;
                SetColor(GREY, BLACK);
            }
            else {
                cout << "  " << menuItems[i] << endl;
            }
        }

        int key = _getch();
        if (key == 224) key = _getch(); // для стрілок

        switch (key) {
        case 72: // UP
            choice--;
            if (choice < 0) choice = menuSize - 1;
            break;
        case 80: // DOWN
            choice++;
            if (choice >= menuSize) choice = 0;
            break;
        case 13: // ENTER
            system("cls");
            switch (choice) {
            case 0: {
                Employee e;
                cout << "Enter name: "; getline(cin, e.name);
                cout << "Enter position: "; getline(cin, e.position);
                cout << "Enter phone: "; getline(cin, e.phone);
                cout << "Enter email: "; getline(cin, e.email);
                dealer.addEmployee(e);
                break;
            }
            case 1: {
                int id;
                cout << "Enter employee ID to remove: "; cin >> id;
                dealer.removeEmployee(id);
                cin.ignore();
                break;
            }
            case 2: dealer.showEmployees(); break;
            case 3: {
                Car c;
                cout << "Enter manufacturer: "; getline(cin, c.manufacturer);
                cout << "Enter year: "; cin >> c.year; cin.ignore();
                cout << "Enter model: "; getline(cin, c.model);
                cout << "Enter cost price: "; cin >> c.costPrice;
                cout << "Enter potential price: "; cin >> c.potentialPrice; cin.ignore();
                dealer.addCar(c);
                break;
            }
            case 4: {
                int id;
                cout << "Enter car ID to remove: "; cin >> id;
                dealer.removeCar(id);
                cin.ignore();
                break;
            }
            case 5: dealer.showCars(); break;
            case 6: {
                Sale s;
                cout << "Enter employee ID: "; cin >> s.employeeId;
                cout << "Enter car ID: "; cin >> s.carId; cin.ignore();
                cout << "Enter date (YYYY-MM-DD): "; getline(cin, s.date);
                cout << "Enter real price: "; cin >> s.realPrice; cin.ignore();
                dealer.addSale(s);
                break;
            }
            case 7: {
                int id;
                cout << "Enter sale ID to remove: "; cin >> id;
                dealer.removeSale(id);
                cin.ignore();
                break;
            }
            case 8: dealer.showSales(); break;

            case 9: {
                cout << "===== ALL INFORMATION =====\n\n";
                dealer.showEmployees();
                cout << "\n----------------------------\n";
                dealer.showCars();
                cout << "\n----------------------------\n";
                dealer.showSales();
                break;
            }
            case 10: {
                dealer.saveToFile(currentFile);
                cout << "Saved to current file: " << currentFile << endl;
                break;
            }
            case 11: {
                string file;
                cout << "Enter new filename: ";
                getline(cin, file);
                dealer.saveToFile(file);
                currentFile = file;
                cout << "Saved to new file: " << file << endl;
                break;
            }
            case 12: {
                string file;
                cout << "Enter filename: ";
                getline(cin, file);
                dealer.loadFromFile(file);
                currentFile = file;
                break;
            }
            case 13:
                running = false;
                break;
            }

            if (running) {
                cout << "\nPress any key to return to menu...";
                _getch();
            }
            break;
        }
    }

    ShowConsoleCursor(true);
    cout << "\nExiting...\n";
    return 0;
}
