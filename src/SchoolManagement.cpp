#include "SchoolManagement.h"
#include "Constants.h"

std::string CLASS_NAMES[13] = {
  "NURSERY", "LKG", "UKG", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X"
};

SchoolManagement::SchoolManagement() {
  // Read the school name and other details from the configuration file
  std::ifstream configFile("config.txt");
  if (configFile.is_open()) {
    // Configuration file found, load data from it
    loadConfigFromFile(configFile);
    configFile.close();
  } else {
    // Configuration file not found, ask the user to enter the details
    std::cout << "Welcome! Since this is the first time running the program, please provide some details." << std::endl;
    setInitialConfig();
  }

  // Check if "school_data.json" exists
  if (std::ifstream("school_data.json")) {
    // If the file exists, load data from it
    loadDataFromFile("school_data.json");
  } else {
    // If the file doesn't exist, start with a fresh state
    std::cout << "No existing data found. Starting with a fresh state." << std::endl;
    // Rest of your code to set up initial configuration goes here...
  }

  // Now, proceed to initialize the Classes map
  Class_type class_type;
  Class _class;
  for (int i = NURSERY; i <= X; i++) {
    class_type = static_cast<Class_type>(i);
    _class.set_class_type(class_type);
    Classes[class_type] = _class;
  }
}

void SchoolManagement::loadConfigFromFile(std::ifstream &configFile) {
  std::string line;

  // Read the school name
  std::getline(configFile, name_of_school);

  // Read the class capacity
  std::getline(configFile, line);
  Class_Capacity = std::stoi(line);

  // Read the array of fees for each class
  for (int i = NURSERY; i <= X; i++) {
    std::getline(configFile, line);
    APRIL_FEES[i] = std::stod(line);
  }
}

void SchoolManagement::setInitialConfig() {
  // Ask the user to enter the school name
  std::cout << "Please enter the name of the school: ";
  std::getline(std::cin, name_of_school);

  // Ask the user to enter the class capacity
  Class_Capacity = Input::get_int_input("Please enter the class capacity: ");

  // Ask the user to enter the fees for each class
  for (int i = NURSERY; i <= X; i++) {
    std::cout << "Please enter the fee for Class " << CLASS_NAMES[i];
    APRIL_FEES[i] = Input::get_double_input(" : ");
  }

  // Create/update the configuration file with the entered data
  std::ofstream configFile("config.txt");
  if (configFile.is_open()) {
    configFile << name_of_school << "\n";
    configFile << Class_Capacity << "\n";
    for (int i = NURSERY; i <= X; i++) {
      configFile << APRIL_FEES[i] << "\n";
    }
    configFile.close();
    std::cout << "Configuration details saved to config.txt." << std::endl;
  } else {
    std::cerr << "Error: Unable to create/update configuration file." << std::endl;
    exit(1);
  }
}

void SchoolManagement::set_name_of_school(const std::string& name_of_school){
  this->name_of_school = name_of_school;
}

const std::string& SchoolManagement::get_name_of_school() const {
  return name_of_school;
}

int SchoolManagement::recordNewAdmission(Class_type class_type, const Student &student) {
  int roll = Classes[class_type].add_student(student);
  int unique_ID = Classes[class_type].get_unique_ID_for_student(roll);
  finance_dept.add_Student_by_default(class_type, unique_ID);
  return roll;
}

void SchoolManagement::deleteAdmission(Class_type class_type, int roll) {
  int unique_ID = Classes[class_type].get_unique_ID_for_student(roll);
  Classes[class_type].rem_student(roll);
  finance_dept.rem_Student(class_type, unique_ID);
}

void SchoolManagement::viewStudentPersonalInfo(Class_type class_type, int roll) const {
    int unique_ID = Classes.at(class_type).get_unique_ID_for_student(roll);
    Classes.at(class_type).view_student_info(roll);
}

void SchoolManagement::viewStudentFeeInfo(Class_type class_type, int roll) const {
    int unique_ID = Classes.at(class_type).get_unique_ID_for_student(roll);
    finance_dept.view_Student(class_type, unique_ID);
}

void SchoolManagement::submitFees(Class_type class_type, Acad_month acadMonth, double fees, int roll) {
    int unique_ID = Classes[class_type].get_unique_ID_for_student(roll);
    finance_dept.submit_fee(class_type, acadMonth, fees, unique_ID);
}

int SchoolManagement::countStudentsWithUnsubmittedFees() const
{
    // Code to count students with unsubmitted fees from 3 months
    int count = 0;
    // ...
    return count;
}

// JSON Serialization for SchoolManagement
nlohmann::json SchoolManagement::toJson() const
{
    nlohmann::json jsonData;

    // Serialize school name
    jsonData["name_of_school"] = name_of_school;

    // Serialize Classes
    nlohmann::json classesJson;
    for (const auto &classEntry : Classes)
    {
        Class_type classType = classEntry.first;
        const Class &classData = classEntry.second;

        // Serialize each Class object to JSON
        classesJson[std::to_string(classType)] = classData.toJson();
    }
    jsonData["Classes"] = classesJson;

    // Serialize finance_dept
    jsonData["finance_dept"] = finance_dept.toJson();

    return jsonData;
}

// JSON Deserialization for SchoolManagement
void SchoolManagement::fromJson(const nlohmann::json &jsonData)
{
    // Clear existing data
    Classes.clear();

    // Deserialize school name
    name_of_school = jsonData["name_of_school"].get<std::string>();

    // Deserialize Classes
    const nlohmann::json &classesJson = jsonData["Classes"];
    for (const auto &classEntry : classesJson.items())
    {
        Class_type classType = static_cast<Class_type>(std::stoi(classEntry.key()));
        const nlohmann::json &classDataJson = classEntry.value();

        Class classData;
        classData.fromJson(classDataJson);

        // Add deserialized Class object to Classes map
        Classes[classType] = classData;
    }

    // Deserialize finance_dept
    const nlohmann::json &financeDeptJson = jsonData["finance_dept"];
    finance_dept.fromJson(financeDeptJson);
}

void SchoolManagement::saveDataToFile(const std::string &filename) {
    // Convert SchoolManagement object to JSON
    nlohmann::json jsonData = toJson();

    // Save JSON data to a file
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
      outputFile << jsonData.dump(4); // Pretty print with indentation of 4 spaces
      outputFile.close();
      std::cout << "Data saved to file: " << filename << std::endl;
    } else {
      std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
    }
}

void SchoolManagement::loadDataFromFile(const std::string &filename)
{
  // Load JSON data from the file
  std::ifstream inputFile(filename);
  if (inputFile.is_open()) {
    nlohmann::json jsonData;
    inputFile >> jsonData;

    // Deserialize JSON data into SchoolManagement object
    fromJson(jsonData);

    inputFile.close();
    std::cout << "Data loaded from file: " << filename << std::endl;
  } else {
    std::cerr << "Error: Unable to open file for reading: " << filename << std::endl;
  }
}
