#include "LocaleLoader.h"

void LoadEnglishLocale()
{

	auto db = &gEnv->game.locale.localeDB;

	(*db)["English"] = std::map<std::string, std::wstring>();
	(*db)["Russian"] = std::map<std::string, std::wstring>();

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

void LoadRussianLocale()
{

	auto db = &gEnv->game.locale.localeDB;

	

	LoadLocaleFromFile("\\resources\\localization\\ru_ru.txt", "Russian");

}

void LoadLine(std::string locale, std::string baseLine, std::wstring localeLine)
{
	gEnv->game.locale.localeDB[locale][baseLine] = localeLine;
}

void LoadLocaleFromFile(std::string filename, std::string locale)
{
	filename = gEnv->game.workDir + filename;

	std::wifstream wif(filename);

	if (wif.fail())
	{
		printf("Locale loader: Cant open file %s \n", filename.c_str());
	}


	wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::wstringstream wss;
	wss << wif.rdbuf();
	std::wstring content = std::wstring(wss.str());
	wss.clear();
	wif.close();

	// require content parsing
	// content is entire file

	int left_idx = 0;
	int right_idx = 0;
	bool work = true;

	while (work)
	{
		
		right_idx = content.find(L"####", left_idx);
		
		if (right_idx == std::wstring::npos)
			break;

		std::string base = "";

		for (int i(left_idx+1); i < right_idx; i++)
		{
			base += content[i];
		}

		left_idx = right_idx + 4;

		right_idx = content.find(L'\n', left_idx);

		if (right_idx == std::wstring::npos)
		{
			right_idx = content.size();
			work = false;
		}
		std::wstring locale_l;

		locale_l = content.substr(left_idx, right_idx - left_idx);

		left_idx = right_idx;

		LoadLine(locale, base, locale_l);

	}

}

std::wstring GetString(std::string x)
{
	return gEnv->game.locale.localeDB[gEnv->game.locale.gameLanguage][x];
}
