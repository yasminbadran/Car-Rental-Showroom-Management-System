#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
protected:
    string username;
    string password;
    string role;

public:
    User();
    User(const string& username, const string& password, const string& role);
    virtual ~User() = default;

    const string& getUsername() const;
    const string& getPassword() const;
    const string& getRole() const;
    virtual void showRoleMenu() const = 0;
};

class Admin : public User {
public:
    Admin();
    Admin(const string& username, const string& password);
    void showRoleMenu() const override;
};

class CustomerUser : public User {
public:
    CustomerUser();
    CustomerUser(const string& username, const string& password);
    void showRoleMenu() const override;
};

#endif
