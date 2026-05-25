#include "ApplicationManager.h"

#include "FileManager.h"

#include <algorithm>
#include <cctype>

using namespace std;

namespace {
const string ADMIN_ACCESS_CODE = "yasminbadran";
const int MAX_ADMIN_CODE_ATTEMPTS = 3;

string trim(const string& value) {
    const string spaces = " \t\r\n";
    const size_t start = value.find_first_not_of(spaces);
    if (start == string::npos) {
        return "";
    }
    const size_t end = value.find_last_not_of(spaces);
    return value.substr(start, end - start + 1);
}

string toLowerCase(string value) {
    for (char& ch : value) {
        ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    }
    return value;
}

vector<string> split(const string& line, char delimiter) {
    vector<string> parts;
    string current;
    for (char ch : line) {
        if (ch == delimiter) {
            parts.push_back(current);
            current.clear();
        } else {
            current += ch;
        }
    }
    parts.push_back(current);
    return parts;
}
}

ApplicationManager::ApplicationManager()
    : carsFile("cars.txt"),
      customersFile("customers.txt"),
      bookingsFile("bookings.txt"),
      rentalsFile("rentals.txt"),
      purchasesFile("purchases.txt"),
      usersFile("users.txt"),
      nextCarID(1),
      nextCustomerID(1),
      nextBookingID(1),
      nextRentalID(1),
      nextPurchaseID(1) {
    loadSystemData();
    seedCarsIfEmpty();
}

void ApplicationManager::run() {
    int choice = -1;

    while (choice != 0) {
        choice = ui.mainMenu();

        if (choice == 1) {
            string username;
            string role;
            if (registerUser(username, role)) {
                if (role == "admin") {
                    adminSession();
                } else {
                    customerSession(username);
                }
            }
        } else if (choice == 2) {
            string username;
            string role;
            if (loginUser(username, role)) {
                if (role == "admin") {
                    if (verifyAdminCode()) {
                        adminSession();
                    }
                } else {
                    customerSession(username);
                }
            } else {
                ui.showMessage("Invalid username or password.");
            }
        } else if (choice == 0) {
            saveSystemData();
            ui.showMessage("Data saved. Goodbye!");
        } else {
            ui.showMessage("Invalid choice.");
        }
    }
}

void ApplicationManager::seedCarsIfEmpty() {
    if (!cars.empty()) {
        return;
    }

    cars.push_back(Car(nextCarID++, "Mercedes", "C180", 2023, "Sedan", 2300000, 4500, true, true, true));
    cars.push_back(Car(nextCarID++, "BMW", "X3", 2024, "SUV", 3100000, 6000, true, true, true));
    cars.push_back(Car(nextCarID++, "Hyundai", "Elantra", 2022, "Sedan", 1450000, 2500, true, true, true));
    saveSystemData();
}

void ApplicationManager::loadSystemData() {
    cars = FileManager::loadCars(carsFile);
    customers = FileManager::loadCustomers(customersFile);
    bookings = FileManager::loadBookings(bookingsFile);
    rentals = FileManager::loadRentals(rentalsFile);
    purchases = FileManager::loadPurchases(purchasesFile);

    for (const Car& car : cars) {
        nextCarID = max(nextCarID, car.getCarID() + 1);
    }
    for (const Customer& customer : customers) {
        nextCustomerID = max(nextCustomerID, customer.getCustomerID() + 1);
    }
    for (const TestDriveBooking& booking : bookings) {
        nextBookingID = max(nextBookingID, booking.getBookingID() + 1);
    }
    for (const RentalOrder& rental : rentals) {
        nextRentalID = max(nextRentalID, rental.getRentalID() + 1);
    }
    for (const PurchaseOrder& purchase : purchases) {
        nextPurchaseID = max(nextPurchaseID, purchase.getPurchaseID() + 1);
    }
}

void ApplicationManager::saveSystemData() const {
    FileManager::saveCars(carsFile, cars);
    FileManager::saveCustomers(customersFile, customers);
    FileManager::saveBookings(bookingsFile, bookings);
    FileManager::saveRentals(rentalsFile, rentals);
    FileManager::savePurchases(purchasesFile, purchases);
}

