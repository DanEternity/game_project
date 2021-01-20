#include "UITooltipsCreate.h"


void createModuleTooltip(Module* m)
{
	gEnv->game.ui.tooltipDescription->removeAllWidgets();
	gEnv->game.ui.tooltipDescription->setSize(300, 250 + m->effects.size() * 30);
	gEnv->game.ui.tooltipDescription->setRenderer(gEnv->globalTheme.getRenderer("Panel2"));

	tgui::Panel::Ptr pan = createWidget(WidgetType::Panel, "Panel2", "300", "&.height", "0", "0")->cast<tgui::Panel>();
	gEnv->game.ui.tooltipDescription->add(pan);

	tgui::Button::Ptr button = createWidget(WidgetType::Button, "Button", "300", "30", "0", "0")->cast<tgui::Button>();
	button->setText(m->name);
	pan->add(button, "nameButtonTooltip");

	std::string render = "Label";
	pan->add(createWidgetLabel(render, "(&.width - width) / 2", std::to_string(30), 18, L"Module"));
	pan->add(createWidgetLabel(render, "(&.width - width) / 4 - 20", std::to_string(60), 18, L"Level: " + std::to_wstring(m->level)));
	pan->add(createWidgetLabel(render, "(&.width - width) / 4 * 3", std::to_string(60), 18, L"Rarity: " + std::to_wstring(m->rarity)));

	tgui::Label::Ptr label4 = tgui::Label::create();
	label4->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label4->setPosition("(&.width - width) / 2", 90);
	std::wstring text = L"";
	switch (m->slot)
	{
	case moduleSlot::core:
		text = L"Slot type: Core";
		break;
	case moduleSlot::hyperdrive:
		text = L"Slot type: Hyperdrive";
		break;
	case moduleSlot::engine:
		text = L"Slot type: Engine";
		break;
	case moduleSlot::system:
		text = L"Slot type: System";
		break;
	case moduleSlot::primaryWeapon:
		text = L"Slot type: Primary Weapon";
		break;
	case moduleSlot::secondaryWeapon:
		text = L"Slot type: Secondary Weapon";
		break;
	case moduleSlot::universal:
		text = L"Slot type: Universal";
		break;
	}
	label4->setTextSize(18);
	pan->add(createWidgetLabel(render, "(&.width - width) / 2", std::to_string(90), 18, text));


	tgui::Label::Ptr label5 = tgui::Label::create();
	label5->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label5->setPosition(10, 120);
	label5->setTextSize(18);
	pan->add(label5);

	std::wstring str = L"";
	bool first = true;


	str += L"Usage Power Supply: " + createFloatString(static_cast<Module*>(m)->powerSupply.total) + L"\n";
	str += L"Usage High Power Supply: " + createFloatString(static_cast<Module*>(m)->highPowerSupply.total) + L"\n\n";
	for (auto i : static_cast<Module*>(m)->effects)
	{
		if (i->effectGroup == effectGroups::statModifier)
		{
			StatModEffect* eff = static_cast<StatModEffect*>(i);
			str += createStringByStatName(eff->statName);

			if (static_cast<StatModEffect*>(i)->p_add != 0)
				str += L"+" + createFloatString(static_cast<StatModEffect*>(i)->p_add) + L" ";
			if (static_cast<StatModEffect*>(i)->p_mul != 0)
				str += L"+" + createFloatString(static_cast<StatModEffect*>(i)->p_mul * 100) + L"% ";
			if (static_cast<StatModEffect*>(i)->p_sub != 0)
				str += L"-" + createFloatString(static_cast<StatModEffect*>(i)->p_sub) + L" ";
			if (static_cast<StatModEffect*>(i)->p_negMul != 0)
				str += L"-" + createFloatString(static_cast<StatModEffect*>(i)->p_negMul * 100) + L"% ";

			if (!first) label5->setText(label5->getText() + str + L"\n");
			else label5->setText(str + L"\n");
			first = false;
			str = L"";
		}
	}
}

