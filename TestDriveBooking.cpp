#include "TestDriveBooking.h"

#include <iostream>
#include <sstream>

using namespace std;

TestDriveBooking::TestDriveBooking()
    : bookingID(0), carID(0), customerID(0), status("Pending") {
}

TestDriveBooking::TestDriveBooking(int bookingID, int carID, int customerID,
                                   const string& date, const string& time,
                                   const string& status)
    : bookingID(bookingID), carID(carID), customerID(customerID),
      date(date), time(time), status(status) {
}

int TestDriveBooking::getBookingID() const { return bookingID; }
int TestDriveBooking::getCarID() const { return carID; }
int TestDriveBooking::getCustomerID() const { return customerID; }
const string& TestDriveBooking::getStatus() const { return status; }

void TestDriveBooking::setStatus(const string& newStatus) {
    status = newStatus;
}

void TestDriveBooking::confirmBooking() {
    status = "Confirmed";
}

void TestDriveBooking::cancelBooking() {
    status = "Cancelled";
}

string TestDriveBooking::toDisplayString() const {
    ostringstream output;
    output << "Booking ID: " << bookingID
           << " | Car ID: " << carID
           << " | Customer ID: " << customerID
           << " | Date: " << date
           << " | Time: " << time
           << " | Status: " << status;
    return output.str();
}

string TestDriveBooking::toFileString() const {
    ostringstream output;
    output << bookingID << '|'
           << carID << '|'
           << customerID << '|'
           << date << '|'
           << time << '|'
           << status;
    return output.str();
}

TestDriveBooking TestDriveBooking::fromFileString(const string& line) {
    stringstream input(line);
    string token;
    int bookingID = 0;
    int carID = 0;
    int customerID = 0;
    string date;
    string time;
    string status;

    getline(input, token, '|');
    bookingID = stoi(token);
    getline(input, token, '|');
    carID = stoi(token);
    getline(input, token, '|');
    customerID = stoi(token);
    getline(input, date, '|');
    getline(input, time, '|');
    getline(input, status, '|');

    return TestDriveBooking(bookingID, carID, customerID, date, time, status);
}
