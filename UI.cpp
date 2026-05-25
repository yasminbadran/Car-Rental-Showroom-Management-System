#include "UI.h"

#include <iostream>
#include <limits>

using namespace std;

int UI::mainMenu() const {
    cout << "\n=== Vehicle Showroom, Rental, and Test Drive Management System ===\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "0. Exit\n";
    return getInt("Choice: ");
}

int UI::customerMenu() const {
    cout << "\nCustomer Menu\n";
    cout << "1. View available cars\n";
    cout << "2. Search cars\n";
    cout << "3. Book test drive\n";
    cout << "4. Rent a car\n";
    cout << "5. Buy a car\n";
    cout << "6. View my profile\n";
    cout << "0. Logout\n";
    return getInt("Choice: ");
}

int UI::adminMenu() const {
    cout << "\nAdmin Menu\n";
    cout << "1. View all cars\n";
    cout << "2. Add car\n";
    cout << "3. Update car\n";
    cout << "4. Delete car\n";
    cout << "5. View test drive bookings\n";
    cout << "6. View rental orders\n";
    cout << "7. View purchase orders\n";
    cout << "8. Confirm booking\n";
    cout << "9. Confirm rental\n";
    cout << "10. Confirm purchase\n";
    cout << "11. Cancel booking\n";
    cout << "12. Cancel rental\n";
    cout << "13. Cancel purchase\n";
    cout << "14. Save data\n";
    cout << "0. Logout\n";
    return getInt("Choice: ");
}

int UI::searchMenu() const {
    cout << "\nSearch Menu\n";
    cout << "1. Search by brand\n";
    cout << "2. Search by model\n";
    cout << "3. Search by type\n";
    cout << "4. Search by maximum price\n";
    cout << "0. Back\n";
    return getInt("Choice: ");
}

void UI::loginMenu(string& username, string& password) const {
    username = getLine("Username: ");
    password = getLine("Password: ");
}

void UI::registerMenu(string& name, string& phone, string& email,
                      string& address, string& username,
                      string& password, string& role) const {
    name = getLine("Enter full name: ");
    phone = getLine("Enter phone: ");
    email = getLine("Enter email: ");
    address = getLine("Enter address: ");
    username = getLine("Choose username: ");
    password = getLine("Choose password: ");
    role = getLine("Account type (admin/customer): ");
}

void UI::showMessage(const string& message) const {
    cout << message << '\n';
}

void UI::pause() const {
    cout << "\nPress Enter to continue...";
    cin.get();
}

string UI::getLine(const string& prompt) const {
    cout << prompt;
    string value;
    getline(cin, value);
    return value;
}

int UI::getInt(const string& prompt) const {
    cout << prompt;
    int value = 0;
    cin >> value;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

double UI::getDouble(const string& prompt) const {
    cout << prompt;
    double value = 0.0;
    cin >> value;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

bool UI::getYesNo(const string& prompt) const {
    return getInt(prompt) == 1;
}

void UI::showCars(const vector<Car>& cars) const {
    if (cars.empty()) {
        showMessage("No cars to display.");
        return;
    }

    for (const Car& car : cars) {
        cout << car.toDisplayString() << '\n';
    }
}

void UI::showCustomers(const vector<Customer>& customers) const {
    if (customers.empty()) {
        showMessage("No customers to display.");
        return;
    }

    for (const Customer& customer : customers) {
        cout << customer.toDisplayString() << '\n';
    }
}

void UI::showBookings(const vector<TestDriveBooking>& bookings) const {
    if (bookings.empty()) {
        showMessage("No test drive bookings found.");
        return;
    }

    for (const TestDriveBooking& booking : bookings) {
        cout << booking.toDisplayString() << '\n';
    }
}

void UI::showRentals(const vector<RentalOrder>& rentals) const {
    if (rentals.empty()) {
        showMessage("No rental orders found.");
        return;
    }

    for (const RentalOrder& rental : rentals) {
        cout << rental.toDisplayString() << '\n';
    }
}

void UI::showPurchases(const vector<PurchaseOrder>& purchases) const {
    if (purchases.empty()) {
        showMessage("No purchase orders found.");
        return;
    }

    for (const PurchaseOrder& purchase : purchases) {
        cout << purchase.toDisplayString() << '\n';
    }
}

Car UI::getNewCarData(int carID) const {
    string brand = getLine("Brand: ");
    string model = getLine("Model: ");
    int year = getInt("Year: ");
    string type = getLine("Type: ");
    double salePrice = getDouble("Sale price: ");
    double dailyRentalPrice = getDouble("Daily rental price: ");
    bool forSale = getYesNo("Available for sale? (1/0): ");
    bool forRent = getYesNo("Available for rent? (1/0): ");

    return Car(carID, brand, model, year, type, salePrice, dailyRentalPrice, forSale, forRent, true);
}

void UI::getCarUpdateData(double& salePrice, double& dailyRentalPrice,
                          bool& forSale, bool& forRent, bool& available) const {
    salePrice = getDouble("Enter new sale price: ");
    dailyRentalPrice = getDouble("Enter new daily rental price: ");
    forSale = getYesNo("Available for sale? (1/0): ");
    forRent = getYesNo("Available for rent? (1/0): ");
    available = getYesNo("Currently available? (1/0): ");
}
