#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Car.h"
#include "Customer.h"
#include "PurchaseOrder.h"
#include "RentalOrder.h"
#include "TestDriveBooking.h"

#include <string>
#include <vector>

using namespace std;

class FileManager {
public:
    static vector<Car> loadCars(const string& fileName);
    static void saveCars(const string& fileName, const vector<Car>& cars);

    static vector<Customer> loadCustomers(const string& fileName);
    static void saveCustomers(const string& fileName, const vector<Customer>& customers);

    static vector<TestDriveBooking> loadBookings(const string& fileName);
    static void saveBookings(const string& fileName, const vector<TestDriveBooking>& bookings);

    static vector<RentalOrder> loadRentals(const string& fileName);
    static void saveRentals(const string& fileName, const vector<RentalOrder>& rentals);

    static vector<PurchaseOrder> loadPurchases(const string& fileName);
    static void savePurchases(const string& fileName, const vector<PurchaseOrder>& purchases);

    static vector<string> loadLines(const string& fileName);
    static void saveLines(const string& fileName, const vector<string>& lines);
};

#endif
