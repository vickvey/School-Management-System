// This header file contains blueprint for student personal 
// information and student enrolled in Class info

//------------------------Class.h----------------------------------//
#ifndef CLASS_H
#define CLASS_H

#include "Unique_ID_Container.h"
#include "RollNumberManager.h"
#include "json.hpp"
#include "Constants.h"
#include <string>
#include <map>
#include <set>

typedef struct {
  std::string name;
  std::string aadhar_number; 
  std::string father_name;
  std::string date_of_birth; // DD/MM/YYYY format
} Student;

class Class {
  public :
    // Initialises class_type to NURSERY and cap to default
    Class();
    Class(Class_type class_type, int cap);

    void set_class_type(Class_type class_type);
    void set_cap(int cap);

    // returns roll number of studen after adding the student
    int add_student(const Student& student);
    
    void rem_student(int roll); 
    int get_number_of_students() const;
    void view_student_info(int roll) const;
    void view_all_students_info() const;

    int get_unique_ID_for_student(int roll) const;

    // JSON Serialization
    nlohmann::json toJson() const;

    // JSON Deserialization
    void fromJson(const nlohmann::json& jsonData);
    
  private :
    int cap; // total capacity of a Class
    Class_type class_type;

    // Map : pair(uniqueID,roll) -> Student
    std::map<std::pair<int,int>, Student> students;
    RollNumberManager rollNumberManager;
};

#endif
//-----------------------------------------------------------------//