bool ApplicationManager::registerUser(string& username, string& role) {
    string name;
    string phone;
    string email;
    string address;
    string password;

    ui.registerMenu(name, phone, email, address, username, password, role);
    role = toLowerCase(trim(role));

    if (role != "admin" && role != "customer") {
        role = "customer";
    }

    vector<string> users = FileManager::loadLines(usersFile);
    for (const string& userLine : users) {
        vector<string> parts = split(userLine, '|');
        if (!parts.empty() && parts[0] == username) {
            ui.showMessage("Username already exists.");
            return false;
        }
    }

    int customerID = nextCustomerID++;
    if (role == "admin") {
        if (!verifyAdminCode()) {
            role = "customer";
            ui.showMessage("Registered as customer instead.");
        }
    }

    users.push_back(username + "|" + password + "|" + role + "|" + to_string(customerID));
    FileManager::saveLines(usersFile, users);
    customers.push_back(Customer(customerID, name, phone, email, address));
    saveSystemData();
    ui.showMessage("Registration completed successfully.");
    return true;
}

bool ApplicationManager::loginUser(string& username, string& role) const {
    string password;
    ui.loginMenu(username, password);

    vector<string> users = FileManager::loadLines(usersFile);
    for (const string& userLine : users) {
        vector<string> parts = split(userLine, '|');
        if (parts.size() >= 4 && parts[0] == username && parts[1] == password) {
            role = parts[2];
            return true;
        }
    }
    return false;
}

bool ApplicationManager::verifyAdminCode() const {
    ui.showMessage("\n--- Admin Verification ---");

    for (int attempt = 1; attempt <= MAX_ADMIN_CODE_ATTEMPTS; ++attempt) {
        string code = ui.getLine("Admin code: ");
        if (trim(code) == ADMIN_ACCESS_CODE) {
            ui.showMessage("Admin verified successfully.");
            return true;
        }

        const int attemptsLeft = MAX_ADMIN_CODE_ATTEMPTS - attempt;
        if (attemptsLeft > 0) {
            ui.showMessage("Incorrect code. Attempts left: " + to_string(attemptsLeft));
        }
    }

    ui.showMessage("Admin access denied. You will continue as a customer.");
    return false;
}

void ApplicationManager::adminSession() {
    int choice = -1;

    while (choice != 0) {
        choice = ui.adminMenu();

        switch (choice) {
        case 1:
            viewAllCars();
            ui.pause();
            break;
        case 2:
            addCar();
            ui.pause();
            break;
        case 3:
            updateCar();
            ui.pause();
            break;
        case 4:
            deleteCar();
            ui.pause();
            break;
        case 5:
            viewBookings();
            ui.pause();
            break;
        case 6:
            viewRentals();
            ui.pause();
            break;
        case 7:
            viewPurchaseOrders();
            ui.pause();
            break;
        case 8:
            confirmBooking();
            ui.pause();
            break;
        case 9:
            confirmRental();
            ui.pause();
            break;
        case 10:
            confirmPurchase();
            ui.pause();
            break;
        case 11:
            cancelBooking();
            ui.pause();
            break;
        case 12:
            cancelRental();
            ui.pause();
            break;
        case 13:
            cancelPurchase();
            ui.pause();
            break;
        case 14:
            saveSystemData();
            ui.showMessage("Data saved successfully.");
            ui.pause();
            break;
        case 0:
            break;
        default:
            ui.showMessage("Invalid choice.");
            ui.pause();
        }
    }
}

void ApplicationManager::customerSession(const string& username) {
    int choice = -1;

    while (choice != 0) {
        choice = ui.customerMenu();

        switch (choice) {
        case 1:
            viewAvailableCars();
            ui.pause();
            break;
        case 2:
            searchCars();
            ui.pause();
            break;
        case 3:
            bookTestDrive(username);
            ui.pause();
            break;
        case 4:
            rentCar(username);
            ui.pause();
            break;
        case 5:
            buyCar(username);
            ui.pause();
            break;
        case 6:
            viewCustomerProfile(username);
            ui.pause();
            break;
        case 0:
            break;
        default:
            ui.showMessage("Invalid choice.");
            ui.pause();
        }
    }
}

void ApplicationManager::viewAllCars() const {
    ui.showCars(cars);
}

void ApplicationManager::viewAvailableCars() const {
    vector<Car> availableCars;
    for (const Car& car : cars) {
        if (car.isAvailable()) {
            availableCars.push_back(car);
        }
    }
    ui.showCars(availableCars);
}

void ApplicationManager::addCar() {
    cars.push_back(ui.getNewCarData(nextCarID++));
    saveSystemData();
    ui.showMessage("Car added successfully.");
}

