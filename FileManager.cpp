#include "FileManager.h"

#include <fstream>

using namespace std;

vector<Car> FileManager::loadCars(const string& fileName) {
    vector<Car> cars;
    ifstream file(fileName);
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            cars.push_back(Car::fromFileString(line));
        }
    }
    return cars;
}

void FileManager::saveCars(const string& fileName, const vector<Car>& cars) {
    ofstream file(fileName);
    for (const Car& car : cars) {
        file << car.toFileString() << '\n';
    }
}

vector<Customer> FileManager::loadCustomers(const string& fileName) {
    vector<Customer> customers;
    ifstream file(fileName);
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            customers.push_back(Customer::fromFileString(line));
        }
    }
    return customers;
}

void FileManager::saveCustomers(const string& fileName, const vector<Customer>& customers) {
    ofstream file(fileName);
    for (const Customer& customer : customers) {
        file << customer.toFileString() << '\n';
    }
}

vector<TestDriveBooking> FileManager::loadBookings(const string& fileName) {
    vector<TestDriveBooking> bookings;
    ifstream file(fileName);
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            bookings.push_back(TestDriveBooking::fromFileString(line));
        }
    }
    return bookings;
}

void FileManager::saveBookings(const string& fileName, const vector<TestDriveBooking>& bookings) {
    ofstream file(fileName);
    for (const TestDriveBooking& booking : bookings) {
        file << booking.toFileString() << '\n';
    }
}

vector<RentalOrder> FileManager::loadRentals(const string& fileName) {
    vector<RentalOrder> rentals;
    ifstream file(fileName);
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            rentals.push_back(RentalOrder::fromFileString(line));
        }
    }
    return rentals;
}

void FileManager::saveRentals(const string& fileName, const vector<RentalOrder>& rentals) {
    ofstream file(fileName);
    for (const RentalOrder& rental : rentals) {
        file << rental.toFileString() << '\n';
    }
}

vector<PurchaseOrder> FileManager::loadPurchases(const string& fileName) {
    vector<PurchaseOrder> purchases;
    ifstream file(fileName);
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            purchases.push_back(PurchaseOrder::fromFileString(line));
        }
    }
    return purchases;
}

void FileManager::savePurchases(const string& fileName, const vector<PurchaseOrder>& purchases) {
    ofstream file(fileName);
    for (const PurchaseOrder& purchase : purchases) {
        file << purchase.toFileString() << '\n';
    }
}

vector<string> FileManager::loadLines(const string& fileName) {
    vector<string> lines;
    ifstream file(fileName);
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    return lines;
}

void FileManager::saveLines(const string& fileName, const vector<string>& lines) {
    ofstream file(fileName);
    for (const string& line : lines) {
        file << line << '\n';
    }
}
