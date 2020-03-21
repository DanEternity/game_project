#include "scriptCompilerUtilityParsers.h"

int convertMarkerToLine(CompilerCommandTemplateDataBuffer * buffer, std::wstring marker)
{
	if (buffer->markers->find(marker) == buffer->markers->end())
	{
		// error
		printf("Error! [Line: %i] Undefined marker reference: (%ws)", buffer->line, marker.c_str());
		buffer->error = true;
	}

	return (*buffer->markers)[marker];
}

std::wstring convertExtReferences(CompilerCommandTemplateDataBuffer * buffer, std::wstring line)
{
	
	std::wstring res = L"";

	int lastIdx = 0;
	int idx = 0;

	// seek all "$ext:" transform to "$EXT:

	while (1)
	{
		idx = line.find(L"$ext:", idx + 1);
		if (idx == std::wstring::npos)
			break;
		line[idx + 1] = 'E';
		line[idx + 2] = 'X';
		line[idx + 3] = 'T';
	}

	idx = 0;

	while (1)
	{
		lastIdx = idx;

		if (idx == 0)
			idx = line.find(L"$EXT:", idx);
		else
			idx = line.find(L"$EXT:", idx + 1);
		if (idx == std::wstring::npos)
			break;
		int tmp = idx - lastIdx;
		res += line.substr(lastIdx, idx - lastIdx);

		// "$EXT:XXXX:VALUE"
		//  012345678901234

		int v = line.find(':', idx + 5);

		std::wstring tableId = line.substr(idx + 5, v - idx - 5);

		if (buffer->localExtReference->find(tableId) == buffer->localExtReference->end())
		{
			wprintf(L"Error! External table %s does not exist or not initialized", tableId.c_str());
			buffer->error = true;
			return std::wstring();
		}
		std::wstring newTableId = (*buffer->localExtReference)[tableId];

		res += line.substr(lastIdx + tmp, idx - lastIdx - tmp + 5);

		res += newTableId;

		idx = v;
	}
	res += line.substr(lastIdx, line.size() - lastIdx);
	return res;

}

ComparatorElement parseCondition(std::wstring s)
{

	// "true"
	// "value/const operator value/const"

	bool operatorFound = false;
	int size = 2;
	int pos = -1;

	if (!operatorFound && s.find(L"==", 0) != std::wstring::npos)
	{
		pos = s.find(L"==", 0);
		operatorFound = true;
	}

	if (!operatorFound && s.find(L"!=", 0) != std::wstring::npos)
	{
		pos = s.find(L"!=", 0);
		operatorFound = true;
	}

	if (!operatorFound && s.find(L"<=", 0) != std::wstring::npos)
	{
		pos = s.find(L"<=", 0);
		operatorFound = true;
	}

	if (!operatorFound && s.find(L">=", 0) != std::wstring::npos)
	{
		pos = s.find(L">=", 0);
		operatorFound = true;
	}

	if (!operatorFound && s.find(L"<>", 0) != std::wstring::npos)
	{
		pos = s.find(L"<>", 0);
		operatorFound = true;
	}

	if (operatorFound)
	{

		std::wstring f1;
		std::wstring op;
		std::wstring f2;

		int ps;

		f1 = s.substr(0, pos);
		// need to erase spaces
		ps = f1.find(' ');
		if (ps != std::wstring::npos)
			if (ps == 0)
				f1 = f1.substr(1, f1.size() - 1);

		ps = f1.find(' ');
		if (ps != std::wstring::npos)
			if (ps > 0)
				f1 = f1.substr(0, ps);


		op = s.substr(pos, size);

		f2 = s.substr(pos + size, s.size() - pos - size);
		ps = f2.find(' ');
		if (ps != std::wstring::npos)
			if (ps == 0)
				f2 = f2.substr(1, f2.size() - 1);

		ps = f2.find(' ');
		if (ps != std::wstring::npos)
			if (ps > 0)
				f2 = f2.substr(0, ps);

		return ComparatorElement(false, f1, op, f2);
	}

	size = 1;

	if (!operatorFound && s.find(L"<", 0) != std::wstring::npos)
	{
		pos = s.find(L"<", 0);
		operatorFound = true;
	}

	if (!operatorFound && s.find(L">", 0) != std::wstring::npos)
	{
		pos = s.find(L">", 0);
		operatorFound = true;
	}

	if (operatorFound)
	{
		std::wstring f1;
		std::wstring op;
		std::wstring f2;

		int ps;

		f1 = s.substr(0, pos);

		// need to erase spaces
		ps = f1.find(' ');
		if (ps != std::wstring::npos)
			if (ps == 0)
				f1 = f1.substr(1, f1.size() - 1);

		ps = f1.find(' ');
		if (ps != std::wstring::npos)
			if (ps > 0)
				f1 = f1.substr(0, ps);


		op = s.substr(pos, size);

		f2 = s.substr(pos + size, s.size() - pos - size);
		ps = f2.find(' ');
		if (ps != std::wstring::npos)
			if (ps == 0)
				f2 = f2.substr(1, f2.size() - 1);

		ps = f2.find(' ');
		if (ps != std::wstring::npos)
			if (ps > 0)
				f2 = f2.substr(0, ps);

		return ComparatorElement(false, f1, op, f2);
	}

	// assume that selection allready boolean type
	// probably need a check



	return ComparatorElement(true, s, L"", L"");
}
