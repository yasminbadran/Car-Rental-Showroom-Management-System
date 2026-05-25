#include "Car.h"

#include <iomanip>
#include <sstream>

using namespace std;

Car::Car()
    : carID(0), year(0), salePrice(0.0), dailyRentalPrice(0.0),
      availableForSale(false), availableForRent(false), available(true) {
}

Car::Car(int carID, const string& brand, const string& model, int year,
         const string& type, double salePrice, double dailyRentalPrice,
         bool availableForSale, bool availableForRent, bool available)
    : carID(carID), brand(brand), model(model), year(year), type(type),
      salePrice(salePrice), dailyRentalPrice(dailyRentalPrice),
      availableForSale(availableForSale), availableForRent(availableForRent),
      available(available) {
}

int Car::getCarID() const { return carID; }
const string& Car::getBrand() const { return brand; }
const string& Car::getModel() const { return model; }
int Car::getYear() const { return year; }
const string& Car::getType() const { return type; }
double Car::getSalePrice() const { return salePrice; }
double Car::getDailyRentalPrice() const { return dailyRentalPrice; }
bool Car::isForSale() const { return availableForSale; }
bool Car::isRentable() const { return availableForRent; }
bool Car::isAvailable() const { return available; }

void Car::setAvailable(bool value) { available = value; }

void Car::setData(const string& newBrand, const string& newModel, int newYear,
                  const string& newType, double newSalePrice,
                  double newDailyRentalPrice, bool forSale, bool forRent,
                  bool isAvailableNow) {
    brand = newBrand;
    model = newModel;
    year = newYear;
    type = newType;
    salePrice = newSalePrice;
    dailyRentalPrice = newDailyRentalPrice;
    availableForSale = forSale;
    availableForRent = forRent;
    available = isAvailableNow;
}

void Car::updateCar(double newSalePrice, double newDailyRentalPrice, bool forSale,
                    bool forRent, bool isAvailableNow) {
    salePrice = newSalePrice;
    dailyRentalPrice = newDailyRentalPrice;
    availableForSale = forSale;
    availableForRent = forRent;
    available = isAvailableNow;
}

string Car::toDisplayString() const {
    ostringstream output;
    output << "ID: " << carID
           << " | Brand: " << brand
           << " | Model: " << model
           << " | Year: " << year
           << " | Type: " << type
           << " | Sale Price: " << fixed << setprecision(2) << salePrice
           << " | Daily Rent: " << dailyRentalPrice
           << " | For Sale: " << (availableForSale ? "Yes" : "No")
           << " | For Rent: " << (availableForRent ? "Yes" : "No")
           << " | Available: " << (available ? "Yes" : "No");
    return output.str();
}

string Car::toFileString() const {
    ostringstream output;
    output << carID << '|'
           << brand << '|'
           << model << '|'
           << year << '|'
           << type << '|'
           << salePrice << '|'
           << dailyRentalPrice << '|'
           << availableForSale << '|'
           << availableForRent << '|'
           << available;
    return output.str();
}

Car Car::fromFileString(const string& line) {
    stringstream input(line);
    string token;
    int carID = 0;
    string brand;
    string model;
    int year = 0;
    string type;
    double salePrice = 0.0;
    double dailyRentalPrice = 0.0;
    bool availableForSale = false;
    bool availableForRent = false;
    bool available = true;

    getline(input, token, '|');
    carID = stoi(token);
    getline(input, brand, '|');
    getline(input, model, '|');
    getline(input, token, '|');
    year = stoi(token);
    getline(input, type, '|');
    getline(input, token, '|');
    salePrice = stod(token);
    getline(input, token, '|');
    dailyRentalPrice = stod(token);
    getline(input, token, '|');
    availableForSale = (token == "1");
    getline(input, token, '|');
    availableForRent = (token == "1");
    getline(input, token, '|');
    available = (token == "1");

    return Car(carID, brand, model, year, type, salePrice, dailyRentalPrice,
               availableForSale, availableForRent, available);
}
