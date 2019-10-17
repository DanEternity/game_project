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
			selection += src[line][idx];
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

		if (tp == syntaxType::c_ariphmetic)
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
						parseAriphmetic(selection);
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

		if (tp == syntaxType::c_choose)
		{
			selection += src[line][idx];

			switch (status)
			{
			case 0:
			{
				if (src[line][idx] == '"')
				{
					bracketCount++;
					if (bracketCount == 2)
					{
						bracketCount = 0;
						status = 1;
					}
				}
			}
				break;
			case 1:
			{
				if (src[line][idx] == ';')
				{
					if (parameterCount == 0)
					{
						printf("Error while script parsing! [Line: %i] ';' found, ',' expected: (%s <-). Choose should have at least 1 variant", line, selection.c_str());
						error = true;
					}
					else
					{
						parseChoose(selection);
					}
				}
				else
					if (src[line][idx] == ',')
					{
						status = 2;
						bracketCount = 0;
						squareBracketCount = 0;
					}
					else
						if (src[line][idx] != ' ')
						{
							printf("Error while script parsing! [Line: %i] Invalid character: (%s <-)", line, selection.c_str());
							error = true;
						}
			}
				break;
			case 2:
			{
				if (src[line][idx] == '[')
				{
						status = 3;
				}
			}
				break;
			case 3:
			{
				if (src[line][idx] == ']')
				{
					status = 4;
				}
				break;
			}
			case 4:
			{
				if (src[line][idx] == '"')
				{
					status = 5;
				}
				break;
			}
			case 5:
			{
				if (src[line][idx] == '"')
				{
					status = 6;
				}
				break;
			}
			case 6:
			{
				if (src[line][idx] == '[')
				{
					status = 7;
				}
				break;
			}
			case 7:
			{
				if (src[line][idx] == ']')
				{
					parameterCount += 1;
					status = 1;
				}
				break;
			}
			default:
				break;
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
			{
				tp = syntaxType::none;
				emptyLine = true;
				selection = "";
			}
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
				if (tp != syntaxType::none)
				{
					printf("Error while script parsing! [Line: %i] Invalid directive: (%s <-)", line, selection.c_str());
					error = true;
				}
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

	if (!error)
		postProcessCommands();

	return !error;
}

ScriptDescriptor * ScriptCompiler::getScriptDescriptor()
{
	return p_s;
}

void ScriptCompiler::setFamilyId(std::string id)
{
	familyId = id;
}

void ScriptCompiler::postProcessCommands()
{

	for (int i(0); i < p_s->scriptLines.size(); i++)
	{
		auto ptr = p_s->scriptLines[i];

		auto tp = ptr->scriptType;

		switch (tp)
		{
		case scriptType::null:
			break;
		case scriptType::text:
			break;
		case scriptType::put:
			break;
		case scriptType::choose:
			postUpdateChoose(ptr);
			break;
		case scriptType::terminate:
			break;
		case scriptType::jump:
			postUpdateJump(ptr);
			break;
		case scriptType::ariphmetic:
			break;
		case scriptType::ifDoJump:
			postUpdateIfDoJump(ptr);
			break;
		default:
			break;
		}
	}

}

bool ScriptCompiler::parseDirecive(std::string s)
{

	std::string f1;
	std::string f2;

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

	if (f1 == "#ext")
	{
		if (familyId == "")
		{
			// creating ext
			localExtReference[f2] = createExternalTable();
			return true;
		}
	}

	

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

	if (s == "Terminate" || s == "terminate")
	{
		parseTerminate(s);
		return true;
	}

	if (s == "Choose" || s == "choose")
	{
		this->tp = syntaxType::c_choose;
		bracketCount = 0;
		parameterCount = 0;
		selection = "";
		status = 0;
		squareBracketCount = 0;
		if (quote)
		{
			selection += '"';
			bracketCount = 1;
		}
		return true;
	}

	if (s == "Ariphmetic" || s == "ariphmetic")
	{
		tp = syntaxType::c_ariphmetic;
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
	std::string id;
	//s = s.substr(1, s.size() - 1);
	if (s.find(' ') != std::string::npos)
		id = s.substr(0, s.size() - 1);
	else
		id = s;

	// register marker
		
	markers[id] = commandsCount;




	return true;
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

	// increase lines counter
	ptr->commandId = commandsCount++;

	p_s->scriptLines.push_back(ptr);



	tp = syntaxType::none;
	selection = "";
	emptyLine = true;
	return true;
}

bool ScriptCompiler::parseTerminate(std::string s)
{
	TerminateScript * ptr = static_cast<TerminateScript*>(createScriptCommand(scriptType::terminate));


	// increase lines counter
	ptr->commandId = commandsCount++;

	p_s->scriptLines.push_back(ptr);
	tp = syntaxType::none;
	selection = "";
	emptyLine = true;


	return true;
}

bool ScriptCompiler::parseJump(std::string s)
{

	// jump command cant be determined immediantly because of not all marks parsed

	std::string f1;
	int posf1;

	posf1 = s.find('"', 0);
	s = s.substr(posf1 + 1, s.size() - posf1 - 1);

	posf1 = s.find('"', 1);

	f1 = s.substr(0, posf1);

	JumpScript * ptr = static_cast<JumpScript*>(createScriptCommand(scriptType::jump));
	ptr->chache = f1;

	// increase lines counter
	ptr->commandId = commandsCount++;

	p_s->scriptLines.push_back(ptr);
	tp = syntaxType::none;
	selection = "";
	emptyLine = true;
	return true;
}

bool ScriptCompiler::parseChoose(std::string s)
{

	// Choose "some text", [true]"variant 1"[1], [true]"variant 2"[2], [true]"variant 3"[3];

	std::string f1;
	int posf1;
	int posf2;
	posf1 = s.find('"', 0);
	posf2 = s.find('"', posf1 + 1);

	f1 = s.substr(posf1 + 1, posf2 - posf1 - 1);
	int p = posf2+1;

	ChooseScript * ptr = static_cast<ChooseScript*>(createScriptCommand(scriptType::choose));

	ptr->text = f1;

	while (1)
	{
		if (p > s.size()-1)
		{
			// error
			printf("Error! [Line: %i] ';' or ',' expected. (%s)", line, s.c_str());
			error = true;
			break;
		}

		if (s[p] == ',')
		{
			std::string a1;
			std::string a2;
			std::string a3;

			int posB1;
			int posB2;

			posB1 = s.find('[', p);
			posB2 = s.find(']', p);

			a1 = s.substr(posB1 + 1, posB2 - posB1 - 1);

			posB1 = s.find('"', posB2+1);
			posB2 = s.find('"', posB1+1);

			a2 = s.substr(posB1 + 1, posB2 - posB1 - 1);

			posB1 = s.find('[', posB2 + 1);
			posB2 = s.find(']', posB1 + 1);

			a3 = s.substr(posB1 + 1, posB2 - posB1 - 1);

			ComparatorElement comp = parseCondition(a1);

			ptr->variants.push_back(ChooseElement(a2, 0, comp));

			ptr->variants[ptr->variants.size() - 1].chache = a3;

			p = posB2 + 1;

		}
		else
		{
			break;
		}
	}

	// increase lines counter
	ptr->commandId = commandsCount++;

	tp = syntaxType::none;
	selection = "";
	emptyLine = true;

	if (error)
	{
		delete ptr;
		return false;
	}

	p_s->scriptLines.push_back(ptr);

	return true;
}

bool ScriptCompiler::parseAriphmetic(std::string s)
{

	// "value/const operator value/const" to "value"

	AriphmeticScript * ptr = static_cast<AriphmeticScript*>(createScriptCommand(scriptType::ariphmetic));

	std::string f1;
	std::string f2;
	int pos1;
	int pos2;
	int pos3;
	int pos4;

	pos1 = s.find('"', 0);
	pos2 = s.find('"', pos1 + 1);
	pos3 = s.find('"', pos2 + 1);
	pos4 = s.find('"', pos3 + 1);

	f2 = s.substr(pos3 + 1, pos4 - pos3 - 1);
	s = s.substr(pos1 + 1, pos2 - pos1 - 1);

	// parsing ariphmetic (left) fragment

	bool operatorFound = false;
	int size = 1;
	int pos = -1;

	if (!operatorFound && s.find("+", 0) != std::string::npos)
	{
		pos = s.find("+", 0);
		operatorFound = true;
	}

	if (!operatorFound && s.find("-", 0) != std::string::npos)
	{
		pos = s.find("-", 0);
		operatorFound = true;
	}

	if (!operatorFound && s.find("/", 0) != std::string::npos)
	{
		pos = s.find("/", 0);
		operatorFound = true;
	}

	if (!operatorFound && s.find("*", 0) != std::string::npos)
	{
		pos = s.find("*", 0);
		operatorFound = true;
	}

	if (operatorFound)
	{
		std::string f1;
		std::string op;
		std::string f2;

		int ps;

		f1 = s.substr(0, pos);

		// need to erase spaces
		ps = f1.find(' ');
		if (ps != std::string::npos)
			if (ps == 0)
				f1 = f1.substr(1, f1.size() - 1);

		ps = f1.find(' ');
		if (ps != std::string::npos)
			if (ps > 0)
				f1 = f1.substr(0, ps);


		op = s.substr(pos, size);

		f2 = s.substr(pos + size, s.size() - pos - size);


		ps = f2.find(' ');
		if (ps != std::string::npos)
			if (ps == 0)
				f2 = f2.substr(1, f2.size() - 1);

		ps = f2.find(' ');
		if (ps != std::string::npos)
			if (ps > 0)
				f2 = f2.substr(0, ps);

		ptr->left = f1;
		ptr->operation = op;
		ptr->right = f2;

	}
	else
		error = true;

	ptr->dest = f2;

	// increase lines counter
	ptr->commandId = commandsCount++;

	tp = syntaxType::none;
	selection = "";
	emptyLine = true;

	if (error)
	{
		delete ptr;
		return false;
	}

	p_s->scriptLines.push_back(ptr);

	return true;
}

ComparatorElement ScriptCompiler::parseCondition(std::string s)
{

	// "true"
	// "value/const operator value/const"

	bool operatorFound = false;
	int size = 2;
	int pos = -1;

	if (!operatorFound && s.find("==", 0) != std::string::npos)
	{
		pos = s.find("==", 0);
		operatorFound = true;
	}

	if (!operatorFound && s.find("!=", 0) != std::string::npos)
	{
		pos = s.find("!=", 0);
		operatorFound = true;
	}

	if (!operatorFound && s.find("<=", 0) != std::string::npos)
	{
		pos = s.find("<=", 0);
		operatorFound = true;
	}

	if (!operatorFound && s.find(">=", 0) != std::string::npos)
	{
		pos = s.find(">=", 0);
		operatorFound = true;
	}

	if (!operatorFound && s.find("<>", 0) != std::string::npos)
	{
		pos = s.find("<>", 0);
		operatorFound = true;
	}

	if (operatorFound)
	{

		std::string f1;
		std::string op;
		std::string f2;

		int ps;

		f1 = s.substr(0, pos);
		// need to erase spaces
		ps = f1.find(' ');
		if (ps != std::string::npos)
			if (ps == 0)
				f1 = f1.substr(1, f1.size() - 1);

		ps = f1.find(' ');
		if (ps != std::string::npos)
			if (ps > 0)
				f1 = f1.substr(0, ps);


		op = s.substr(pos, size);

		f2 = s.substr(pos + size, s.size() - pos - size);
		ps = f2.find(' ');
		if (ps != std::string::npos)
			if (ps == 0)
				f2 = f2.substr(1, f2.size() - 1);

		ps = f2.find(' ');
		if (ps != std::string::npos)
			if (ps > 0)
				f2 = f2.substr(0, ps);

		return ComparatorElement(false, f1, op, f2);
	}

	size = 1;

	if (!operatorFound && s.find("<", 0) != std::string::npos)
	{
		pos = s.find("<", 0);
		operatorFound = true;
	}

	if (!operatorFound && s.find(">", 0) != std::string::npos)
	{
		pos = s.find(">", 0);
		operatorFound = true;
	}

	if (operatorFound)
	{
		std::string f1;
		std::string op;
		std::string f2;

		int ps;

		f1 = s.substr(0, pos);

		// need to erase spaces
		ps = f1.find(' ');
		if (ps != std::string::npos)
			if (ps == 0)
				f1 = f1.substr(1, f1.size() - 1);

		ps = f1.find(' ');
		if (ps != std::string::npos)
			if (ps > 0)
				f1 = f1.substr(0, ps);


		op = s.substr(pos, size);

		f2 = s.substr(pos + size, s.size() - pos - size);
		ps = f2.find(' ');
		if (ps != std::string::npos)
			if (ps == 0)
				f2 = f2.substr(1, f2.size() - 1);

		ps = f2.find(' ');
		if (ps != std::string::npos)
			if (ps > 0)
				f2 = f2.substr(0, ps);

		return ComparatorElement(false, f1, op, f2);
	}

	// assume that selection allready boolean type
	// probably need a check



	return ComparatorElement(true, s, "","");
}

bool ScriptCompiler::postUpdateChoose(BaseScript * ptr)
{
	ChooseScript * p = static_cast<ChooseScript*>(ptr);

	for (int i(0); i < p->variants.size(); i++)
	{
		if (p->variants[i].chache[0] == '@')
		{
			p->variants[i].jump = convertMarkerToLine(p->variants[i].chache);
		}
		else
		{
			p->variants[i].jump = atoi(p->variants[i].chache.c_str());
		}
		p->variants[i].chache = "";
	}

	return true;
}

bool ScriptCompiler::postUpdateJump(BaseScript * ptr)
{

	JumpScript * p = static_cast<JumpScript*>(ptr);

	if (p->chache[0] == '@')
	{
		p->lineId = convertMarkerToLine(p->chache);
	}
	else
	{
		p->lineId = atoi(p->chache.c_str());
	}
	p->chache = "";
	return true;
}

bool ScriptCompiler::postUpdateIfDoJump(BaseScript * ptr)
{

	IfDoJumpScript * p = static_cast<IfDoJumpScript*>(ptr);
	
	if (p->chache[0] == '@')
	{
		p->lineId = convertMarkerToLine(p->chache);
	}
	else
	{
		p->lineId = atoi(p->chache.c_str());
	}
	p->chache = "";
	return true;
	
}

int ScriptCompiler::convertMarkerToLine(std::string marker)
{
	
	if (markers.find(marker) == markers.end())
	{
		// error
		printf("Error! [Line: %i] Undefined marker reference: (%s)", line, marker.c_str());
		error = true;
	}

	return markers[marker];
}
