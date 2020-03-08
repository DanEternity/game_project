#pragma once

#include "enviroment.h"

// Performs language load

// This is default supported language
// This function can be used as template for other locales
void LoadEnglishLocale();




void LoadLine(std::string locale, std::string baseLine, std::wstring localeLine);

std::wstring GetString(std::string x);