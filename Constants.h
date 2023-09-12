#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

enum Class_type {
  NURSERY = 0, LKG = 1, UKG = 2, I = 3, II = 4, III = 5,
  IV = 6, V = 7, VI = 8, VII = 9, VIII = 10, IX = 11, X = 12
};

enum Acad_month { // Academic months
  April = 0, May = 1, June = 2, July = 3, 
  August = 4, September = 5, October = 6, 
  November = 7, December = 8, January = 9, 
  February = 10, March = 11 
};

extern std::string CLASS_NAMES[13];

// Declare the maxm number of students in a class as extern
extern int Class_Capacity;
// Declare the array of fees for each class as extern
extern double APRIL_FEES[];

#endif
