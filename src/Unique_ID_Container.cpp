#include "Unique_ID_Container.h"

Unique_ID_Container::Unique_ID_Container() : last_unique_ID(0) {}

void Unique_ID_Container::addUniqueID(int uniqueID)
{
  unique_ID_Container.insert(uniqueID);
  last_unique_ID = uniqueID;
}

void Unique_ID_Container::removeUniqueID(int uniqueID)
{
  unique_ID_Container.erase(uniqueID);
}

int Unique_ID_Container::getLastUniqueID() const
{
  return last_unique_ID;
}

int Unique_ID_Container::getFreshUniqueID()
{
  addUniqueID(last_unique_ID + 1);
  return last_unique_ID + 1;
} // also inserts fresh ID in uniqueIDContainer

// JSON Serialization
nlohmann::json Unique_ID_Container::toJson() const
{
  nlohmann::json jsonData;
  jsonData["last_unique_ID"] = last_unique_ID;

  for (int uniqueID : unique_ID_Container)
  {
    jsonData["unique_ID_Container"].push_back(uniqueID);
  }

  return jsonData;
}

// JSON Deserialization
void Unique_ID_Container::fromJson(const nlohmann::json &jsonData)
{
  unique_ID_Container.clear();
  last_unique_ID = jsonData["last_unique_ID"].get<int>();

  for (const auto &uniqueID : jsonData["unique_ID_Container"])
  {
    unique_ID_Container.insert(uniqueID.get<int>());
  }
}

// Define the global instance of Unique_ID_Container
Unique_ID_Container unique_ID_Manager;