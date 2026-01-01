#include "RollNumberManager.h"

RollNumberManager::RollNumberManager() : lastRollNumber(0) {}

void RollNumberManager::addRollNumber(int roll) {
  rollNumberContainer.insert(roll);
  lastRollNumber = roll;
}

void RollNumberManager::removeRollNumber(int roll) {
  rollNumberContainer.erase(roll);
}

int RollNumberManager::getLastRollNumber() const {
  return lastRollNumber;
}

int RollNumberManager::getFreshRollNumber() {
  int freshRollNumber = lastRollNumber + 1;
  while (rollNumberContainer.find(freshRollNumber) != rollNumberContainer.end()) {
    freshRollNumber++;
  }
  addRollNumber(freshRollNumber);
  return freshRollNumber;
}
