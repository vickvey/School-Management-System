
#include <iostream>
#include <string>
#include "Input.h"
#include "SchoolManagement.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

#include "SchoolManagement.h"
#include <iostream>

void add_new_Student(SchoolManagement& schoolManagement);
void delete_Student(SchoolManagement& schoolManagement);
void view_Student_Personal_Info(SchoolManagement& schoolManagement);
void view_Student_Fee_Info(SchoolManagement& schoolManagement);
void Submit_Fees(SchoolManagement& schoolManagement);
void countStudentWithUnsubmittedFees(SchoolManagement& schoolManagement);

int main() {
  // Initialize SchoolManagement object
  SchoolManagement schoolManagement;

  // Display the school name
  std::cout << "Welcome to " << schoolManagement.get_name_of_school() << " School Management System!" << std::endl;

  Class_type class_type;
  int choice;
  do
  {
    // Display the menu options
    std::cout << "\nMenu:\n";
    std::cout << "1. Add New Student\n";
    std::cout << "2. Delete Student\n";
    std::cout << "3. View Student Personal Info\n";
    std::cout << "4. View Student Fee Info\n";
    std::cout << "5. Submit Fees\n";
    std::cout << "6. Count Students with Unsubmitted Fees\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
      case 1:
        system("clear");
        add_new_Student(schoolManagement);
        break;
      case 2:
        system("clear");
        delete_Student(schoolManagement);
        break;
      case 3:
        system("clear");
        view_Student_Personal_Info(schoolManagement);
        break;
      case 4:
        system("clear");
        view_Student_Fee_Info(schoolManagement);
        break;
      case 5:
        system("clear");
        Submit_Fees(schoolManagement);
        break;
      case 6:
        system("clear");
        countStudentWithUnsubmittedFees(schoolManagement);
        break;
      case 0:
        std::cout << "Exiting program. Goodbye!" << std::endl;
        break;
      default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        break;
    }

  } while (choice != 0);

  // Save data to file before exiting
  schoolManagement.saveDataToFile("school_data.json");
  return 0;
}

void add_new_Student(SchoolManagement& schoolManagement) {
  Class_type class_type = Input::get_class_type("In which class would you add admisson into : ");
  // taking input of student info for class
  Student student;
  student.name = Input::get_string_input("Enter the name of the student : ");
  student.aadhar_number = Input::get_string_input("Enter the aadhar number of student : ");
  student.date_of_birth = Input::get_string_input("Enter the Date of Birth in (DD/MM/YYYY) format!\nfor e.g. 01/01/2000 : ");
  student.father_name = Input::get_string_input("Enter the father's name of student : ");
  system("clear");

  // taking input of student fee record for finance department
  std::cout << "Take the april fees of the student.\n";
  std::cout << "April fee will be submitted with the admission.\n";

  int roll = schoolManagement.recordNewAdmission(class_type, student);
  std::cout << "Student Admission taken successfully.\n";
  std::cout << "Here is the complete data of the student in our database : \n";
  std::cout << "The roll number of the student is : " << roll << "\n";
  std::cout << "Please note the allotted roll number for future references.\n";
  schoolManagement.viewStudentPersonalInfo(class_type, roll);
  schoolManagement.viewStudentFeeInfo(class_type, roll);
}

void delete_Student(SchoolManagement& schoolManagement) {
  Class_type class_type = Input::get_class_type("Enter the Class the student is in : ");
  int roll = Input::get_int_input("Enter the roll number of the student : ");
  std::cout << "Here is the details of the student to be removed in our database : \n";
  schoolManagement.viewStudentPersonalInfo(class_type, roll);
  schoolManagement.viewStudentFeeInfo(class_type, roll);
  std::cout << "press 1 to continue removing the student : ";
  bool input = Input::get_bool_input("Press 1 to continue removing student : ");
  schoolManagement.deleteAdmission(class_type, roll);
  std::cout << "Student removed successfully from the database.\n";
}

void view_Student_Personal_Info(SchoolManagement& schoolManagement) {
  Class_type class_type = Input::get_class_type("Enter the Class in which the student is enrolled in : ");
  int roll = Input::get_int_input("Enter the roll number of the student : ");
  std::cout << "Here is the personal information of student enrolled.\n";
  schoolManagement.viewStudentPersonalInfo(class_type, roll);
  int p = 0;
  std::cout << "If you want to see the Fee info of the student, ";
  p = Input::get_int_input("then Enter 1 : for seeing fee info.\n");
  if(p == 1) {
    schoolManagement.viewStudentFeeInfo(class_type, roll);
  }
}

void view_Student_Fee_Info(SchoolManagement& schoolManagement) {
  Class_type class_type = Input::get_class_type("Enter the Class in which the student is enrolled in : ");
  int roll = Input::get_int_input("Enter the roll number of the student : ");
  std::cout << "Here is the Fee information of student enrolled.\n";
  schoolManagement.viewStudentFeeInfo(class_type, roll);
}

void Submit_Fees(SchoolManagement& schoolManagement) {
  Class_type class_type = Input::get_class_type("Enter the class in which student is studying in : ");
  int roll = Input::get_int_input("Enter the roll number of the student : ");
  Acad_month acad_month = Input::get_acad_month("Enter the month for which you want to get your fee submitted : ");
  double fees = Input::get_double_input("Enter the fee amount for the month : ");

  schoolManagement.submitFees(class_type, acad_month, fees, roll);
  std::cout << "Fee is submitted.\n";
  std::cout << "Here is latest fee info for the student.\n";
  schoolManagement.viewStudentFeeInfo(class_type, roll);
}

void countStudentWithUnsubmittedFees(SchoolManagement& schoolManagement) {
  std::cout << "This feature is coming soon..\n";
}
