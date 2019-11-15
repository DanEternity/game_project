#pragma once

#include <string>

bool isUfloat(const std::wstring& s) {
	bool correct = true;
	int pointcount = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '.')
		{
			pointcount++;
		}
		if (pointcount == 2) return false;
	}
	return s.find_first_not_of(L".0123456789") == std::wstring::npos;
}