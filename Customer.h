#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

using namespace std;

class Customer {
private:
    int customerID;
    string name;
    string phone;
    string email;
    string address;

public:
    Customer();
    Customer(int customerID, const string& name, const string& phone,
             const string& email, const string& address);

    int getCustomerID() const;
    const string& getName() const;
    const string& getPhone() const;
    const string& getEmail() const;
    const string& getAddress() const;

    void updateCustomer(const string& newName, const string& newPhone,
                        const string& newEmail, const string& newAddress);
    string toDisplayString() const;
    string toFileString() const;
    static Customer fromFileString(const string& line);
};

#endif
