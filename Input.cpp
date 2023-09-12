#include "Input.h"

const int Input::get_int_input(const char* prompt) {
  int temp;
  std::cout << prompt;
  std::cin >> temp;
  return temp;
}

const double Input::get_double_input(const char* prompt) {
  double temp;
  std::cout << prompt;
  std::cin >> temp;
  return temp;
}

const bool Input::get_bool_input(const char* prompt) {
  bool temp;
  std::cout << prompt;
  std::cin >> temp;
  return temp;
}

const std::string Input::get_string_input(const char* prompt) {
  std::string temp;
  std::cout << prompt;
  std::cin >> temp;
  return temp;
}

Class_type Input::get_class_type(const char *prompt) {
  int input = 0;
  std::cout << prompt << std::endl;
  std::cout << "Press the respective button for admission into the respective class.\n";

  // Print the available class options
  for (int i = NURSERY; i <= X; i++) {
    std::cout << "Press " << i << " for " << getClassTypeString(static_cast<Class_type>(i)) << std::endl;
  }

  // Validate user input
  while (true) {
    std::cout << "Enter your choice: ";
    std::cin >> input;

    // Check if the input is valid (within the range of Class_type enum)
    if (input >= NURSERY && input <= X) {
      // Clear any remaining input from the buffer
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      break;
    } else {
      std::cout << "Invalid input! Please enter a valid option.\n";
      // Clear the error flag for cin and ignore any remaining input from the buffer
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return static_cast<Class_type>(input);
}

Acad_month Input::get_acad_month(const char *prompt)
{
  int input = 0;
  std::cout << prompt << std::endl;
  std::cout << "Press the respective button for the academic month.\n";

  // Print the available academic month options
  for (int i = April; i <= March; i++)
  {
    std::cout << "Press " << i << " for " << getAcadMonthString(static_cast<Acad_month>(i)) << std::endl;
  }

  // Validate user input
  while (true)
  {
    std::cout << "Enter your choice: ";
    std::cin >> input;

    // Check if the input is valid (within the range of Acad_month enum)
    if (input >= April && input <= March)
    {
      // Clear any remaining input from the buffer
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      break;
    }
    else
    {
      std::cout << "Invalid input! Please enter a valid option.\n";
      // Clear the error flag for cin and ignore any remaining input from the buffer
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  return static_cast<Acad_month>(input);
}

// Helper function to get the string representation of Class_type
std::string Input::getClassTypeString(Class_type classType) {
  switch (classType) {
    case NURSERY: return "NURSERY";
    case LKG : return "LKG";
    case UKG : return "UKG";
    case I : return "I";
    case II : return "II";
    case III : return "III";
    case IV : return "IV";
    case V : return "V";
    case VI : return "VI";
    case VII : return "VII";
    case VIII : return "VIII";
    case IX : return "IX";
    case X: return "X";
    default: return "UNKNOWN";
  }
}

std::string Input::getAcadMonthString(Acad_month acadMonth) {
  switch (acadMonth) {
    case January: return "JANUARY";
    case February: return "FEBRUARY";
    case March: return "MARCH";
    case April: return "APRIL";
    case May: return "MAY";
    case June: return "JUNE";
    case July: return "JULY";
    case August: return "AUGUST";
    case September: return "SEPTEMBER";
    case October: return "OCTOBER";
    case November: return "NOVEMBER";
    case December: return "DECEMBER";
    default: return "UNKNOWN";
  }
}