#include "scriptCompiler.h"

bool ScriptCompiler::compileScriptText(std::vector<std::wstring> src)
{ 

	// Available directives
	//
	// #version "1" - version of used syntax (may need to get compability)
	//
	// #ext "xxx1" - identifier for external tables. This identifier will be
	// changed in process of compilation. But same identifiers still get
	// same replace. For example: all xxx1 -> 00A0
	//

	// List of supported special characters
	//	# - directive (has no effect while not at start of line)
	//	$ - value (has no effect while not in function)
	//	@ - marker (has no effect while not at start of line)
	//	_ - local variable (only for $_ )
	//	// - comment until end of line (may not working inside function)

	p_s = createScriptDescriptor();

	TemplateBuffer.localExtReference = &localExtReference;
	TemplateBuffer.markers = &markers;

	bool directiveHasOpenBracket;

	while (!error)
	{
		// ignore empty string
		if (src[line].empty())
		{
			if (line < src.size() - 1)
				line++;
			else
			{
				// end of file

				// if there are any selection we should process it
				// then finilize parsing because no text left;
				//
				break;
			}
			continue;
		}


		// check if symbol correct
		if (src[line][idx] < 60000)
		{
			// zero sybmols in selection
			if (emptyLine)
			{
				// directive
				if (src[line][idx] == '#')
				{
					// directive
					emptyLine = false;
					
					directiveHasOpenBracket = false;
					tp = syntaxType::directive;
				}

				if ((src[line][idx] >= 'a' && src[line][idx] <= 'z') || (src[line][idx] >= 'A' && src[line][idx] <= 'Z'))
				{
					// function

					// If started with any letter will be considered function name

					//selection += src[line][idx];
					emptyLine = false;
					tp = syntaxType::command;

				}

				if (src[line][idx] == '@')
				{
					// marker
					//selection += src[line][idx];
					emptyLine = false;
					tp = syntaxType::marker;
				}

				if (src[line][idx] == '/')
				{
					// this line is a comment
					emptyLine = false;
					tp = syntaxType::comment;
				}

				if (src[line][idx] <= '9' && src[line][idx] >= '0')
				{
					// invalid character

				}

			}

			if (tp == syntaxType::directive)
			{
				selection += src[line][idx];
				if (src[line][idx] == '"')
				{
					if (directiveHasOpenBracket)
					{

						// directive selection completed
						tp = syntaxType::none;

						parseDirecive(selection);

						selection = L"";
						emptyLine = true;

					}
					else
					{
						directiveHasOpenBracket = true;
					}
				}

				if (
					src[line][idx] == '/' ||
					src[line][idx] == '@' ||
					src[line][idx] == '#' ||
					src[line][idx] == '$' ||
					src[line][idx] == '[' ||
					src[line][idx] == ']' ||
					src[line][idx] == ';'
					)
				{
					// invalid symbol
					printf("Error while script parsing! Expected [#directive \"value\"] found (%ws <-)\n", selection.c_str());
					printf("Hint: You probably forgot \" \". Directive comments should be inside brackets.\n");
				}

			}

			if (tp == syntaxType::command)
			{
				selection += src[line][idx];
				if (src[line][idx] == '"' || src[line][idx] == ' ')
				{
					bool code = parseCommand(selection);
				}
				else
				{
					if (
						src[line][idx] == '/' ||
						src[line][idx] == '@' ||
						src[line][idx] == '#' ||
						src[line][idx] == ':' ||
						src[line][idx] == '$' ||
						src[line][idx] == '_' ||
						src[line][idx] == '[' ||
						src[line][idx] == ']' ||
						src[line][idx] == ';'
						)
						printf("Error while script parsing! [Line: %i] Invalid command: (%ws <-)", line, selection.c_str());

				}
			}

			if (tp == syntaxType::marker)
			{
				selection += src[line][idx];
				if (src[line][idx] == ' ')
				{
					parseMarker(selection);
					emptyLine = true;
					selection = L"";
					tp = syntaxType::none;
				}
			}


			if (tp == syntaxType::t_command)
			{

				if (checkTemplate())
				{
					// make object code
					completeCommand();
				}
				else
					collectNewSymbol(src[line][idx]);

			}

		}
		// move right
		if (idx < src[line].size() - 1 && src[line][idx] !='\n')
			idx++;
		else // next line
		{
			// probalby need to add space
			// because some functions can be parsed wrong if
			// located in multiple lines
			

			if (tp == syntaxType::comment)
			{
				tp = syntaxType::none;
				emptyLine = true;
				selection = L"";
			}
			if (tp == syntaxType::marker)
			{
				parseMarker(selection);
				emptyLine = true;
				selection = L"";
				tp = syntaxType::none;
			}

			if (tp == syntaxType::command)
			{
				bool code = parseCommand(selection);

				if (checkTemplate())
				{
					// make object code
					completeCommand();
				}

			}

			if (tp == syntaxType::directive)
			{
				selection += src[line][idx];
				if (src[line][idx] == '"')
				{
					if (directiveHasOpenBracket)
					{

						// directive selection completed
						tp = syntaxType::none;

						parseDirecive(selection);

						selection = L"";
						emptyLine = true;

					}
					else
					{
						directiveHasOpenBracket = true;
					}
				}
				if (tp != syntaxType::none)
				{
					printf("Error while script parsing! [Line: %i] Invalid directive: (%ws <-)", line, selection.c_str());
					error = true;
				}
			}
			if (src[line][idx] == '\n')
			{
				idx++;
			}
			else
				if (line < src.size() - 1)
				{
					line++;
					idx = 0;
				}
				else
				{
					// end of file

					// if there are any selection we should process it
					// then finilize parsing because no text left;
					//
					break;
				}
		}


	}

	if (!error)
		postProcessCommands();

	return !error;
}

