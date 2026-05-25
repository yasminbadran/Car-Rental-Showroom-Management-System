#ifndef PURCHASEORDER_H
#define PURCHASEORDER_H

#include <string>

using namespace std;

class PurchaseOrder {
private:
    int purchaseID;
    int carID;
    int customerID;
    string paymentMethod;
    string status;

public:
    PurchaseOrder();
    PurchaseOrder(int purchaseID, int carID, int customerID,
                  const string& paymentMethod, const string& status);

    int getPurchaseID() const;
    int getCarID() const;
    int getCustomerID() const;
    const string& getStatus() const;

    void setStatus(const string& newStatus);
    void confirmPurchase();
    void cancelPurchase();
    string toDisplayString() const;
    string toFileString() const;
    static PurchaseOrder fromFileString(const string& line);
};

#endif
