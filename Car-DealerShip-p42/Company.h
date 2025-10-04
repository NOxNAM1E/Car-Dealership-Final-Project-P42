#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define MAX_EMPLOYEES 100
#define MAX_CARS 100
#define MAX_SALES 100

struct Employee {
    string name;
    string position;
    string phone;
    string email;
};

struct Car {
    string manufacturer;
    int year;
    string model;
    double costPrice;
    double potentialPrice;
};

struct Sale {
    int employeeId;
    int carId;
    string date;
    double realPrice;
};

class CarDealership {
    Employee employees[MAX_EMPLOYEES];
    Car cars[MAX_CARS];
    Sale sales[MAX_SALES];
    int employeeCount = 0;
    int carCount = 0;
    int saleCount = 0;
    string currentFile = "";

public:
    // ---------------- EMPLOYEES ----------------
    void addEmployee(const Employee& e) {
        if (employeeCount < MAX_EMPLOYEES)
            employees[employeeCount++] = e;
        else
            cout << "Employee list full!\n";
    }

    void removeEmployee(int id) {
        if (id >= 0 && id < employeeCount) {
            for (int i = id; i < employeeCount - 1; i++)
                employees[i] = employees[i + 1];
            employeeCount--;
        }
    }

    void showEmployees() {
        if (employeeCount == 0) {
            cout << "No employees.\n";
            return;
        }
        cout << "\n===== EMPLOYEES =====\n";
        for (int i = 0; i < employeeCount; i++) {
            cout << i << ". " << employees[i].name << " | " << employees[i].position
                << " | " << employees[i].phone << " | " << employees[i].email << endl;
        }
    }

    // ---------------- CARS ----------------
    void addCar(const Car& c) {
        if (carCount < MAX_CARS)
            cars[carCount++] = c;
        else
            cout << "Car list full!\n";
    }

    void removeCar(int id) {
        if (id >= 0 && id < carCount) {
            for (int i = id; i < carCount - 1; i++)
                cars[i] = cars[i + 1];
            carCount--;
        }
    }

    void showCars() {
        if (carCount == 0) {
            cout << "No cars.\n";
            return;
        }
        cout << "\n===== CARS =====\n";
        for (int i = 0; i < carCount; i++) {
            cout << i << ". " << cars[i].manufacturer << " " << cars[i].model
                << " (" << cars[i].year << ") "
                << "Cost: " << cars[i].costPrice
                << " | Potential: " << cars[i].potentialPrice << endl;
        }
    }

    // ---------------- SALES ----------------
    void addSale(const Sale& s) {
        if (saleCount < MAX_SALES)
            sales[saleCount++] = s;
        else
            cout << "Sales list full!\n";
    }

    void removeSale(int id) {
        if (id >= 0 && id < saleCount) {
            for (int i = id; i < saleCount - 1; i++)
                sales[i] = sales[i + 1];
            saleCount--;
        }
    }

    void showSales() {
        if (saleCount == 0) {
            cout << "No sales.\n";
            return;
        }
        cout << "\n===== SALES =====\n";
        for (int i = 0; i < saleCount; i++) {
            cout << i << ". Seller: " << employees[sales[i].employeeId].name
                << " | Car: " << cars[sales[i].carId].manufacturer
                << " " << cars[sales[i].carId].model
                << " | Date: " << sales[i].date
                << " | Price: " << sales[i].realPrice << endl;
        }
    }

    // ---------------- SHOW ALL ----------------
    void showAll() {
        cout << "\n========== FULL DEALERSHIP INFO ==========\n";
        showEmployees();
        showCars();
        showSales();
        cout << "==========================================\n";
    }

    // ---------------- SAVE / LOAD ----------------
    void saveToFile(const string& filename) {
        ofstream out(filename);
        if (!out) {
            cout << "Error saving file!\n";
            return;
        }

        out << employeeCount << endl;
        for (int i = 0; i < employeeCount; i++)
            out << employees[i].name << ";" << employees[i].position << ";" << employees[i].phone << ";" << employees[i].email << endl;

        out << carCount << endl;
        for (int i = 0; i < carCount; i++)
            out << cars[i].manufacturer << ";" << cars[i].year << ";" << cars[i].model << ";" << cars[i].costPrice << ";" << cars[i].potentialPrice << endl;

        out << saleCount << endl;
        for (int i = 0; i < saleCount; i++)
            out << sales[i].employeeId << ";" << sales[i].carId << ";" << sales[i].date << ";" << sales[i].realPrice << endl;

        currentFile = filename;
        cout << "Data saved to " << filename << endl;
    }

    void loadFromFile(const string& filename) {
        ifstream in(filename);
        if (!in) {
            cout << "Error loading file!\n";
            return;
        }

        employeeCount = carCount = saleCount = 0;
        int n;
        string temp;

        in >> n; in.ignore();
        for (int i = 0; i < n; i++) {
            Employee e;
            getline(in, e.name, ';');
            getline(in, e.position, ';');
            getline(in, e.phone, ';');
            getline(in, e.email);
            employees[employeeCount++] = e;
        }

        in >> n; in.ignore();
        for (int i = 0; i < n; i++) {
            Car c;
            string yearStr, costStr, priceStr;
            getline(in, c.manufacturer, ';');
            getline(in, yearStr, ';');
            c.year = stoi(yearStr);
            getline(in, c.model, ';');
            getline(in, costStr, ';');
            getline(in, priceStr);
            c.costPrice = stod(costStr);
            c.potentialPrice = stod(priceStr);
            cars[carCount++] = c;
        }

        in >> n; in.ignore();
        for (int i = 0; i < n; i++) {
            Sale s;
            string empId, carId, price;
            getline(in, empId, ';');
            getline(in, carId, ';');
            getline(in, s.date, ';');
            getline(in, price);
            s.employeeId = stoi(empId);
            s.carId = stoi(carId);
            s.realPrice = stod(price);
            sales[saleCount++] = s;
        }

        currentFile = filename;
        cout << "Data loaded from " << filename << endl;
    }

    // ---------------- SAVE TO CURRENT FILE ----------------
    void saveToCurrentFile() {
        if (currentFile.empty()) {
            cout << "No file currently loaded. Use option 10 or 11 first.\n";
            return;
        }
        saveToFile(currentFile);
    }
};
