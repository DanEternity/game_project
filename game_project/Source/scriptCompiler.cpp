#include "scriptCompiler.h"

bool ScriptCompiler::compileScriptText(std::vector<std::string> src)
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

	bool directiveHasOpenBracket;

	while (!error)
	{
		// zero sybmols in selection
		if (emptyLine)
		{
			// directive
			if (src[line][idx] == '#')
			{
				// directive
				emptyLine = false;
				//selection += src[line][idx];
				directiveHasOpenBracket = false;
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

					selection = "";
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
				printf("Error while script parsing! Expected [#directive ""value""] found (%s <-)\n", selection.c_str());
				printf("Hint: You probably forgot "" "". Directive comments should be inside brackets.\n");
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
					printf("Error while script parsing! [Line: %i] Invalid command: (%s <-)", line, selection.c_str());

			}
		}

		if (tp == syntaxType::marker)
		{
			if (src[line][idx] == ' ')
			{
				parseMarker(selection);
				emptyLine = true;
				selection = "";
				tp = syntaxType::none;
			}
		}

		if (tp == syntaxType::c_put)
		{
			selection += src[line][idx];
			if (src[line][idx] == '"')
			{
				bracketCount++;
				if (bracketCount == 2)
				{
					bracketCount = 0;
					parameterCount++;
					if (parameterCount == 2)
					{
						parsePut(selection);
					}
				}
			}
		}

		if (tp == syntaxType::c_text)
		{
			selection += src[line][idx];
			if (src[line][idx] == '"')
			{
				bracketCount++;
				if (bracketCount == 2)
				{
					bracketCount = 0;
					parameterCount++;
					if (parameterCount == 1)
					{
						parseText(selection);
					}
				}
			}
		}

		// move right
		if (idx < src[line].size() - 1)
			idx++;
		else // next line
		{
			// probalby need to add space
			// because some functions can be parsed wrong if
			// located in multiple lines
			idx = 0;

			if (tp == syntaxType::comment)
				tp = syntaxType::none;

			if (tp == syntaxType::marker)
			{
				parseMarker(selection);
				emptyLine = true;
				selection = "";
				tp = syntaxType::none;
			}

			if (tp == syntaxType::command)
			{
				bool code = parseCommand(selection);
			}

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
		}

	}

	return true;
}

ScriptDescriptor * ScriptCompiler::getScriptDescriptor()
{
	return p_s;
}

bool ScriptCompiler::parseDirecive(std::string s)
{
	return false;
}

bool ScriptCompiler::parseCommand(std::string s)
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
	if (s == "Put" || s == "put")
	{
		// Put "value/const" to "value"
		this->tp = syntaxType::c_put;
		bracketCount = 0;
		parameterCount = 0;
		selection = "";

		if (quote)
		{
			selection += '"';
			bracketCount = 1;
		}
		return true;
	}

	if (s == "Text" || s == "text")
	{
		// Put "value/const" to "value"
		this->tp = syntaxType::c_text;
		bracketCount = 0;
		parameterCount = 0;
		selection = "";

		if (quote)
		{
			selection += '"';
			bracketCount = 1;
		}
		return true;
	}

	printf("Error! [Line: %i] Undefined command: (%s)", line, s.c_str());
	error = true;

	return false;
}

bool ScriptCompiler::parseMarker(std::string s)
{
	return false;
}

bool ScriptCompiler::parsePut(std::string s)
{

	// "value/const" to "value"
	// it's possible to not use "to"
	// example: "value/const" "value"	

	std::string f1;
	std::string f2;
	int posf1;
	int posf12;
	int posf2;

	posf1 = s.find('"', 0);
	s = s.substr(posf1+1, s.size() - posf1 - 1);

	posf1 = s.find('"', 1);
	posf12 = s.find('"', posf1 + 1);
	posf2 = s.find('"', posf12 + 1);

	f1 = s.substr(0, posf1);
	f2 = s.substr(posf12 + 1, posf2 - posf12 - 1);

	PutScript * ptr = static_cast<PutScript*>(createScriptCommand(scriptType::put));

	ptr->scr = f1;
	ptr->dest = f2;
	ptr->commandId = commandsCount++;

	p_s->scriptLines.push_back(ptr);

	tp = syntaxType::none;
	selection = "";
	emptyLine = true;
	return true;
}

bool ScriptCompiler::parseText(std::string s)
{

	// Text "text" 

	std::string f1;
	int posf1;

	posf1 = s.find('"', 0);
	s = s.substr(posf1+1, s.size() - posf1 - 1);

	posf1 = s.find('"', 1);

	f1 = s.substr(0, posf1);

	TextScript * ptr = static_cast<TextScript*>(createScriptCommand(scriptType::text));

	ptr->text = f1;

	p_s->scriptLines.push_back(ptr);

	tp = syntaxType::none;
	selection = "";
	emptyLine = true;
	return true;
}
