#include "scriptCompilerTemplates.h"

BaseScript * scriptCompilerTemplates::mainHandler::Put(CompilerCommandTemplateDataBuffer * buffer)
{
	PutScript * p = new PutScript();

	p->scr = convertExtReferences(buffer, buffer->arg["$A"]);
	p->dest = convertExtReferences(buffer, buffer->arg["$B"]);
	p->commandId = buffer->commandId;

	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::Text(CompilerCommandTemplateDataBuffer * buffer)
{
	TextScript * p = new TextScript();

	p->text = convertExtReferences(buffer, buffer->arg["$A"]);
	p->commandId = buffer->commandId;

	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::Terminate(CompilerCommandTemplateDataBuffer * buffer)
{
	TerminateScript * p = new TerminateScript();
	p->commandId;

	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::Jump(CompilerCommandTemplateDataBuffer * buffer)
{
	JumpScript * p = new JumpScript();
	p->chache = buffer->arg["$A"];
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::Choose(CompilerCommandTemplateDataBuffer * buffer)
{
	// TEMPLATE
	// "$T" %[$A]"$B"[$C]%,;

	ChooseScript * p = new ChooseScript();
	p->text = convertExtReferences(buffer, buffer->arg["$T"]);

	int variants = 0;
	while (buffer->arg.find("$A" + std::to_string(variants+1)) != buffer->arg.end())
	{
		variants++;

		ComparatorElement c = parseCondition(convertExtReferences(buffer, buffer->arg["$A" + std::to_string(variants)]));
		ChooseElement a = ChooseElement(convertExtReferences(buffer, buffer->arg["$B" + std::to_string(variants)]), 0, c);
		a.chache = buffer->arg["$C" + std::to_string(variants)];
		p->variants.push_back(a);
	}

	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::Ariphmetic(CompilerCommandTemplateDataBuffer * buffer)
{
	AriphmeticScript * p = new AriphmeticScript();

	// parsing ariphmetic (left) fragment

	std::wstring s = buffer->arg["$A"];

	p->dest = convertExtReferences(buffer, buffer->arg["$B"]);

	bool operatorFound = false;
	int size = 1;
	int pos = -1;

	if (!operatorFound && s.find(L"+", 0) != std::wstring::npos)
	{
		pos = s.find(L"+", 0);
		operatorFound = true;
	}

	if (!operatorFound && s.find(L"-", 0) != std::wstring::npos)
	{
		pos = s.find(L"-", 0);
		operatorFound = true;
	}

	if (!operatorFound && s.find(L"/", 0) != std::wstring::npos)
	{
		pos = s.find(L"/", 0);
		operatorFound = true;
	}

	if (!operatorFound && s.find(L"*", 0) != std::wstring::npos)
	{
		pos = s.find(L"*", 0);
		operatorFound = true;
	}

	if (!operatorFound && s.find(L"%", 0) != std::wstring::npos)
	{
		pos = s.find(L"%", 0);
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

		p->left = convertExtReferences(buffer, f1);
		p->operation = op;
		p->right = convertExtReferences(buffer, f2);

	}
	else
		buffer->error = true;

	p->commandId = buffer->commandId;

	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::ChangeScriptEntryPoint(CompilerCommandTemplateDataBuffer * buffer)
{
	ChangeScriptEntryPointScript * p = new ChangeScriptEntryPointScript();

	p->scriptId = convertExtReferences(buffer, buffer->arg["$A"]);
	p->chache = buffer->arg["$B"];
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::SpendTime(CompilerCommandTemplateDataBuffer * buffer)
{
	SpendTimeScript * p = new SpendTimeScript();
	p->amount = convertExtReferences(buffer, buffer->arg["$A"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::InitRewardBuffer(CompilerCommandTemplateDataBuffer * buffer)
{
	InitRewardBufferScript * p = new InitRewardBufferScript();
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::PutToPointer(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new PutToPointerScript();
	p->src = convertExtReferences(buffer, buffer->arg["$A"]);
	p->dst = convertExtReferences(buffer, buffer->arg["$B"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::AddToRewardBuffer(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new AddRewardToBufferScript();
	p->src = convertExtReferences(buffer, buffer->arg["$A"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::Call(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new CallScript();
	p->scriptId = convertExtReferences(buffer, buffer->arg["$PTR"]);
	int variants = 0;
	while (buffer->arg.find("$A" + std::to_string(variants + 1)) != buffer->arg.end())
	{
		variants++;
		p->arg.push_back(convertExtReferences(buffer, buffer->arg["$A" + std::to_string(variants)]));
	}
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::PutFromPointer(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new PutFromPointerScript();
	p->src = convertExtReferences(buffer, buffer->arg["$A"]);
	p->dst = convertExtReferences(buffer, buffer->arg["$B"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::Random(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new RandomScript();
	p->dst = convertExtReferences(buffer, buffer->arg["$A"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::CreateSysModule(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new CreateSysModuleScript();
	p->dst = convertExtReferences(buffer, buffer->arg["$A"]);
	p->name = convertExtReferences(buffer, buffer->arg["$B"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::CreateModStatEffect(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new CreateModStatEffectScript();
	p->dst = convertExtReferences(buffer, buffer->arg["$A"]);
	p->targetType = convertExtReferences(buffer, buffer->arg["$Target"]);
	p->statName = convertExtReferences(buffer, buffer->arg["$Stat"]);
	p->p_add = convertExtReferences(buffer, buffer->arg["$Add"]);
	p->p_mul = convertExtReferences(buffer, buffer->arg["$Mul"]);
	p->p_sub = convertExtReferences(buffer, buffer->arg["$Sub"]);
	p->p_negMul = convertExtReferences(buffer, buffer->arg["$NegMul"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::ApplyEffect(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new ApplyEffectScript();
	p->src = convertExtReferences(buffer, buffer->arg["$A"]);
	p->dst = convertExtReferences(buffer, buffer->arg["$B"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::ApplyEffectToSysModule(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new ApplyEffectScript();
	p->scriptType = scriptType::applyEffectToSysModule; // override type

	p->src = convertExtReferences(buffer, buffer->arg["$A"]); 
	p->dst = convertExtReferences(buffer, buffer->arg["$B"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::PutItemToPlayerInventory(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new PutItemToPlayerInventoryScript();
	p->src = convertExtReferences(buffer, buffer->arg["$A"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::EditItemProperties(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new EditItemPropertiesScript();
	p->src = convertExtReferences(buffer, buffer->arg["$src"]);
	p->level = convertExtReferences(buffer, buffer->arg["$level"]);
	p->rarity = convertExtReferences(buffer, buffer->arg["$rarity"]);
	p->itemId = convertExtReferences(buffer, buffer->arg["$itemId"]);
	p->itemClass = convertExtReferences(buffer, buffer->arg["$itemClass"]);
	p->itemName = convertExtReferences(buffer, buffer->arg["$itemName"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::EditModuleProperties(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new EditModulePropertiesScript();
	p->src = convertExtReferences(buffer, buffer->arg["$src"]);
	p->moduleType = convertExtReferences(buffer, buffer->arg["$moduleType"]);
	p->moduleSlot = convertExtReferences(buffer, buffer->arg["$moduleSlot"]);
	p->moduleSize = convertExtReferences(buffer, buffer->arg["$moduleSize"]);
	p->powerSupply = convertExtReferences(buffer, buffer->arg["$powerSupply"]);
	p->highPowerSupply = convertExtReferences(buffer, buffer->arg["$highPowerSupply"]);
	p->powerPriority = convertExtReferences(buffer, buffer->arg["$powerPriority"]);
	p->commandId = buffer->commandId;
	return p;
}

void scriptCompilerTemplates::afterUpdateHandler::Jump(CompilerCommandTemplateDataBuffer * buffer, BaseScript * p1)
{
	auto p = static_cast<JumpScript*> (p1);
	p->lineId = convertMarkerToLine(buffer, p->chache);
}

void scriptCompilerTemplates::afterUpdateHandler::Choose(CompilerCommandTemplateDataBuffer * buffer, BaseScript * p1)
{
	auto p = static_cast<ChooseScript*> (p1);
	for (int i(0); i < p->variants.size(); i++)
	{
		p->variants[i].jump = convertMarkerToLine(buffer, p->variants[i].chache);
	}
}

void scriptCompilerTemplates::afterUpdateHandler::ChangeScriptEntryPoint(CompilerCommandTemplateDataBuffer * buffer, BaseScript * p1)
{
	auto p = static_cast<ChangeScriptEntryPointScript*>(p1);
	p->lineId = convertMarkerToLine(buffer, p->chache);
}
