#include "User.h"

#include <iostream>

using namespace std;

User::User() {
}

User::User(const string& username, const string& password, const string& role)
    : username(username), password(password), role(role) {
}

const string& User::getUsername() const { return username; }
const string& User::getPassword() const { return password; }
const string& User::getRole() const { return role; }

Admin::Admin() : User("", "", "admin") {
}

Admin::Admin(const string& username, const string& password)
    : User(username, password, "admin") {
}

void Admin::showRoleMenu() const {
    cout << "\nAdmin Menu\n";
    cout << "1. View all cars\n";
    cout << "2. Add car\n";
    cout << "3. Update car\n";
    cout << "4. Delete car\n";
    cout << "5. View test drive bookings\n";
    cout << "6. View rental orders\n";
    cout << "7. Save data\n";
    cout << "0. Logout\n";
}

CustomerUser::CustomerUser() : User("", "", "customer") {
}

CustomerUser::CustomerUser(const string& username, const string& password)
    : User(username, password, "customer") {
}

void CustomerUser::showRoleMenu() const {
    cout << "\nCustomer Menu\n";
    cout << "1. View available cars\n";
    cout << "2. Search by brand\n";
    cout << "3. Book test drive\n";
    cout << "4. Rent a car\n";
    cout << "5. View my profile\n";
    cout << "0. Logout\n";
}
