#include "LocaleLoader.h"

void LoadEnglishLocale()
{

	auto db = &gEnv->game.locale.localeDB;

	(*db)["English"] = std::map<std::string, std::wstring>();

	// example
	LoadLine("English", "Hello world", L"Hello world");

	LoadLine("English", "Engine", L"Engine");
	LoadLine("English", "Hyperdrive", L"Hyperdrive");
	LoadLine("English", "Core", L"Core");
	LoadLine("English", "System", L"System");
	LoadLine("English", "Primary weapon", L"Primary weapon");
	LoadLine("English", "Secondary weapon", L"Secondary weapon");
	LoadLine("English", "Universal", L"Universal");

	LoadLine("English", "No filter", L"No filter");

}

void LoadLine(std::string locale, std::string baseLine, std::wstring localeLine)
{
	gEnv->game.locale.localeDB[locale][baseLine] = localeLine;
}

std::wstring GetString(std::string x)
{
	return gEnv->game.locale.localeDB[gEnv->game.locale.gameLanguage][x];
}