void ApplicationManager::updateCar() {
    if (cars.empty()) {
        ui.showMessage("No cars to update.");
        return;
    }

    ui.showMessage("Cars available to update:");
    ui.showCars(cars);
    int carID = ui.getInt("Enter car ID to update: ");
    Car* car = findCarByID(carID);

    if (car == nullptr) {
        ui.showMessage("Car not found.");
        return;
    }

    double salePrice = 0.0;
    double dailyRentalPrice = 0.0;
    bool forSale = false;
    bool forRent = false;
    bool available = false;
    ui.getCarUpdateData(salePrice, dailyRentalPrice, forSale, forRent, available);
    car->updateCar(salePrice, dailyRentalPrice, forSale, forRent, available);
    saveSystemData();
    ui.showMessage("Car updated successfully.");
}

void ApplicationManager::deleteCar() {
    if (cars.empty()) {
        ui.showMessage("No cars to delete.");
        return;
    }

    ui.showMessage("Cars available to delete:");
    ui.showCars(cars);
    int carID = ui.getInt("Enter car ID to delete: ");

    for (size_t i = 0; i < cars.size(); ++i) {
        if (cars[i].getCarID() == carID) {
            cars.erase(cars.begin() + static_cast<ptrdiff_t>(i));
            saveSystemData();
            ui.showMessage("Car deleted successfully.");
            return;
        }
    }

    ui.showMessage("Car not found.");
}

void ApplicationManager::viewBookings() const {
    ui.showBookings(bookings);
}

void ApplicationManager::viewRentals() const {
    ui.showRentals(rentals);
}

void ApplicationManager::viewPurchaseOrders() const {
    ui.showPurchases(purchases);
}

void ApplicationManager::searchCars() const {
    int choice = ui.searchMenu();

    switch (choice) {
    case 1:
        searchByBrand();
        break;
    case 2:
        searchByModel();
        break;
    case 3:
        searchByType();
        break;
    case 4:
        searchByPrice();
        break;
    default:
        break;
    }
}

void ApplicationManager::searchByBrand() const {
    string brand = toLowerCase(trim(ui.getLine("Enter brand to search: ")));
    vector<Car> results;

    for (const Car& car : cars) {
        if (toLowerCase(trim(car.getBrand())).find(brand) != string::npos) {
            results.push_back(car);
        }
    }

    ui.showCars(results);
}

void ApplicationManager::searchByModel() const {
    string model = toLowerCase(trim(ui.getLine("Enter model to search: ")));
    vector<Car> results;

    for (const Car& car : cars) {
        if (toLowerCase(trim(car.getModel())).find(model) != string::npos) {
            results.push_back(car);
        }
    }

    ui.showCars(results);
}

void ApplicationManager::searchByType() const {
    string type = toLowerCase(trim(ui.getLine("Enter type to search: ")));
    vector<Car> results;

    for (const Car& car : cars) {  
        if (toLowerCase(trim(car.getType())).find(type) != string::npos) {
            results.push_back(car);
        }
    }

    ui.showCars(results);
}

void ApplicationManager::searchByPrice() const {
    double maxPrice = ui.getDouble("Enter maximum sale price: ");
    vector<Car> results;

    for (const Car& car : cars) {
        if (car.getSalePrice() <= maxPrice) {
            results.push_back(car);
        }
    }

    ui.showCars(results);
}

void ApplicationManager::bookTestDrive(const string& username) {
    int customerID = getCustomerIDByUsername(username);
    if (customerID == -1) {
        ui.showMessage("Customer profile not found.");
        return;
    }

    viewAvailableCars();
    int carID = ui.getInt("Enter car ID for test drive: ");
    string date = ui.getLine("Enter date (DD/MM/YYYY): ");
    string time = ui.getLine("Enter time: ");

    Car* car = findCarByID(carID);
    if (car == nullptr || !car->isAvailable()) {
        ui.showMessage("Car is not available.");
        return;
    }

    bookings.push_back(TestDriveBooking(nextBookingID++, carID, customerID, date, time, "Pending"));
    saveSystemData();
    ui.showMessage("Test drive booked successfully.");
}

