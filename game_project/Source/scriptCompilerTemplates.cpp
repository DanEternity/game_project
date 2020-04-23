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

BaseScript * scriptCompilerTemplates::mainHandler::EditItemConstructableProperties(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new EditItemConstructablePropertiesScript();
	p->src = convertExtReferences(buffer, buffer->arg["$src"]);
	p->key = convertExtReferences(buffer, buffer->arg["$key"]);
	p->quality = convertExtReferences(buffer, buffer->arg["$quality"]);
	p->modifier = convertExtReferences(buffer, buffer->arg["$modifier"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::IfDoJump(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new IfDoJumpScript();
	ComparatorElement c = parseCondition(convertExtReferences(buffer, buffer->arg["$A"]));
	p->condition = c;
	p->chache = buffer->arg["$B"];
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::CreateResourceItem(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new CreateResourceItemScript();
	p->dst = convertExtReferences(buffer, buffer->arg["$dst"]);
	p->count = convertExtReferences(buffer, buffer->arg["$count"]);
	p->maxCount = convertExtReferences(buffer, buffer->arg["$maxCount"]);
	p->name = convertExtReferences(buffer, buffer->arg["$name"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::CreateEquipmentItem(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new CreateEquipmentItemScript();
	p->dst = convertExtReferences(buffer, buffer->arg["$dst"]);
	p->name = convertExtReferences(buffer, buffer->arg["$name"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::ApplyEffectToEquipment(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new ApplyEffectScript();
	p->scriptType = scriptType::applyEffectToEquipment; // override type

	p->src = convertExtReferences(buffer, buffer->arg["$A"]);
	p->dst = convertExtReferences(buffer, buffer->arg["$B"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::EditEquipmentProperties(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new EditEquipmentPropertiesScript();
	p->src = convertExtReferences(buffer, buffer->arg["$src"]);
	p->name = convertExtReferences(buffer, buffer->arg["$name"]);
	p->slot = convertExtReferences(buffer, buffer->arg["$slot"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::CreatePool(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new CreatePoolScript();
	p->dst = convertExtReferences(buffer, buffer->arg["$dst"]);
	p->count = convertExtReferences(buffer, buffer->arg["$argCount"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::AddToPool(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new AddToPoolScript();
	p->dst = convertExtReferences(buffer, buffer->arg["$dst"]);
	p->weight = convertExtReferences(buffer, buffer->arg["$weight"]);
	int variants = 0;
	while (buffer->arg.find("$arg" + std::to_string(variants + 1)) != buffer->arg.end())
	{
		variants++;
		p->args.push_back(convertExtReferences(buffer, buffer->arg["$arg" + std::to_string(variants)]));
	}
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::GetFromPool(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new GetFromPoolScript();
	p->src = convertExtReferences(buffer, buffer->arg["$src"]);
	p->key = convertExtReferences(buffer, buffer->arg["$key"]);
	int variants = 0;
	while (buffer->arg.find("$arg" + std::to_string(variants + 1)) != buffer->arg.end())
	{
		variants++;
		p->args.push_back(convertExtReferences(buffer, buffer->arg["$arg" + std::to_string(variants)]));
	}
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::StringConcat(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new StringConcatScript();
	p->dest = convertExtReferences(buffer, buffer->arg["$dest"]);
	p->a = convertExtReferences(buffer, buffer->arg["$A"]);
	p->b = convertExtReferences(buffer, buffer->arg["$B"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::CreateExternalTable(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new CreateExternalTableScript();
	p->dest = convertExtReferences(buffer, buffer->arg["$dest"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::PutToExternalTable(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new PutToExternalTableScript();
	p->dst = convertExtReferences(buffer, buffer->arg["$dest"]);
	p->src = convertExtReferences(buffer, buffer->arg["$src"]);
	p->table = convertExtReferences(buffer, buffer->arg["$table"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::PutFromExternalTable(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new PutFromExternalTableScript();
	p->dst = convertExtReferences(buffer, buffer->arg["$dest"]);
	p->src = convertExtReferences(buffer, buffer->arg["$src"]);
	p->table = convertExtReferences(buffer, buffer->arg["$table"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::CreateMarker(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new CreateMarkerScript();
	p->dst = convertExtReferences(buffer, buffer->arg["$dest"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::AddMarkerToSector(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new AddMarkerToSectorScript();
	p->dst = convertExtReferences(buffer, buffer->arg["$dst"]);
	p->src = convertExtReferences(buffer, buffer->arg["$src"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::EditMarkerProperties(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new EditMarkerPropertiesScript();
	p->src = convertExtReferences(buffer, buffer->arg["$src"]);
	p->level = convertExtReferences(buffer, buffer->arg["$level"]);
	p->danger = convertExtReferences(buffer, buffer->arg["$danger"]);
	p->posX = convertExtReferences(buffer, buffer->arg["$posX"]);
	p->posY = convertExtReferences(buffer, buffer->arg["$posY"]);
	p->label = convertExtReferences(buffer, buffer->arg["$label"]);
	p->desc = convertExtReferences(buffer, buffer->arg["$desc"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::CallMarkerInitialization(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new CallCustomScript();
	p->categoryId = L"SectorTemplate";
	p->scriptId = convertExtReferences(buffer, buffer->arg["$path"]);
	int variants = 0;
	while (buffer->arg.find("$A" + std::to_string(variants + 1)) != buffer->arg.end())
	{
		variants++;
		p->arg.push_back(convertExtReferences(buffer, buffer->arg["$A" + std::to_string(variants)]));
	}
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::LinkScriptToMarker(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new LinkScriptToMarkerScript();
	p->marker = convertExtReferences(buffer, buffer->arg["$dst"]);
	p->script = convertExtReferences(buffer, buffer->arg["$src"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::SetMarkerPosition(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new SetMarkerPositionScript();
	p->src = convertExtReferences(buffer, buffer->arg["$src"]);
	p->x = convertExtReferences(buffer, buffer->arg["$X"]);
	p->y = convertExtReferences(buffer, buffer->arg["$Y"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::CreateDecoration(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new CreateDecorationScript();
	//p.body = "\"$dst\" \"$model\" \"$sX\" \"$sY\" \"$rotation\" \"$posX\" \"$posY\"";
	p->dest = convertExtReferences(buffer, buffer->arg["$dst"]);
	p->model = convertExtReferences(buffer, buffer->arg["$model"]);
	p->scaleX = convertExtReferences(buffer, buffer->arg["$sX"]);
	p->scaleY = convertExtReferences(buffer, buffer->arg["$sY"]);
	p->rotation = convertExtReferences(buffer, buffer->arg["$rotation"]);
	p->posX = convertExtReferences(buffer, buffer->arg["$posX"]);
	p->posY = convertExtReferences(buffer, buffer->arg["$posY"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::AddDecorationToSector(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new AddDecorationToSectorScript();
	p->dst = convertExtReferences(buffer, buffer->arg["$dst"]);
	p->src = convertExtReferences(buffer, buffer->arg["$src"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::AddBackgroundToSector(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new AddBackgroundToSectorScript();
	p->dst = convertExtReferences(buffer, buffer->arg["$dst"]);
	p->src = convertExtReferences(buffer, buffer->arg["$src"]);
	p->commandId = buffer->commandId;
	return p;
}

BaseScript * scriptCompilerTemplates::mainHandler::EquipModule(CompilerCommandTemplateDataBuffer * buffer)
{
	auto p = new EquipModuleScript();
	p->dst = convertExtReferences(buffer, buffer->arg["$dst"]);
	p->src = convertExtReferences(buffer, buffer->arg["$src"]);
	p->slotId = convertExtReferences(buffer, buffer->arg["$slot"]);
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

void scriptCompilerTemplates::afterUpdateHandler::IfDoJump(CompilerCommandTemplateDataBuffer * buffer, BaseScript * p1)
{
	auto p = static_cast<IfDoJumpScript*>(p1);
	p->lineId = convertMarkerToLine(buffer, p->chache);
}
