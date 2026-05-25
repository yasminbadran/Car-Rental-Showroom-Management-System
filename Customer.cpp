#include "Customer.h"

#include <iostream>
#include <sstream>

using namespace std;

Customer::Customer() : customerID(0) {
}

Customer::Customer(int customerID, const string& name, const string& phone,
                   const string& email, const string& address)
    : customerID(customerID), name(name), phone(phone), email(email), address(address) {
}

int Customer::getCustomerID() const { return customerID; }
const string& Customer::getName() const { return name; }
const string& Customer::getPhone() const { return phone; }
const string& Customer::getEmail() const { return email; }
const string& Customer::getAddress() const { return address; }

void Customer::updateCustomer(const string& newName, const string& newPhone,
                              const string& newEmail, const string& newAddress) {
    name = newName;
    phone = newPhone;
    email = newEmail;
    address = newAddress;
}

string Customer::toDisplayString() const {
    ostringstream output;
    output << "Customer ID: " << customerID
           << " | Name: " << name
           << " | Phone: " << phone
           << " | Email: " << email
           << " | Address: " << address;
    return output.str();
}

string Customer::toFileString() const {
    ostringstream output;
    output << customerID << '|'
           << name << '|'
           << phone << '|'
           << email << '|'
           << address;
    return output.str();
}

Customer Customer::fromFileString(const string& line) {
    stringstream input(line);
    string token;
    int customerID = 0;
    string name;
    string phone;
    string email;
    string address;

    getline(input, token, '|');
    customerID = stoi(token);
    getline(input, name, '|');
    getline(input, phone, '|');
    getline(input, email, '|');
    getline(input, address, '|');

    return Customer(customerID, name, phone, email, address);
}