void ApplicationManager::rentCar(const string& username) {
    int customerID = getCustomerIDByUsername(username);
    if (customerID == -1) {
        ui.showMessage("Customer profile not found.");
        return;
    }

    viewAvailableCars();
    int carID = ui.getInt("Enter car ID to rent: ");
    int numberOfDays = ui.getInt("Enter number of rental days: ");
    bool delivery = ui.getYesNo("Need home delivery? (1/0): ");

    Car* car = findCarByID(carID);
    if (car == nullptr || !car->isAvailable() || !car->isRentable()) {
        ui.showMessage("Selected car is not available for rent.");
        return;
    }

    string address = "No delivery";
    double deliveryFee = 0.0;
    if (delivery) {
        address = ui.getLine("Enter delivery address: ");
        deliveryFee = 250.0;
    }

    RentalOrder rental(nextRentalID++, carID, customerID, numberOfDays, delivery, address, deliveryFee, 0.0, "Pending");
    const double totalCost = rental.calculateRentalCost(car->getDailyRentalPrice());
    rental = RentalOrder(rental.getRentalID(), carID, customerID, numberOfDays, delivery, address, deliveryFee, totalCost, "Pending");

    rentals.push_back(rental);
    car->setAvailable(false);
    saveSystemData();
    ui.showMessage("Rental order created successfully.");
    ui.showMessage("Total rental cost: " + to_string(totalCost));
}

void ApplicationManager::buyCar(const string& username) {
    int customerID = getCustomerIDByUsername(username);
    if (customerID == -1) {
        ui.showMessage("Customer profile not found.");
        return;
    }

    viewAvailableCars();
    int carID = ui.getInt("Enter car ID to buy: ");
    Car* car = findCarByID(carID);
    if (car == nullptr || !car->isAvailable() || !car->isForSale()) {
        ui.showMessage("Selected car is not available for purchase.");
        return;
    }

    string paymentMethod = ui.getLine("Enter payment method: ");
    purchases.push_back(PurchaseOrder(nextPurchaseID++, carID, customerID, paymentMethod, "Pending"));
    car->setAvailable(false);
    saveSystemData();
    ui.showMessage("Purchase order created successfully.");
}

void ApplicationManager::viewCustomerProfile(const string& username) const {
    const Customer* customer = findCustomerByUsername(username);
    if (customer == nullptr) {
        ui.showMessage("Customer profile not found.");
        return;
    }

    ui.showMessage(customer->toDisplayString());
}

void ApplicationManager::confirmBooking() {
    vector<TestDriveBooking> pendingBookings;
    for (const TestDriveBooking& booking : bookings) {
        if (booking.getStatus() == "Pending") {
            pendingBookings.push_back(booking);
        }
    }

    if (pendingBookings.empty()) {
        ui.showMessage("No pending test drive bookings to confirm.");
        return;
    }

    ui.showMessage("Pending bookings:");
    ui.showBookings(pendingBookings);
    int bookingID = ui.getInt("Enter booking ID to confirm: ");
    for (TestDriveBooking& booking : bookings) {
        if (booking.getBookingID() == bookingID) {
            if (booking.getStatus() != "Pending") {
                ui.showMessage("This booking is already " + booking.getStatus() + ".");
                return;
            }
            booking.confirmBooking();
            saveSystemData();
            ui.showMessage("Booking confirmed.");
            return;
        }
    }
    ui.showMessage("Booking not found.");
}

void ApplicationManager::confirmRental() {
    vector<RentalOrder> pendingRentals;
    for (const RentalOrder& rental : rentals) {
        if (rental.getStatus() == "Pending") {
            pendingRentals.push_back(rental);
        }
    }

    if (pendingRentals.empty()) {
        ui.showMessage("No pending rental orders to confirm.");
        return;
    }

    ui.showMessage("Pending rental orders:");
    ui.showRentals(pendingRentals);
    int rentalID = ui.getInt("Enter rental ID to confirm: ");
    for (RentalOrder& rental : rentals) {
        if (rental.getRentalID() == rentalID) {
            if (rental.getStatus() != "Pending") {
                ui.showMessage("This rental order is already " + rental.getStatus() + ".");
                return;
            }
            rental.confirmRental();
            saveSystemData();
            ui.showMessage("Rental confirmed.");
            return;
        }
    }
    ui.showMessage("Rental order not found.");
}

void ApplicationManager::confirmPurchase() {
    vector<PurchaseOrder> pendingPurchases;
    for (const PurchaseOrder& purchase : purchases) {
        if (purchase.getStatus() == "Pending") {
            pendingPurchases.push_back(purchase);
        }
    }

    if (pendingPurchases.empty()) {
        ui.showMessage("No pending purchase orders to confirm.");
        return;
    }

    ui.showMessage("Pending purchase orders:");
    ui.showPurchases(pendingPurchases);
    int purchaseID = ui.getInt("Enter purchase ID to confirm: ");
    for (PurchaseOrder& purchase : purchases) {
        if (purchase.getPurchaseID() == purchaseID) {
            if (purchase.getStatus() != "Pending") {
                ui.showMessage("This purchase order is already " + purchase.getStatus() + ".");
                return;
            }
            purchase.confirmPurchase();
            saveSystemData();
            ui.showMessage("Purchase confirmed.");
            return;
        }
    }
    ui.showMessage("Purchase order not found.");
}

