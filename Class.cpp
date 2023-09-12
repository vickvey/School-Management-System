#include "Class.h"
#include <iostream>

const int default_num_in_class = 30;

Class::Class() : class_type(Class_type::NURSERY), cap(default_num_in_class){};

Class::Class(Class_type class_type, int cap) : class_type(class_type), cap(cap){};

void Class::set_class_type(Class_type class_type)
{
  this->class_type = class_type;
}

void Class::set_cap(int cap)
{
  this->cap = cap;
}

int Class::add_student(const Student &student)
{
  int unique_ID = unique_ID_Manager.getFreshUniqueID();
  int roll = rollNumberManager.getFreshRollNumber();

  std::pair<int, int> temp = std::make_pair(unique_ID, roll);
  students.insert(std::make_pair(temp, student));
  return roll;
}

void Class::rem_student(int roll)
{
  for (auto it = students.begin(); it != students.end(); ++it)
  {
    if ((it->first).second == roll)
    {
      students.erase(it);
      return;
    }
  }
}

int Class::get_number_of_students() const
{
  return students.size();
}

void Class::view_student_info(int roll) const
{
  auto it = students.find({get_unique_ID_for_student(roll), roll});
  if (it != students.end())
  {
    const Student &student = it->second;

    std::cout << "Student Roll Number: " << roll << std::endl;
    std::cout << "Name: " << student.name << std::endl;
    std::cout << "Aadhar Number: " << student.aadhar_number << std::endl;
    std::cout << "Father's Name: " << student.father_name << std::endl;
    std::cout << "Date of Birth: " << student.date_of_birth << std::endl;
  }
  else
  {
    std::cout << "Student with Roll Number " << roll << " not found." << std::endl;
  }
}

void Class::view_all_students_info() const
{
  if (students.empty())
  {
    std::cout << "No students enrolled in this class." << std::endl;
    return;
  }

  std::cout << "Students Enrolled in Class " << class_type << ":" << std::endl;

  for (const auto &entry : students)
  {
    int roll = entry.first.second;
    const Student &student = entry.second;

    std::cout << "----------------------------------" << std::endl;
    std::cout << "Roll Number: " << roll << std::endl;
    std::cout << "Name: " << student.name << std::endl;
    std::cout << "Aadhar Number: " << student.aadhar_number << std::endl;
    std::cout << "Father's Name: " << student.father_name << std::endl;
    std::cout << "Date of Birth: " << student.date_of_birth << std::endl;
  }

  std::cout << "----------------------------------" << std::endl;
  std::cout << "Total Students: " << students.size() << std::endl;
}

int Class::get_unique_ID_for_student(int roll) const
{
  for (auto it = students.begin(); it != students.end(); ++it)
  {
    if ((it->first).second == roll)
    {
      return (it->first).first;
    }
  }
  return -1;
}

// JSON Serialization
nlohmann::json Class::toJson() const
{
  nlohmann::json jsonData;

  jsonData["cap"] = cap;
  jsonData["class_type"] = class_type;

  // Convert students map to JSON
  nlohmann::json studentsJson;
  for (const auto &studentEntry : students)
  {
    int uniqueID = studentEntry.first.first;
    int roll = studentEntry.first.second;
    const Student &student = studentEntry.second;

    nlohmann::json studentJson;
    studentJson["name"] = student.name;
    studentJson["aadhar_number"] = student.aadhar_number;
    studentJson["father_name"] = student.father_name;
    studentJson["date_of_birth"] = student.date_of_birth;

    // Add student data to studentsJson using uniqueID and roll as keys
    studentsJson[std::to_string(uniqueID)][std::to_string(roll)] = studentJson;
  }
  jsonData["students"] = studentsJson;

  return jsonData;
}

// JSON Deserialization
void Class::fromJson(const nlohmann::json &jsonData)
{
  // Clear existing data
  students.clear();

  // Deserialize class data
  cap = jsonData["cap"].get<int>();
  class_type = jsonData["class_type"].get<Class_type>();

  // Deserialize students map
  const nlohmann::json &studentsJson = jsonData["students"];
  for (const auto &uniqueIDEntry : studentsJson.items())
  {
    int uniqueID = std::stoi(uniqueIDEntry.key());
    const nlohmann::json &rollStudentsJson = uniqueIDEntry.value();
    for (const auto &rollEntry : rollStudentsJson.items())
    {
      int roll = std::stoi(rollEntry.key());
      const nlohmann::json &studentJson = rollEntry.value();

      Student student;
      student.name = studentJson["name"].get<std::string>();
      student.aadhar_number = studentJson["aadhar_number"].get<std::string>();
      student.father_name = studentJson["father_name"].get<std::string>();
      student.date_of_birth = studentJson["date_of_birth"].get<std::string>();

      // Add student to the students map using uniqueID and roll as keys
      students[std::make_pair(uniqueID, roll)] = student;
    }
  }
}