ScriptDescriptor * ScriptCompiler::getScriptDescriptor()
{
	return p_s;
}

void ScriptCompiler::setFamilyId(std::wstring id)
{
	familyId = id;
}

void ScriptCompiler::postProcessCommands()
{

	for (int i(0); i < p_s->scriptLines.size(); i++)
	{
		auto ptr = p_s->scriptLines[i];

		if (gEnv->game.gameLogic.compilerCommandTemplates[ptr->prefix].postUpdateHandler != NULL)
			gEnv->game.gameLogic.compilerCommandTemplates[ptr->prefix].postUpdateHandler(&TemplateBuffer, ptr);
	
	}

}

bool ScriptCompiler::parseDirecive(std::wstring s)
{

	std::wstring f1;
	std::wstring f2;

	int pos1;
	int pos2;
	int pos3;

	pos1 = s.find('"', 0);
	pos2 = s.find('"', pos1 + 1);

	f1 = s.substr(0, pos1);
	f2 = s.substr(pos1+1, pos2-pos1-1);

	// deleting possible spaces
	pos3 = f1.find(' ', 0);
	f1 = f1.substr(0, pos3);

	if (f1 == L"#extLocal")
	{

		// creating ext
		localExtReference[f2] = createExternalTable();
		return true;

	}

	if (f1 == L"#ext" || f1 == L"#EXT")
	{
		if (familyId == L"")
		{
			// creating ext
			localExtReference[f2] = createExternalTable();
			return true;
		}
		else
		{
			if (gEnv->scripts.scriptGroups[familyId].extReference.find(f2) == gEnv->scripts.scriptGroups[familyId].extReference.end())
			{ // create new
				gEnv->scripts.scriptGroups[familyId].extReference[f2] = createExternalTable();
				localExtReference[f2] = gEnv->scripts.scriptGroups[familyId].extReference[f2];
			}
			else
			{ // use existing
				localExtReference[f2] = gEnv->scripts.scriptGroups[familyId].extReference[f2];
			}
		}
	}
	

	return false;
}

