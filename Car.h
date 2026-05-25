#ifndef CAR_H
#define CAR_H

#include <string>

using namespace std;

class Car {
private:
    int carID;
    string brand;
    string model;
    int year;
    string type;
    double salePrice;
    double dailyRentalPrice;
    bool availableForSale;
    bool availableForRent;
    bool available;

public:
    Car();
    Car(int carID, const string& brand, const string& model, int year,
        const string& type, double salePrice, double dailyRentalPrice,
        bool availableForSale, bool availableForRent, bool available = true);

    int getCarID() const;
    const string& getBrand() const;
    const string& getModel() const;
    int getYear() const;
    const string& getType() const;
    double getSalePrice() const;
    double getDailyRentalPrice() const;
    bool isForSale() const;
    bool isRentable() const;
    bool isAvailable() const;

    void setAvailable(bool value);
    void setData(const string& newBrand, const string& newModel, int newYear,
                 const string& newType, double newSalePrice,
                 double newDailyRentalPrice, bool forSale, bool forRent,
                 bool isAvailableNow);
    void updateCar(double newSalePrice, double newDailyRentalPrice, bool forSale,
                   bool forRent, bool isAvailableNow);
    string toDisplayString() const;
    string toFileString() const;
    static Car fromFileString(const string& line);
};

#endif
