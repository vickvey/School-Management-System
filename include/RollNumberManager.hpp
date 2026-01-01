
//----------------------RollNumberManager.h----------------------------//
#ifndef ROLL_NUMBER_MANAGER_H
#define ROLL_NUMBER_MANAGER_H

#include <set>

class RollNumberManager {
  public:
    RollNumberManager(); // Constructor

    void addRollNumber(int roll);
    void removeRollNumber(int roll);
    int getLastRollNumber() const; // Returns last used roll number

    // Returns a fresh roll number to use and adds it to the container
    int getFreshRollNumber();

  private:
    std::set<int> rollNumberContainer;
    int lastRollNumber;
};

#endif
//---------------------------------------------------------------------//
