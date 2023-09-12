//----------------------------------------------Finance.h------------------------------------------------//
#ifndef FINANCE_H
#define FINANCE_H

const int TOTAL_MONTHS = 12;
#include "Unique_ID_Container.h"
#include "Constants.h"
#include "json.hpp"
#include <map>

class Finance_Dept {
  public :
    Finance_Dept();
    typedef struct {
      double fee_submitted[TOTAL_MONTHS];
      bool fee_months_submitted[TOTAL_MONTHS];
      int last_month_fees_submitted; // relatd to Acad_Month enum (Apr, Mar)
    } Student_fee_record;

    /*
    This function will initialise default value for struct Student_fee_record 
    i.e.
    April month fee will be submitted by taking values from Constants.h :
    fee_submitted[April] = some_value_from_Constants.h and all other elements of array will be 0
    fee_months_submitted[April] = true and all other elements will be false
    last_month_fee_submitted = April
    */
    void add_Student_by_default(Class_type class_type, int unique_ID);
    void add_Student(Class_type class_type, int unique_ID, const Student_fee_record& student_fee_record);
    void rem_Student(Class_type class_type, int unique_ID);
    void view_Student(Class_type class_type, int unique_ID) const;
    void submit_fee(Class_type class_type, Acad_month acad_month, double fees, int unique_ID);

    // JSON Serialization and Deserialization methods
    nlohmann::json toJson() const;
    void fromJson(const nlohmann::json& jsonData);

    friend class get_pending_fee;
  private:
    std::map<Class_type, std::map<int, Student_fee_record>> studentsByGrade;
    // Outer map: Key is grade level (e.g., Nursery, LKG, UKG, ...)
    // Inner map: Key is unique_ID, Value is Student(financial data)
    // Outer map: Classtype -> map of a Class  
    // Inner map: unique_ID -> Student(financial data) 
};

class get_pending_fee {
  public :
    // Gives important information about pending fee of a student b/w an interval of months
    static void of_a_student(Class_type Class_type, int unique_ID, Acad_month from, Acad_month upto);

    // Gives important information about pending fee of a whole class b/w an interval of months
    static void of_a_Class(Class_type class_type, Acad_month from, Acad_month upto);
};

// create a global instance of Finance_dept class
extern Finance_Dept finance_dept;

#endif
//-------------------------------------------------------------------------------------------------------//