#pragma once

//
// This file contain some localization staff
//
//

#include <map>
#include <string>



class LocaleData
{
public:
	// localization
	// localeDB["LANGUAGE"]["STRING_ID"] = STRING;
	
	std::map<std::string, std::map<std::string, std::wstring>> localeDB;

	// This probably should be loaded from file
	// except Eng laguage

	// This is default language
	std::string gameLanguage = "English";


};