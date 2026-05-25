#ifndef RENTALORDER_H
#define RENTALORDER_H

#include <string>

using namespace std;

class RentalOrder {
private:
    int rentalID;
    int carID;
    int customerID;
    int numberOfDays;
    bool deliveryOption;
    string deliveryAddress;
    double deliveryFee;
    double totalCost;
    string status;

public:
    RentalOrder();
    RentalOrder(int rentalID, int carID, int customerID, int numberOfDays,
                bool deliveryOption, const string& deliveryAddress,
                double deliveryFee, double totalCost, const string& status);

    int getRentalID() const;
    int getCarID() const;
    int getCustomerID() const;
    int getNumberOfDays() const;
    double getTotalCost() const;
    const string& getStatus() const;

    void setDelivery(bool hasDelivery, const string& address, double fee);
    double calculateRentalCost(double dailyRentalPrice) const;
    void setStatus(const string& newStatus);
    void confirmRental();
    void cancelRental();
    string toDisplayString() const;
    string toFileString() const;
    static RentalOrder fromFileString(const string& line);
};

#endif
