
#ifndef SCHOOL_MANAGEMENT_H
#define SCHOOL_MANAGEMENT_H

#include "Class.h"
#include "Finance.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "json.hpp"
#include "Input.h"

class SchoolManagement {
  public:
    SchoolManagement();

    void set_name_of_school(const std::string& name_of_school);
    const std::string& get_name_of_school() const;

    // adds new admission and returns roll number of student
    int recordNewAdmission(Class_type classType, const Student& student);
    void deleteAdmission(Class_type classType, int roll);

    void viewStudentPersonalInfo(Class_type class_type, int roll) const;
    void viewStudentFeeInfo(Class_type class_type, int roll) const;

    void submitFees(Class_type classType, Acad_month acadMonth, double fees, int roll);
    int countStudentsWithUnsubmittedFees() const;

    // JSON Serialization and Deserialization methods
    nlohmann::json toJson() const;
    void fromJson(const nlohmann::json& jsonData);

    // New functions for serialization
    void saveDataToFile(const std::string& filename);
    void loadDataFromFile(const std::string& filename);

    void setInitialConfig();
    void loadConfigFromFile(std::ifstream &configFile);

  private:
    std::string name_of_school;
    std::map<Class_type, Class> Classes;
    Finance_Dept finance_dept;
};

#endif // SCHOOL_MANAGEMENT_H
