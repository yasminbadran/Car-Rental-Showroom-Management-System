#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include "Car.h"
#include "Customer.h"
#include "PurchaseOrder.h"
#include "RentalOrder.h"
#include "TestDriveBooking.h"
#include "UI.h"

#include <string>
#include <vector>

using namespace std;

class ApplicationManager {
private:
    UI ui;
    vector<Car> cars;
    vector<Customer> customers;
    vector<TestDriveBooking> bookings;
    vector<RentalOrder> rentals;
    vector<PurchaseOrder> purchases;

    const string carsFile;
    const string customersFile;
    const string bookingsFile;
    const string rentalsFile;
    const string purchasesFile;
    const string usersFile;

    int nextCarID;
    int nextCustomerID;
    int nextBookingID;
    int nextRentalID;
    int nextPurchaseID;

    void seedCarsIfEmpty();
    void loadSystemData();
    void saveSystemData() const;

    bool registerUser(string& username, string& role);
    bool loginUser(string& username, string& role) const;
    bool verifyAdminCode() const;

    void adminSession();
    void customerSession(const string& username);

    void viewAllCars() const;
    void viewAvailableCars() const;
    void addCar();
    void updateCar();
    void deleteCar();
    void viewBookings() const;
    void viewRentals() const;
    void viewPurchaseOrders() const;

    void searchCars() const;
    void searchByBrand() const;
    void searchByModel() const;
    void searchByType() const;
    void searchByPrice() const;

    void bookTestDrive(const string& username);
    void rentCar(const string& username);
    void buyCar(const string& username);
    void viewCustomerProfile(const string& username) const;

    void confirmBooking();
    void confirmRental();
    void confirmPurchase();
    void cancelBooking();
    void cancelRental();
    void cancelPurchase();

    Car* findCarByID(int carID);
    const Customer* findCustomerByUsername(const string& username) const;
    int getCustomerIDByUsername(const string& username) const;

public:
    ApplicationManager();
    void run();
};

#endif
