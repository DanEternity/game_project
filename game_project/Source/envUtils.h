#pragma once

#include "enviroment.h"

//
// This file contain usefull functions to interact with enviroment
// These functions provide safe way to create, modify and delete
// items in enviroment
//

// Model Descriptor

#pragma region createModelDescriptor(std::string name)
///
/// <summary> Creates object ModelDescriptor and stores it in 
/// enviroment database (modelDB). </summary>
/// <param name="name"> Key in modelDB that used to access object. Any string value can be used. Dublications should be avoided. </param>
/// <param name="pathToFile"> Path to texture file. Relative path should be used. </param>
/// <param name="highPriority"> Indicates should file be loaded before actual start of loading. Usefull if file should be used imediantly. </param>
///
bool createModelDescriptor(std::string name);
#pragma endregion

#pragma region createModelDescriptor(std::string name, std::string pathToFile, bool highPriority = false)
///
/// <summary> Creates object ModelDescriptor and stores it in 
/// enviroment database (modelDB). </summary>
/// <param name="name"> Key in modelDB that used to access object. Any string value can be used. Dublications should be avoided. </param>
/// <param name="pathToFile"> Path to texture file. Relative path should be used. </param>
/// <param name="highPriority"> Indicates should file be loaded before actual start of loading. Usefull if file should be used imediantly. </param>
///
bool createModelDescriptor(std::string name, std::string pathToFile, bool highPriority = false);
#pragma endregion

#pragma region getModelDescriptor(std::string name)
///
/// <summary> Acceses element in ModelDB. Will return NULL if such object does no exist </summary>
/// <param name="name"> Key in modelDB that used to access object. Any string value can be used. Dublications should be avoided. </param>
///
ModelDescriptor * getModelDescriptor(std::string name);
#pragma endregion

#pragma region deleteModelDescriptor(std::string name)
///
/// <summary> Warnign: Model Descriptors are not suitable for deleting. Use this function at your own risk </summary>
/// <param name="name"> Key in modelDB that used to access object. Any string value can be used. Dublications should be avoided. </param>
///
bool deleteModelDescriptor(std::string name);
#pragma endregion

#pragma region loadTextureToModelDescriptor(std::string name)
///
/// <summary> Loads texture from file binded to ModelDescriptor. If no path to file provided or other error returns FALSE.
/// True in other ways </summary>
/// <param name="name"> Key in modelDB that used to access object. Any string value can be used. Dublications should be avoided. </param>
///
bool loadTextureToModelDescriptor(std::string name);
#pragma endregion