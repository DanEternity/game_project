#pragma once

#include "enviroment.h"
#include <fstream>
#include <sstream>
#include <codecvt>

// Performs language load

// This is default supported language
// This function can be used as template for other locales
void LoadEnglishLocale();
void LoadRussianLocale();



void LoadLine(std::string locale, std::string baseLine, std::wstring localeLine);

// existed entries will be overwrited if duplicates occured
void LoadLocaleFromFile(std::string filename, std::string locale);

// Access to locales database. Basically short inline function. Will use current game language.
std::wstring GetString(std::string x);