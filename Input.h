
//--------------------------Input.h------------------------------------//
#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>
#include <limits>
#include "Constants.h"

class Input {
  public:
    static const int get_int_input(const char* prompt);
    static const double get_double_input(const char* prompt);
    static const bool get_bool_input(const char* prompt);
    static const std::string get_string_input(const char* prompt);
    static Class_type get_class_type(const char* prompt);
    static Acad_month get_acad_month(const char* prompt);

  private:
    // Helper function to get the string representation of Class_type
    static std::string getClassTypeString(Class_type classType);
    static std::string getAcadMonthString(Acad_month acadMonth);
};

#endif
//---------------------------------------------------------------------//