bool ScriptCompiler::parseCommand(std::wstring s)
{

	int pos = 0;
	bool quote = false;

	pos = s.find(' ', 0);
	if (pos > 0)
		s = s.substr(0, pos);

	pos = s.find('"', 0);
	if (pos > 0)
	{
		s = s.substr(0, pos);
		quote = true;
	}

	pos = s.find('\n', 0);
	if (pos > 0)
		s = s.substr(0, pos);

	std::for_each(s.begin(), s.end(), [](wchar_t & c) {
		c = ::toupper(c);
	});

	/*
	if (s == L"Put" || s == L"put")
	{
		// Put "value/const" to "value"
		this->tp = syntaxType::c_put;
		bracketCount = 0;
		parameterCount = 0;
		selection = L"";

		if (quote)
		{
			selection += '"';
			bracketCount = 1;
		}
		return true;
	}

	if (s == L"Text" || s == L"text")
	{
		// Put "value/const" to "value"
		this->tp = syntaxType::c_text;
		bracketCount = 0;
		parameterCount = 0;
		selection = L"";

		if (quote)
		{
			selection += '"';
			bracketCount = 1;
		}
		return true;
	}

	if (s == L"Terminate" || s == L"terminate")
	{
		parseTerminate(s);
		return true;
	}

	if (s == L"Choose" || s == L"choose")
	{
		this->tp = syntaxType::c_choose;
		bracketCount = 0;
		parameterCount = 0;
		selection = L"";
		status = 0;
		squareBracketCount = 0;
		if (quote)
		{
			selection += '"';
			bracketCount = 1;
		}
		return true;
	}

	if (s == L"Ariphmetic" || s == L"ariphmetic")
	{
		tp = syntaxType::c_ariphmetic;
		bracketCount = 0;
		parameterCount = 0;
		selection = L"";
		if (quote)
		{
			selection += '"';
			bracketCount = 1;
		}
		return true;
	}

	if (s == L"ChangeScriptEntryPoint" || s == L"changeScriptEntryPoint")
	{
		tp = syntaxType::c_changeScriptEntryPoint;
		bracketCount = 0;
		parameterCount = 0;
		selection = L"";
		if (quote)
		{
			selection += '"';
			bracketCount = 1;
		}
		return true;
	}

	if (s == L"SpendTime" || s == L"spendTime")
	{
		tp = syntaxType::c_spendTime;
		bracketCount = 0;
		parameterCount = 0;
		selection = L"";
		if (quote)
		{
			selection += '"';
			bracketCount = 1;
		}
		return true;
	}

	if (s == L"InitRewardBuffer" || L"initRewardBuffer")
	{
		//tp = syntaxType::c_initRewardBuffer
		parseInitRewardBuffer(s);
		return true;
	}
	*/

	for (auto t(gEnv->game.gameLogic.compilerCommandTemplates.begin()); t != gEnv->game.gameLogic.compilerCommandTemplates.end(); t++)
	{
		if (t->second.mainPrefix == s)
		{
			tp = syntaxType::t_command;
			selectedTemplateCommandName = t->first;
			targetTemplate = &t->second;
			
			if (quote)
				collectedBody = L"\"";
			else
				collectedBody = L"";

			templateBodyPos = 0;
			repeatedBlock = false;
			collectingArgument = false;
			
			if (targetTemplate->body.size() > 2)
				templateCollected = false;
			else
				templateCollected = true;
			
			return true;
		}

	}

	printf("Error! [Line: %i] Undefined command: (%ws)", line, s.c_str());
	error = true;

	return false;
}

bool ScriptCompiler::parseMarker(std::wstring s)
{
	std::wstring id;
	//s = s.substr(1, s.size() - 1);
	if (s.find(' ') != std::wstring::npos)
		id = s.substr(0, s.size() - 1);
	else
		id = s;

	if (s.find('\n') != std::wstring::npos)
		id = s.substr(0, s.size() - 1);

	// register marker
		
	markers[id] = commandsCount;




	return true;
}

ComparatorElement ScriptCompiler::parseCondition(std::wstring s)
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



	return ComparatorElement(true, s, L"",L"");
}

int ScriptCompiler::convertMarkerToLine(std::wstring marker)
{
	
	if (markers.find(marker) == markers.end())
	{
		// error
		printf("Error! [Line: %i] Undefined marker reference: (%ws)", line, marker.c_str());
		error = true;
	}

	return markers[marker];
}

std::wstring ScriptCompiler::convertExtReferences(std::wstring line)
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

		if (localExtReference.find(tableId) == localExtReference.end())
		{
			wprintf(L"Error! External table %s does not exist or not initialized", tableId.c_str());
			error = true;
			return std::wstring();
		}
		std::wstring newTableId = localExtReference[tableId];

		res += line.substr(lastIdx + tmp, idx - lastIdx - tmp + 5);

		res += newTableId;

		idx = v;
	}
	res += line.substr(lastIdx, line.size() - lastIdx);
	return res;
}

