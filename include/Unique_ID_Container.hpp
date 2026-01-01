
//-----------------------------Unique_ID_Container.h----------------------------------//
#ifndef UNIQUE_ID_CONTAINER_H
#define UNIQUE_ID_CONTAINER_H

#include <set>
#include "json.hpp"

class Unique_ID_Container {
public:
    Unique_ID_Container(); // Constructor

    void addUniqueID(int uniqueID);
    void removeUniqueID(int uniqueID);
    int getLastUniqueID() const;   // returns last used ID

    // returns fresh ID to use and also adds that ID to container
    int getFreshUniqueID();

    // JSON Serialization
    nlohmann::json toJson() const;

    // JSON Deserialization
    void fromJson(const nlohmann::json& jsonData);

private:
    std::set<int> unique_ID_Container;
    int last_unique_ID;
};

// Create a global instance of the Unique_ID_Container class
extern Unique_ID_Container unique_ID_Manager;

#endif
//------------------------------------------------------------------------------------//