void createWeaponModuleTooltip(WeaponModule* w)
{
	gEnv->game.ui.tooltipDescription->removeAllWidgets();
	gEnv->game.ui.tooltipDescription->setSize(400, 550 + w->effects.size() * 30);
	gEnv->game.ui.tooltipDescription->setRenderer(gEnv->globalTheme.getRenderer("Panel2"));

	tgui::Panel::Ptr pan = createWidget(WidgetType::Panel, "Panel2", "400", "&.height", "0", "0")->cast<tgui::Panel>();
	gEnv->game.ui.tooltipDescription->add(pan);

	tgui::Button::Ptr button = createWidget(WidgetType::Button, "Button", "400", "30", "0", "0")->cast<tgui::Button>();
	button->setText(w->name);
	pan->add(button, "nameButtonTooltip");

	int y = 0;
	int yDif = 30;

	std::string render = "Label";
	pan->add(createWidgetLabel(render, "(&.width - width) / 2", std::to_string(y += yDif), 18, L"Weapon"));
	pan->add(createWidgetLabel(render, "(&.width - width) / 4 - 20", std::to_string(y += yDif), 18, L"Level: " + std::to_wstring(w->level)));
	pan->add(createWidgetLabel(render, "(&.width - width) / 4 * 3 + 20", std::to_string(y), 18, L"Rarity: " + std::to_wstring(w->rarity)));

	pan->add(createWidgetLabel(render, "8", std::to_string(y += yDif), 18, L"Power Supply: " + std::to_wstring(w->powerSupply.total)));
	pan->add(createWidgetLabel(render, "8", std::to_string(y += yDif), 18, L"High Power Supply: " + std::to_wstring(w->highPowerSupply.total)));

	std::wstring text = L"";
	/*switch (w->type)
	{

		WRITE WEAPON TYPE INTO text VAR

	} */
	pan->add(createWidgetLabel(render, "(&.width - width) / 2", std::to_string(y += yDif), 18, text));

	pan->add(createWidgetLabel(render, "8", std::to_string(y += yDif), 18, L"Damage: " + createFloatString(w->baseDamage.total * (int)w->projectilesAmount.total) + L" (" + createFloatString(w->baseDamage.total) + L" damage x " + std::to_wstring((int)w->projectilesAmount.total) + L" hits)"));

	switch (w->damageType)
	{
	case 0:
		pan->add(createWidgetLabel(render, "8", std::to_string(y += yDif), 18, L"Damage type: Null"));
		break;
	case 1:
		pan->add(createWidgetLabel(render, "8", std::to_string(y += yDif), 18, L"Damage type: Physical"));
		break;
	case 2:
		pan->add(createWidgetLabel(render, "8", std::to_string(y += yDif), 18, L"Damage type: Energy"));
		break;
	}

	pan->add(createWidgetLabel(render, "8", std::to_string(y += yDif), 18, L"Optimal distance: " + createFloatString(w->optimalDistance.total) + L" hex"));
	pan->add(createWidgetLabel(render, "8", std::to_string(y += yDif), 18, L"Accuracy: " + createFloatString(w->accuracy.total)));
	pan->add(createWidgetLabel(render, "8", std::to_string(y += yDif), 18, L"Over range: Damage/Hex -" + createFloatString(w->damagePenalty.total * 100) + L"%"));
	pan->add(createWidgetLabel(render, "108", std::to_string(y += yDif), 18, L"Accuracy/Hex -" + createFloatString(w->accuracyPenalty.total * 100) + L"%"));
	pan->add(createWidgetLabel(render, "8", std::to_string(y += yDif), 18, L"Hull crit chance: " + createFloatString(w->criticalChanceHull.total * 100) + L"%; Multiplier: " + createFloatString(w->criticalDamageHull.total * 100) + L"%"));
	pan->add(createWidgetLabel(render, "8", std::to_string(y += yDif), 18, L"Shield crit chance: " + createFloatString(w->criticalChanceShield.total * 100) + L"%; Multiplier: " + createFloatString(w->criticalDamageShield.total * 100) + L"%"));
	pan->add(createWidgetLabel(render, "8", std::to_string(y += yDif), 18, L"Hull penetration: " + createFloatString(w->resistanceIgnoreHullFlat.total) + L" + " + createFloatString(w->resistanceIgnoreHullPercent.total * 100) + L"% of target resist"));
	pan->add(createWidgetLabel(render, "8", std::to_string(y += yDif), 18, L"Shield penetration: " + createFloatString(w->resistanceIgnoreShieldFlat.total) + L" + " + createFloatString(w->resistanceIgnoreShieldPercent.total * 100) + L"% of target resist"));
	pan->add(createWidgetLabel(render, "8", std::to_string(y += yDif), 18, L"Weapon capacity: " + std::to_wstring((int)w->activationsLimit.total) + L"; Full cooldown: " + std::to_wstring((int)w->fullCooldown.total) + L" rounds"));
	pan->add(createWidgetLabel(render, "8", std::to_string(y += yDif), 18, L"Overheat limit: " + std::to_wstring((int)w->activationsPartial.total) + L"; Overheat cooldown: " + std::to_wstring((int)w->partialCooldown.total) + L" rounds"));

	tgui::ToolTip::setDistanceToMouse({ 15, -100 });
}

void createResourseTooltip(ItemResource* r)
{
	gEnv->game.ui.tooltipDescription->removeAllWidgets();
	gEnv->game.ui.tooltipDescription->setSize(300, 100);
	gEnv->game.ui.tooltipDescription->setRenderer(gEnv->globalTheme.getRenderer("Panel2"));

	tgui::Button::Ptr button = createWidget(WidgetType::Button, "Button", "300", "30", "0", "0")->cast<tgui::Button>();
	button->setText(r->name);
	gEnv->game.ui.tooltipDescription->add(button, "nameButtonTooltip");

	gEnv->game.ui.tooltipDescription->add(createWidgetLabel("Label", "(&.width - width) / 2", std::to_string(30), 18, L"Level " + std::to_wstring(r->level)));
	gEnv->game.ui.tooltipDescription->add(createWidgetLabel("Label", "(&.width - width) / 2", std::to_string(60), 18, L"Count: " + std::to_wstring(r->count) + L"/" + std::to_wstring(r->maxCount)), "resourceCount");
}

