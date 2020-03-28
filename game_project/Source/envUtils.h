#pragma once

#include "enviroment.h"

//
// This file contain usefull functions to interact with enviroment
// These functions provide safe way to create, modify and delete
// items in enviroment
//

// Model Descriptor

#pragma region createModelDescriptor(std::wstring name)
///
/// <summary> Creates object ModelDescriptor and stores it in 
/// enviroment database (modelDB). </summary>
/// <param name="name"> Key in modelDB that used to access object. Any string value can be used. Dublications should be avoided. </param>
/// <param name="pathToFile"> Path to texture file. Relative path should be used. </param>
/// <param name="highPriority"> Indicates should file be loaded before actual start of loading. Usefull if file should be used imediantly. </param>
///
bool createModelDescriptor(std::wstring name);
#pragma endregion

#pragma region createModelDescriptor(std::wstring name, std::wstring pathToFile, bool highPriority = false)
///
/// <summary> Creates object ModelDescriptor and stores it in 
/// enviroment database (modelDB). </summary>
/// <param name="name"> Key in modelDB that used to access object. Any string value can be used. Dublications should be avoided. </param>
/// <param name="pathToFile"> Path to texture file. Relative path should be used. </param>
/// <param name="highPriority"> Indicates should file be loaded before actual start of loading. Usefull if file should be used imediantly. </param>
///
bool createModelDescriptor(std::wstring name, std::string pathToFile, bool highPriority = false);
#pragma endregion

#pragma region getModelDescriptor(std::wstring name)
///
/// <summary> Acceses element in ModelDB. Will return NULL if such object does no exist </summary>
/// <param name="name"> Key in modelDB that used to access object. Any string value can be used. Dublications should be avoided. </param>
///
ModelDescriptor * getModelDescriptor(std::wstring name);
#pragma endregion

#pragma region deleteModelDescriptor(std::wstring name)
///
/// <summary> Warnign: Model Descriptors are not suitable for deleting. Use this function at your own risk </summary>
/// <param name="name"> Key in modelDB that used to access object. Any string value can be used. Dublications should be avoided. </param>
///
bool deleteModelDescriptor(std::wstring name);
#pragma endregion

#pragma region loadTextureToModelDescriptor(std::wstring name)
///
/// <summary> Loads texture from file binded to ModelDescriptor. If no path to file provided or other error returns FALSE.
/// True in other ways </summary>
/// <param name="name"> Key in modelDB that used to access object. Any string value can be used. Dublications should be avoided. </param>
///
bool loadTextureToModelDescriptor(std::wstring name);
#pragma endregion

#pragma region createScriptDescriptor()
///
/// <summary> Creates object ScriptDescriptor and stores in enviroment.
/// Will return NULL if failed.
/// </summary>
/// 
///
ScriptDescriptor * createScriptDescriptor();
#pragma endregion

#pragma region getScriptDescriptor(int tableId)
///
/// <summary> Returns a ScriptDescriptor with selected id.
/// Will return NULL if failed.
/// </summary>
/// 
///
ScriptDescriptor * getScriptDescriptor(int id);
#pragma endregion

#pragma region createScriptCommand(scriptType::ScriptType type)
///
/// <summary> Creates a script command of selected type.
/// Will return NULL if failed.
/// </summary>
/// 
///
BaseScript * createScriptCommand(scriptType::ScriptType type);
#pragma endregion

#pragma region addScriptToQueue(ScriptDescriptor * sd)
///
/// <summary> Adds ScriptDescriptor to the global script queue.
/// This will result that script will be executed when script system is ready.
/// </summary>
/// 
///
bool addScriptToQueue(ScriptDescriptor * sd);
#pragma endregion

#pragma region createExternalTable()
///
/// <summary> Creates External table and returns its name
/// 
/// </summary>
/// 
///
std::wstring createExternalTable();
#pragma endregion

#pragma region deleteExternalTable(std::wstring id)
///
/// <summary> Deletes external table and all "free" objects inside
/// 
/// </summary>
/// 
///
void deleteExternalTable(std::wstring id);
#pragma endregion