#pragma once

#include "enviroment.h"

//
// This file contain usefull functions to interact with enviroment
// These functions provide safe way to create, modify and delete
// items in enviroment
//

// Model Descriptor

bool createModelDescriptor(std::string name);

bool createModelDescriptor(std::string name, std::string pathToFile, bool highPriority = false);

ModelDescriptor * getModelDescriptor(std::string name);

// Warnign: Model Descriptors are not suitable for deleting. Use this function at your own risk
bool deleteModelDescriptor(std::string name);