void ApplicationManager::cancelBooking() {
    vector<TestDriveBooking> cancellableBookings;
    for (const TestDriveBooking& booking : bookings) {
        if (booking.getStatus() != "Cancelled") {
            cancellableBookings.push_back(booking);
        }
    }

    if (cancellableBookings.empty()) {
        ui.showMessage("No test drive bookings to cancel.");
        return;
    }

    ui.showMessage("Bookings available to cancel:");
    ui.showBookings(cancellableBookings);
    int bookingID = ui.getInt("Enter booking ID to cancel: ");
    for (TestDriveBooking& booking : bookings) {
        if (booking.getBookingID() == bookingID) {
            if (booking.getStatus() == "Cancelled") {
                ui.showMessage("This booking is already cancelled.");
                return;
            }
            booking.cancelBooking();
            saveSystemData();
            ui.showMessage("Booking cancelled.");
            return;
        }
    }
    ui.showMessage("Booking not found.");
}

void ApplicationManager::cancelRental() {
    vector<RentalOrder> cancellableRentals;
    for (const RentalOrder& rental : rentals) {
        if (rental.getStatus() != "Cancelled") {
            cancellableRentals.push_back(rental);
        }
    }

    if (cancellableRentals.empty()) {
        ui.showMessage("No rental orders to cancel.");
        return;
    }

    ui.showMessage("Rental orders available to cancel:");
    ui.showRentals(cancellableRentals);
    int rentalID = ui.getInt("Enter rental ID to cancel: ");
    for (RentalOrder& rental : rentals) {
        if (rental.getRentalID() == rentalID) {
            if (rental.getStatus() == "Cancelled") {
                ui.showMessage("This rental order is already cancelled.");
                return;
            }
            rental.cancelRental();
            Car* car = findCarByID(rental.getCarID());
            if (car != nullptr) {
                car->setAvailable(true);
            }
            saveSystemData();
            ui.showMessage("Rental cancelled.");
            return;
        }
    }
    ui.showMessage("Rental order not found.");
}

void ApplicationManager::cancelPurchase() {
    vector<PurchaseOrder> cancellablePurchases;
    for (const PurchaseOrder& purchase : purchases) {
        if (purchase.getStatus() != "Cancelled") {
            cancellablePurchases.push_back(purchase);
        }
    }

    if (cancellablePurchases.empty()) {
        ui.showMessage("No purchase orders to cancel.");
        return;
    }

    ui.showMessage("Purchase orders available to cancel:");
    ui.showPurchases(cancellablePurchases);
    int purchaseID = ui.getInt("Enter purchase ID to cancel: "); // show message + take integer input from user.
    for (PurchaseOrder& purchase : purchases) {
        if (purchase.getPurchaseID() == purchaseID) {
            if (purchase.getStatus() == "Cancelled") {
                ui.showMessage("This purchase order is already cancelled.");
                return;
            }
            purchase.cancelPurchase();
            Car* car = findCarByID(purchase.getCarID());
            if (car != nullptr) { // lw car mwgodh hn3ml ely gwa el   if
                car->setAvailable(true);
            }
            saveSystemData();
            ui.showMessage("Purchase cancelled.");
            return;
        }
    }
    ui.showMessage("Purchase order not found.");
}

Car* ApplicationManager::findCarByID(int carID) {
    for (Car& car : cars) {
        if (car.getCarID() == carID) {
            return &car;
        }
    }
    return nullptr;
}

const Customer* ApplicationManager::findCustomerByUsername(const string& username) const {
    int customerID = getCustomerIDByUsername(username);
    if (customerID == -1) {
        return nullptr;
    }

    for (const Customer& customer : customers) {
        if (customer.getCustomerID() == customerID) {
            return &customer;   //&customer means pointer to the original customer, not a copy
        }
    }

    return nullptr; // mafesh pointer find
}

int ApplicationManager::getCustomerIDByUsername(const string& username) const {
    vector<string> users = FileManager::loadLines(usersFile);
    for (const string& userLine : users) {
        vector<string> parts = split(userLine, '|');
        if (parts.size() >= 4 && parts[0] == username) {
            return stoi(parts[3]);
        }
    }
    return -1;
}
