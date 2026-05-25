#ifndef TESTDRIVEBOOKING_H
#define TESTDRIVEBOOKING_H

#include <string>

using namespace std;

class TestDriveBooking {
private:
    int bookingID;
    int carID;
    int customerID;
    string date;
    string time;
    string status;

public:
    TestDriveBooking();
    TestDriveBooking(int bookingID, int carID, int customerID,
                     const string& date, const string& time,
                     const string& status);

    int getBookingID() const;
    int getCarID() const;
    int getCustomerID() const;
    const string& getStatus() const;

    void setStatus(const string& newStatus);
    void confirmBooking();
    void cancelBooking();
    string toDisplayString() const;
    string toFileString() const;
    static TestDriveBooking fromFileString(const string& line);
};

#endif