void createEquipmentTooltip(Equipment* e)
{
	gEnv->game.ui.tooltipDescription->removeAllWidgets();
	gEnv->game.ui.tooltipDescription->setSize(300, 250 + e->effects.size() * 30);
	gEnv->game.ui.tooltipDescription->setRenderer(gEnv->globalTheme.getRenderer("Panel2"));

	tgui::Panel::Ptr pan = createWidget(WidgetType::Panel, "Panel2", "300", "&.height", "0", "0")->cast<tgui::Panel>();
	gEnv->game.ui.tooltipDescription->add(pan);

	tgui::Button::Ptr button = createWidget(WidgetType::Button, "Button", "300", "30", "0", "0")->cast<tgui::Button>();
	button->setText(e->name);
	pan->add(button, "nameButtonTooltip");

	std::string render = "Label";
	pan->add(createWidgetLabel(render, "(&.width - width) / 2", std::to_string(30), 18, L"Equipment"));
	pan->add(createWidgetLabel(render, "(&.width - width) / 4 - 20", std::to_string(60), 18, L"Level: " + std::to_wstring(e->level)));
	pan->add(createWidgetLabel(render, "(&.width - width) / 4 * 3", std::to_string(60), 18, L"Rarity: " + std::to_wstring(e->rarity)));

	std::wstring text = L"";
	switch (e->equipmentSlotType)
	{
	case equipmentSlot::head:
		text = L"Slot type: Helmet";
		break;
	case equipmentSlot::arms:
		text = L"Slot type: Arms";
		break;
	case equipmentSlot::body:
		text = L"Slot type: Body";
		break;
	case equipmentSlot::legs:
		text = L"Slot type: Legs";
		break;
	case equipmentSlot::universal:
		text = L"Slot type: Universal";
	}
	pan->add(createWidgetLabel(render, "(&.width - width) / 2", std::to_string(90), 18, text));


	tgui::Label::Ptr label5 = tgui::Label::create();
	label5->setRenderer(gEnv->globalTheme.getRenderer("Label"));
	label5->setPosition(10, 120);
	label5->setTextSize(18);
	pan->add(label5);

	std::wstring str = L"";
	bool first = true;
	for (auto i : e->effects)
	{
		if (i->effectGroup == effectGroups::statModifier)
		{
			StatModEffect* eff = static_cast<StatModEffect*>(i);
			str += createStringByStatName(eff->statName);

			if (static_cast<StatModEffect*>(i)->p_add != 0)
				str += L"+" + createFloatString(static_cast<StatModEffect*>(i)->p_add) + L" ";
			if (static_cast<StatModEffect*>(i)->p_mul != 0)
				str += L"+" + createFloatString(static_cast<StatModEffect*>(i)->p_mul * 100) + L"% ";
			if (static_cast<StatModEffect*>(i)->p_sub != 0)
				str += L"-" + createFloatString(static_cast<StatModEffect*>(i)->p_sub) + L" ";
			if (static_cast<StatModEffect*>(i)->p_negMul != 0)
				str += L"-" + createFloatString(static_cast<StatModEffect*>(i)->p_negMul * 100) + L"% ";

			if (!first)
				label5->setText(label5->getText() + str + L"\n");
			else
				label5->setText(str + L"\n");
			first = false;
			str = L"";
		}
	}
}

void createSkillTooltip(PassiveSkill* p)
{
	gEnv->game.ui.tooltipDescription->removeAllWidgets();
	gEnv->game.ui.tooltipDescription->setSize(300, 250);
	gEnv->game.ui.tooltipDescription->setRenderer(gEnv->globalTheme.getRenderer("Panel2"));

	tgui::Panel::Ptr pan = createWidget(WidgetType::Panel, "Panel2", "300", "&.height", "0", "0")->cast<tgui::Panel>();
	gEnv->game.ui.tooltipDescription->add(pan);

	tgui::Button::Ptr button = createWidget(WidgetType::Button, "Button", "300", "30", "0", "0")->cast<tgui::Button>();
	switch (p->effect->targetRole)
	{
	case characterRole::noneRole:
		button->setText("No requirements on role");
		break;
	case characterRole::engineer:
		button->setText("Only on role Engineer");
		break;
	case characterRole::scientist:
		button->setText("Only on role Scientist");

	default:
		button->setText("Don't have definition");
	}
	pan->add(button, "nameButtonTooltip");

}