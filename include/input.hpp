
//--------------------------Input.h------------------------------------//
#ifndef INPUT_H
#define INPUT_H

#include "constants.hpp"
#include <string>

class Input {
public:
  static const int get_int_input(const std::string &prompt);
  static const double get_double_input(const std::string &prompt);
  static const bool get_bool_input(const std::string &prompt);
  static const std::string get_string_input(const std::string &prompt);
  static Class_type get_class_type(const std::string &prompt);
  static Acad_month get_acad_month(const std::string &prompt);

private:
  // Helper function to get the string representation of Class_type
  static std::string getClassTypeString(Class_type classType);
  static std::string getAcadMonthString(Acad_month acadMonth);
};

#endif
//---------------------------------------------------------------------//
