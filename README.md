# Car Rental & Showroom Management System 🚗

This is a C++ Object-Oriented Programming project for managing a car rental and showroom system.

The system allows customers to register, log in, view available cars, search and filter cars, book test drives, rent cars, and view their profile. It also includes an admin dashboard for managing cars, viewing rental orders, viewing test drive bookings, and saving updated data.

## Project Features

- Customer registration and login
- Admin login and dashboard
- View available cars
- Search and filter cars by brand
- Book a test drive
- Rent a car
- Manage customer profile
- Add, update, and delete cars
- View rental orders
- View test drive bookings
- Save and load data using text files

## Technologies Used

- C++
- Object-Oriented Programming (OOP)
- File Handling
- Text Files as a simple database
- Python
- HTML
- CSS
- JavaScript
- GUI Design

## Main C++ Classes

- ApplicationManager
- Car
- Customer
- User
- FileManager
- RentalOrder
- PurchaseOrder
- TestDriveBooking
- UI

## Data Files

The project uses text files to store and load data:

- cars.txt
- customers.txt
- users.txt
- rentals.txt
- purchases.txt
- bookings.txt

## Project Structure

```text
Car-Rental-Showroom-Management-System/
│
├── README.md
├── .gitignore
│
├── cpp-core/
│   ├── ApplicationManager.cpp
│   ├── ApplicationManager.h
│   ├── Car.cpp
│   ├── Car.h
│   ├── Customer.cpp
│   ├── Customer.h
│   ├── FileManager.cpp
│   ├── FileManager.h
│   ├── main.cpp
│   ├── PurchaseOrder.cpp
│   ├── PurchaseOrder.h
│   ├── RentalOrder.cpp
│   ├── RentalOrder.h
│   ├── TestDriveBooking.cpp
│   ├── TestDriveBooking.h
│   ├── UI.cpp
│   ├── UI.h
│   ├── User.cpp
│   └── User.h
│
├── data/
│   ├── bookings.txt
│   ├── cars.txt
│   ├── customers.txt
│   ├── purchases.txt
│   ├── rentals.txt
│   └── users.txt
│
└── gui/
    ├── app.py
    ├── index.html
    ├── styles.css
    ├── app.js
    ├── brand-logos/
    └── car_photos/
```

## GUI

The project includes a simple graphical interface with:

- Register and login page
- Car marketplace page
- Car cards with images and prices
- Search and filter options
- Test drive booking form
- Admin dashboard

The GUI files are available in the uploaded `GUI.rar` file.

## What I Learned

Through this project, I practiced how to build a structured application using C++ and OOP. I also learned how to organize code into multiple files, handle data using text files, and connect the main system logic with a simple GUI.

## Project Type

CSAI 151 - Phase 3 Project

## Author

Yasmin Badran
