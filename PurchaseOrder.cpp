#include "PurchaseOrder.h"

#include <sstream>

using namespace std;

PurchaseOrder::PurchaseOrder()
    : purchaseID(0), carID(0), customerID(0), paymentMethod("Cash"), status("Pending") {
}

PurchaseOrder::PurchaseOrder(int purchaseID, int carID, int customerID,
                             const std::string& paymentMethod, const std::string& status)
    : purchaseID(purchaseID), carID(carID), customerID(customerID),
      paymentMethod(paymentMethod), status(status) {
}

int PurchaseOrder::getPurchaseID() const { return purchaseID; }
int PurchaseOrder::getCarID() const { return carID; }
int PurchaseOrder::getCustomerID() const { return customerID; }
const string& PurchaseOrder::getStatus() const { return status; }

void PurchaseOrder::setStatus(const string& newStatus) {
    status = newStatus;
}

void PurchaseOrder::confirmPurchase() {
    status = "Confirmed";
}

void PurchaseOrder::cancelPurchase() {
    status = "Cancelled";
}

string PurchaseOrder::toDisplayString() const {
    ostringstream output;
    output << "Purchase ID: " << purchaseID
           << " | Car ID: " << carID
           << " | Customer ID: " << customerID
           << " | Payment Method: " << paymentMethod
           << " | Status: " << status;
    return output.str();
}

string PurchaseOrder::toFileString() const {
    ostringstream output;
    output << purchaseID << '|'
           << carID << '|'
           << customerID << '|'
           << paymentMethod << '|'
           << status;
    return output.str();
}

PurchaseOrder PurchaseOrder::fromFileString(const string& line) {
    stringstream input(line);
    string token;
    int purchaseID = 0;
    int carID = 0;
    int customerID = 0;
    string paymentMethod;
    string status;

    getline(input, token, '|');
    purchaseID = stoi(token);
    getline(input, token, '|');
    carID = stoi(token);
    getline(input, token, '|');
    customerID = stoi(token);
    getline(input, paymentMethod, '|');
    getline(input, status, '|');

    return PurchaseOrder(purchaseID, carID, customerID, paymentMethod, status);
}
