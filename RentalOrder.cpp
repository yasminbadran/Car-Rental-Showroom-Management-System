#include "RentalOrder.h"

#include <iostream>
#include <sstream>

using namespace std;

RentalOrder::RentalOrder()
    : rentalID(0), carID(0), customerID(0), numberOfDays(0),
      deliveryOption(false), deliveryFee(0.0), totalCost(0.0), status("Pending") {
}

RentalOrder::RentalOrder(int rentalID, int carID, int customerID, int numberOfDays,
                         bool deliveryOption, const std::string& deliveryAddress,
                         double deliveryFee, double totalCost, const std::string& status)
    : rentalID(rentalID), carID(carID), customerID(customerID), numberOfDays(numberOfDays),
      deliveryOption(deliveryOption), deliveryAddress(deliveryAddress),
      deliveryFee(deliveryFee), totalCost(totalCost), status(status) {
}

int RentalOrder::getRentalID() const { return rentalID; }
int RentalOrder::getCarID() const { return carID; }
int RentalOrder::getCustomerID() const { return customerID; }
int RentalOrder::getNumberOfDays() const { return numberOfDays; }
double RentalOrder::getTotalCost() const { return totalCost; }
const string& RentalOrder::getStatus() const { return status; }

void RentalOrder::setDelivery(bool hasDelivery, const string& address, double fee) {
    deliveryOption = hasDelivery;
    deliveryAddress = address;
    deliveryFee = fee;
}

double RentalOrder::calculateRentalCost(double dailyRentalPrice) const {
    return (dailyRentalPrice * numberOfDays) + deliveryFee;
}

void RentalOrder::setStatus(const string& newStatus) {
    status = newStatus;
}

void RentalOrder::confirmRental() {
    status = "Confirmed";
}

void RentalOrder::cancelRental() {
    status = "Cancelled";
}

string RentalOrder::toDisplayString() const {
    ostringstream output;
    output << "Rental ID: " << rentalID
           << " | Car ID: " << carID
           << " | Customer ID: " << customerID
           << " | Days: " << numberOfDays
           << " | Delivery: " << (deliveryOption ? "Yes" : "No")
           << " | Address: " << deliveryAddress
           << " | Delivery Fee: " << deliveryFee
           << " | Total Cost: " << totalCost
           << " | Status: " << status;
    return output.str();
}

std::string RentalOrder::toFileString() const {
    std::ostringstream output;
    output << rentalID << '|'
           << carID << '|'
           << customerID << '|'
           << numberOfDays << '|'
           << deliveryOption << '|'
           << deliveryAddress << '|'
           << deliveryFee << '|'
           << totalCost << '|'
           << status;
    return output.str();
}

RentalOrder RentalOrder::fromFileString(const std::string& line) {
    std::stringstream input(line);
    std::string token;
    int rentalID = 0;
    int carID = 0;
    int customerID = 0;
    int numberOfDays = 0;
    bool deliveryOption = false;
    std::string deliveryAddress;
    double deliveryFee = 0.0;
    double totalCost = 0.0;
    std::string status;

    std::getline(input, token, '|');
    rentalID = std::stoi(token);
    std::getline(input, token, '|');
    carID = std::stoi(token);
    std::getline(input, token, '|');
    customerID = std::stoi(token);
    std::getline(input, token, '|');
    numberOfDays = std::stoi(token);
    std::getline(input, token, '|');
    deliveryOption = (token == "1");
    std::getline(input, deliveryAddress, '|');
    std::getline(input, token, '|');
    deliveryFee = std::stod(token);
    std::getline(input, token, '|');
    totalCost = std::stod(token);
    std::getline(input, status, '|');

    return RentalOrder(rentalID, carID, customerID, numberOfDays, deliveryOption,
                       deliveryAddress, deliveryFee, totalCost, status);
}
