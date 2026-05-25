#ifndef UI_H
#define UI_H

#include "Car.h"
#include "Customer.h"
#include "PurchaseOrder.h"
#include "RentalOrder.h"
#include "TestDriveBooking.h"

#include <string>
#include <vector>

class UI {
public:
    int mainMenu() const;
    int customerMenu() const;
    int adminMenu() const;
    int searchMenu() const;

    void loginMenu(std::string& username, std::string& password) const;
    void registerMenu(std::string& name, std::string& phone, std::string& email,
                      std::string& address, std::string& username,
                      std::string& password, std::string& role) const;

    void showMessage(const std::string& message) const;
    void pause() const;

    std::string getLine(const std::string& prompt) const;
    int getInt(const std::string& prompt) const;
    double getDouble(const std::string& prompt) const;
    bool getYesNo(const std::string& prompt) const;

    void showCars(const std::vector<Car>& cars) const;
    void showCustomers(const std::vector<Customer>& customers) const;
    void showBookings(const std::vector<TestDriveBooking>& bookings) const;
    void showRentals(const std::vector<RentalOrder>& rentals) const;
    void showPurchases(const std::vector<PurchaseOrder>& purchases) const;

    Car getNewCarData(int carID) const;
    void getCarUpdateData(double& salePrice, double& dailyRentalPrice,
                          bool& forSale, bool& forRent, bool& available) const;
};

#endif