void ScriptCompiler::collectNewSymbol(wchar_t c)
{	
	while (targetTemplate->body[templateBodyPos] == ' ') templateBodyPos++;

	wchar_t br = targetTemplate->body[templateBodyPos];

	collectedBody += c;

	if (collectingArgument)
	{
		// collecting argument

		if (c == br)
		{
			// argument collected
			collectingArgument = false;

			if (templateBodyPos >= targetTemplate->body.size() - 1)
			{
				templateCollected = true;
				return;
			}

			templateBodyPos++;
		}
		else
		{
			if (repeatedBlock)
				TemplateBuffer.arg[argumentName + std::to_string(blockCount)] += c;
			else
				TemplateBuffer.arg[argumentName] += c;

		}

	}
	else
	{
		// collecting left bracket
		if (br == '%')
		{
			if (!repeatedBlock)
			{
				repeatedBlock = true;
				repeatedBlockLeft = templateBodyPos;
				templateBodyPos++;
				blockCount = 1;
				while (targetTemplate->body[templateBodyPos] == ' ' && templateBodyPos < targetTemplate->body.size() - 1) templateBodyPos++;
				
				if (templateBodyPos < targetTemplate->body.size() - 1)
					br = targetTemplate->body[templateBodyPos];
			}
			else
			{
				char v1 = targetTemplate->body[templateBodyPos + 1];
				char v2 = targetTemplate->body[templateBodyPos + 2];

				if (c == v1)
				{
					// repeat once more
					templateBodyPos = repeatedBlockLeft + 1;
					blockCount++;
					while (targetTemplate->body[templateBodyPos] == ' ' && templateBodyPos < targetTemplate->body.size() - 1) templateBodyPos++;

					if (templateBodyPos < targetTemplate->body.size() - 1)
						br = targetTemplate->body[templateBodyPos];
				}
				else
				{
					if (c == v2)
					{
						// exit repeat mode
						templateBodyPos+= 2;
						while (targetTemplate->body[templateBodyPos] == ' ' && templateBodyPos < targetTemplate->body.size() - 1) templateBodyPos++;
						
						if (templateBodyPos >= targetTemplate->body.size() - 1)
						{
							templateCollected = true;
							return;
						}

						if (templateBodyPos < targetTemplate->body.size() - 1)
							br = targetTemplate->body[templateBodyPos];

					}
				}
			}
		}


		if (c == br)
		{
			// left bracket collected
			argumentName = "";
			templateBodyPos++;

			if (templateBodyPos >= targetTemplate->body.size() - 1)
			{
				templateCollected = true;
				return;
			}
			while (
				(targetTemplate->body[templateBodyPos] >= 'a' && targetTemplate->body[templateBodyPos] <= 'z'
				|| targetTemplate->body[templateBodyPos] >= 'A' && targetTemplate->body[templateBodyPos] <= 'Z'
				|| targetTemplate->body[templateBodyPos] >= '0' && targetTemplate->body[templateBodyPos] <= '9'
				|| targetTemplate->body[templateBodyPos] == '$'
				|| targetTemplate->body[templateBodyPos] == '_') 
				&& templateBodyPos < targetTemplate->body.size() - 1)
			{
				argumentName += targetTemplate->body[templateBodyPos];
				templateBodyPos++;
			}
			collectingArgument = true;
		}	

	}

}

bool ScriptCompiler::checkTemplate()
{
	return templateCollected;
}

void ScriptCompiler::completeCommand()
{

	TemplateBuffer.commandId = commandsCount;
	BaseScript * ptr = targetTemplate->mainHandler(&TemplateBuffer);

	tp = syntaxType::none;
	selection = L"";
	emptyLine = true;
	
	commandsCount++;
	ptr->prefix = targetTemplate->mainPrefix;

	if (error)
	{
		delete ptr;
		return;
	}

	p_s->scriptLines.push_back(ptr);


	TemplateBuffer.arg.clear();
	

}


