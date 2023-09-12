// exception is not handled in submit_fee

#include "Finance.h"
#include <iostream>

// Define the global finance_dept object of the Finance class
Finance_Dept finance_dept;

Finance_Dept::Finance_Dept() {
  for(int i = NURSERY; i <= X; i++){
    Class_type class_type = static_cast<Class_type>(i);
    studentsByGrade[class_type] = {};
  } // studentsByGrade(for finance) from Nursery to Tenth are initialised with 0 students in them
}

void Finance_Dept::add_Student_by_default(Class_type class_type, int unique_ID) {
  Student_fee_record student_fee_record;
  for (int i = 0; i < TOTAL_MONTHS; i++) {
    student_fee_record.fee_months_submitted[i] = false;
    student_fee_record.fee_submitted[i] = 0;
  }
  student_fee_record.fee_submitted[April] = APRIL_FEES[class_type];
  student_fee_record.fee_months_submitted[April] = true;
  student_fee_record.last_month_fees_submitted = Acad_month::April;

  // Add the student_fee_record to the studentsByGrade map
  studentsByGrade[class_type][unique_ID] = student_fee_record;
}


void Finance_Dept::add_Student(Class_type class_type, int unique_ID, const Student_fee_record& student_fee_record) {
  studentsByGrade[class_type][unique_ID] = student_fee_record;
}

void Finance_Dept::rem_Student(Class_type class_type, int unique_ID){
  studentsByGrade[class_type].erase(unique_ID);
}

void Finance_Dept::view_Student(Class_type class_type, int unique_ID) const {
  auto classIt = studentsByGrade.find(class_type);
  if (classIt != studentsByGrade.end()) {
    const std::map<int, Student_fee_record>& studentsData = classIt->second;
    auto studentIt = studentsData.find(unique_ID);
    if (studentIt != studentsData.end()) {
      const Student_fee_record& studentData = studentIt->second;

      std::cout << "Class: " << class_type << std::endl;
      std::cout << "Unique ID: " << unique_ID << std::endl;
      std::cout << "Last Month Fees Submitted: " << static_cast<Acad_month>(studentData.last_month_fees_submitted) << std::endl;
      std::cout << "Fees Submitted for Each Month: " << std::endl;

      for (int month = April; month <= March; month++) {
        std::cout << static_cast<Acad_month>(month) << ": ";
        if (studentData.fee_months_submitted[month]) {
          std::cout << "Submitted - " << studentData.fee_submitted[month] << std::endl;
        } else {
          std::cout << "Not Submitted" << std::endl;
        }
      }
    } else {
      std::cout << "Student with Unique ID " << unique_ID << " not found in Class " << class_type << "." << std::endl;
    }
  } else {
    std::cout << "Class " << class_type << " not found." << std::endl;
  }
}


void Finance_Dept::submit_fee(Class_type class_type, Acad_month acad_month, double fees, int unique_ID) {
  if(studentsByGrade[class_type][unique_ID].last_month_fees_submitted == acad_month) {
    // fees already submitted
    return;
  }
  studentsByGrade[class_type][unique_ID].fee_submitted[acad_month] = fees;
  studentsByGrade[class_type][unique_ID].fee_months_submitted[acad_month] = true;
  studentsByGrade[class_type][unique_ID].last_month_fees_submitted = acad_month;
}

void get_pending_fee::of_a_student(Class_type class_type, int unique_ID, Acad_month from, Acad_month upto) {
  Finance_Dept& finance_dept = ::finance_dept; 
  // Assuming ::finance_dept is the global instance of Finance_Dept

  const Finance_Dept::Student_fee_record& student_data = finance_dept.studentsByGrade[class_type][unique_ID];
  double pending_fee = 0.0;

  for (int month = from; month <= upto; ++month) {
    if (!student_data.fee_months_submitted[month]) {
      pending_fee += student_data.fee_submitted[month];
    }
  }

  std::cout << "Pending fee for student with Unique ID: " << unique_ID << std::endl;
  std::cout << "From month: " << from << std::endl;
  std::cout << "Upto month: " << upto << std::endl;
  std::cout << "Pending fee: " << pending_fee << std::endl;
}


void get_pending_fee::of_a_Class(Class_type class_type, Acad_month from, Acad_month upto) {
  Finance_Dept& finance_dept = ::finance_dept; 
  // Assuming ::finance_dept is the global instance of Finance_Dept

  const std::map<int, Finance_Dept::Student_fee_record>& students_data = finance_dept.studentsByGrade[class_type];
  double total_pending_fee = 0.0;

  for (const auto& student_data : students_data) {
    int unique_ID = student_data.first;
    const Finance_Dept::Student_fee_record& student_fee_record = student_data.second;

    for (int month = from; month <= upto; ++month) {
      if (!student_fee_record.fee_months_submitted[month]) {
        total_pending_fee += student_fee_record.fee_submitted[month];
      }
    }
  }
  std::cout << "Pending fee for Class: " << class_type << std::endl;
  std::cout << "From month: " << from << std::endl;
  std::cout << "Upto month: " << upto << std::endl;
  std::cout << "Total pending fee: " << total_pending_fee << std::endl;
}


// JSON Serialization for Finance_Dept
nlohmann::json Finance_Dept::toJson() const {
  nlohmann::json jsonData;

// Serialize studentsByGrade
  nlohmann::json studentsByGradeJson;
  for (const auto& gradeEntry : studentsByGrade) {
    Class_type class_type = gradeEntry.first;
    const std::map<int, Student_fee_record>& studentsData = gradeEntry.second;

    nlohmann::json studentsDataJson;
    for (const auto& studentEntry : studentsData) {
      int uniqueID = studentEntry.first;
      const Student_fee_record& studentData = studentEntry.second;

      nlohmann::json studentDataJson;
      for (int month = April; month <= March; month++) {
        studentDataJson["fee_submitted"][month] = studentData.fee_submitted[month];
        studentDataJson["fee_months_submitted"][month] = studentData.fee_months_submitted[month];
      }
      studentDataJson["last_month_fees_submitted"] = studentData.last_month_fees_submitted;

      studentsDataJson[std::to_string(uniqueID)] = studentDataJson;
    }

    studentsByGradeJson[std::to_string(class_type)] = studentsDataJson;
  }
  jsonData["studentsByGrade"] = studentsByGradeJson;

  return jsonData;
}

// JSON Deserialization for Finance_Dept
void Finance_Dept::fromJson(const nlohmann::json& jsonData) {
  // Clear existing data
  studentsByGrade.clear();

  // Deserialize studentsByGrade
  const nlohmann::json& studentsByGradeJson = jsonData["studentsByGrade"];
  for (const auto& gradeEntry : studentsByGradeJson.items()) {
    Class_type class_type = static_cast<Class_type>(std::stoi(gradeEntry.key()));
    const nlohmann::json& studentsDataJson = gradeEntry.value();

    std::map<int, Student_fee_record> studentsData;
    for (const auto& studentEntry : studentsDataJson.items()) {
      int uniqueID = std::stoi(studentEntry.key());
      const nlohmann::json& studentDataJson = studentEntry.value();

      Student_fee_record studentData;
      for (int month = April; month <= March; month++) {
        studentData.fee_submitted[month] = studentDataJson["fee_submitted"][month].get<double>();
        studentData.fee_months_submitted[month] = studentDataJson["fee_months_submitted"][month].get<bool>();
      }
      studentData.last_month_fees_submitted = studentDataJson["last_month_fees_submitted"].get<int>();

      studentsData[uniqueID] = studentData;
    }

    studentsByGrade[class_type] = studentsData;
  }
}

