#include "Constants.h"
#include <iostream>

// Define the constant variables
int Class_Capacity = 30;

// Define the array of fees for each class
// The order should match the Class_type enum
double APRIL_FEES[] = {
    0.0, // Placeholder values, will be set by the user
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0
};

void set_Class_Capacity() {
  std::cout << "Enter the Class capacity for any class : \n";
  std::cin >> Class_Capacity;
}

void setAprilFees() {
    std::cout << "Enter the fees for each class for the month of April:\n";
    for (int i = NURSERY; i <= X; i++) {
        Class_type class_type = static_cast<Class_type>(i);
        std::cout << "Enter the fee for Class " << i + 1 << ": ";
        std::cin >> APRIL_FEES[i];
    }
}

