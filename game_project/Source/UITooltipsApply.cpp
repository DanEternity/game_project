
#include "UITooltipsApply.h"

void applyStorageTooltip(int id)
{
	if (gEnv->game.player.inventory[id] != NULL)
	{
		switch (gEnv->game.player.inventory[id]->itemType)
		{
		case itemType::module:
			switch (static_cast<Module*>(gEnv->game.player.inventory[id])->moduleType)
			{
			case moduleType::system:
				createModuleTooltip(static_cast<Module*>(gEnv->game.player.inventory[id]));

				for (int i = 0; i < gEnv->game.player.ship->slots.size(); i++)
				{
					if (gEnv->game.player.ship->modules[i] != NULL)
					{
						if (gEnv->game.player.ship->modules[i]->slot == static_cast<Module*>(gEnv->game.player.inventory[id])->slot)
						{
							switch (gEnv->game.player.ship->modules[i]->moduleType)
							{
							case moduleType::system:
								createModuleTooltip(gEnv->game.player.ship->modules[i]);
								break;
							case moduleType::weapon:
								createWeaponModuleTooltip(static_cast<WeaponModule*>(gEnv->game.player.ship->modules[i]));
								break;
							}
							tgui::Widget::Ptr temp = gEnv->game.ui.tooltipDescription->cast<tgui::Widget>()->clone();
							temp->setVisible(true);

							createModuleTooltip(static_cast<Module*>(gEnv->game.player.inventory[id]));
							if (temp->getSize().y < gEnv->game.ui.tooltipDescription->getSize().y)
								gEnv->game.ui.tooltipDescription->setSize(600, gEnv->game.ui.tooltipDescription->getSize().y);
							else gEnv->game.ui.tooltipDescription->setSize(600, temp->getSize().y);

							gEnv->game.ui.tooltipDescription->add(temp, "comparePanel");
							gEnv->game.ui.tooltipDescription->get<tgui::Panel>("comparePanel")->setPosition(300, 0);
						}
					}
				}

				break;
			case moduleType::weapon:
				createWeaponModuleTooltip(static_cast<WeaponModule*>(gEnv->game.player.inventory[id]));

				for (int i = 0; i < gEnv->game.player.ship->slots.size(); i++)
				{
					if (gEnv->game.player.ship->modules[i] != NULL)
					{
						if (gEnv->game.player.ship->modules[i]->slot == static_cast<Module*>(gEnv->game.player.inventory[id])->slot)
						{
							switch (gEnv->game.player.ship->modules[i]->moduleType)
							{
							case moduleType::system:
								createModuleTooltip(gEnv->game.player.ship->modules[i]);
								break;
							case moduleType::weapon:
								createWeaponModuleTooltip(static_cast<WeaponModule*>(gEnv->game.player.ship->modules[i]));
								break;
							}
							tgui::Widget::Ptr temp = gEnv->game.ui.tooltipDescription->cast<tgui::Widget>()->clone();
							temp->setVisible(true);

							createWeaponModuleTooltip(static_cast<WeaponModule*>(gEnv->game.player.inventory[id]));
							if (temp->getSize().y < gEnv->game.ui.tooltipDescription->getSize().y)
								gEnv->game.ui.tooltipDescription->setSize(600, gEnv->game.ui.tooltipDescription->getSize().y);
							else gEnv->game.ui.tooltipDescription->setSize(600, temp->getSize().y);

							gEnv->game.ui.tooltipDescription->add(temp, "comparePanel");
							gEnv->game.ui.tooltipDescription->get<tgui::Panel>("comparePanel")->setPosition(300, 0);
						}
					}
				}

				break;
			}
			break;
		case itemType::equipment:
			createEquipmentTooltip(static_cast<Equipment*>(gEnv->game.player.inventory[id]));
			break;
		case itemType::resource:
			createResourseTooltip(static_cast<ItemResource*>(gEnv->game.player.inventory[id]));
			break;
		}
		gEnv->game.ui.tooltipDescription->setVisible(true);
	}
	else gEnv->game.ui.tooltipDescription->setVisible(false);
}

void applyGridTooltip(int id)
{
	if (id < gEnv->game.player.localInventory.size())
	{
		if (gEnv->game.player.inventory[gEnv->game.player.localInventory[id]] != NULL)
		{
			switch (gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]->itemType)
			{
			case itemType::module:
				switch (static_cast<Module*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]])->moduleType)
				{
				case moduleType::system:
					createModuleTooltip(static_cast<Module*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]));

					switch (gEnv->game.player.shipMenu)
					{
					case shipMenu::ship:
						for (int i = 0; i < gEnv->game.player.ship->slots.size(); i++)
						{
							if (gEnv->game.player.ship->modules[i] != NULL)
							{
								if (gEnv->game.player.ship->modules[i]->slot == static_cast<Module*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]])->slot)
								{
									switch (gEnv->game.player.ship->modules[i]->moduleType)
									{
									case moduleType::system:
										createModuleTooltip(gEnv->game.player.ship->modules[i]);
										break;
									case moduleType::weapon:
										createWeaponModuleTooltip(static_cast<WeaponModule*>(gEnv->game.player.ship->modules[i]));
										break;
									}
									tgui::Widget::Ptr temp = gEnv->game.ui.tooltipDescription->cast<tgui::Widget>()->clone();
									temp->setVisible(true);

									createModuleTooltip(static_cast<Module*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]));
									if (temp->getSize().y < gEnv->game.ui.tooltipDescription->getSize().y)
										gEnv->game.ui.tooltipDescription->setSize(600, gEnv->game.ui.tooltipDescription->getSize().y);
									else gEnv->game.ui.tooltipDescription->setSize(600, temp->getSize().y);

									gEnv->game.ui.tooltipDescription->add(temp, "comparePanel");
									gEnv->game.ui.tooltipDescription->get<tgui::Panel>("comparePanel")->setPosition(300, 0);
								}
							}
						}
						break;
					case shipMenu::hangar:
						for (int i = 0; i < gEnv->game.player.fighterPlanes[gEnv->game.ui.activeOpenFighterWindow]->modules.size(); i++)
						{
							if (gEnv->game.player.fighterPlanes[gEnv->game.ui.activeOpenFighterWindow]->modules[i] != NULL)
							{
								if (gEnv->game.player.fighterPlanes[gEnv->game.ui.activeOpenFighterWindow]->modules[i]->slot == static_cast<Module*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]])->slot)
								{
									switch (gEnv->game.player.fighterPlanes[gEnv->game.ui.activeOpenFighterWindow]->modules[i]->moduleType)
									{
									case moduleType::system:
										createModuleTooltip(gEnv->game.player.fighterPlanes[gEnv->game.ui.activeOpenFighterWindow]->modules[i]);
										break;
									case moduleType::weapon:
										createWeaponModuleTooltip(static_cast<WeaponModule*>(gEnv->game.player.fighterPlanes[gEnv->game.ui.activeOpenFighterWindow]->modules[i]));
										break;
									}
									tgui::Widget::Ptr temp = gEnv->game.ui.tooltipDescription->cast<tgui::Widget>()->clone();
									temp->setVisible(true);

									createModuleTooltip(static_cast<Module*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]));
									if (temp->getSize().y < gEnv->game.ui.tooltipDescription->getSize().y)
										gEnv->game.ui.tooltipDescription->setSize(600, gEnv->game.ui.tooltipDescription->getSize().y);
									else gEnv->game.ui.tooltipDescription->setSize(600, temp->getSize().y);

									gEnv->game.ui.tooltipDescription->add(temp, "comparePanel");
									gEnv->game.ui.tooltipDescription->get<tgui::Panel>("comparePanel")->setPosition(300, 0);
								}
							}
						}
						break;
					}
					break;
				case moduleType::weapon:
					createWeaponModuleTooltip(static_cast<WeaponModule*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]));
					switch (gEnv->game.player.shipMenu)
					{
					case shipMenu::ship:
						for (int i = 0; i < gEnv->game.player.ship->slots.size(); i++)
						{
							if (gEnv->game.player.ship->modules[i] != NULL)
							{
								if (gEnv->game.player.ship->modules[i]->slot == static_cast<Module*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]])->slot)
								{
									switch (gEnv->game.player.ship->modules[i]->moduleType)
									{
									case moduleType::system:
										createModuleTooltip(gEnv->game.player.ship->modules[i]);
										break;
									case moduleType::weapon:
										createWeaponModuleTooltip(static_cast<WeaponModule*>(gEnv->game.player.ship->modules[i]));
										break;
									}
									tgui::Widget::Ptr temp = gEnv->game.ui.tooltipDescription->cast<tgui::Widget>()->clone();
									temp->setVisible(true);

									createWeaponModuleTooltip(static_cast<WeaponModule*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]));
									if (temp->getSize().y < gEnv->game.ui.tooltipDescription->getSize().y)
										gEnv->game.ui.tooltipDescription->setSize(800, gEnv->game.ui.tooltipDescription->getSize().y);
									else gEnv->game.ui.tooltipDescription->setSize(800, temp->getSize().y);

									gEnv->game.ui.tooltipDescription->add(temp, "comparePanel");
									gEnv->game.ui.tooltipDescription->get<tgui::Panel>("comparePanel")->setPosition(400, 0);
								}
							}
						}
						break;
					case shipMenu::hangar:
						for (int i = 0; i < gEnv->game.player.fighterPlanes[gEnv->game.ui.activeOpenFighterWindow]->modules.size(); i++)
						{
							if (gEnv->game.player.fighterPlanes[gEnv->game.ui.activeOpenFighterWindow]->modules[i] != NULL)
							{
								if (gEnv->game.player.fighterPlanes[gEnv->game.ui.activeOpenFighterWindow]->modules[i]->slot == static_cast<Module*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]])->slot)
								{
									switch (gEnv->game.player.fighterPlanes[gEnv->game.ui.activeOpenFighterWindow]->modules[i]->moduleType)
									{
									case moduleType::system:
										createModuleTooltip(gEnv->game.player.fighterPlanes[gEnv->game.ui.activeOpenFighterWindow]->modules[i]);
										break;
									case moduleType::weapon:
										createWeaponModuleTooltip(static_cast<WeaponModule*>(gEnv->game.player.fighterPlanes[gEnv->game.ui.activeOpenFighterWindow]->modules[i]));
										break;
									}
									tgui::Widget::Ptr temp = gEnv->game.ui.tooltipDescription->cast<tgui::Widget>()->clone();
									temp->setVisible(true);

									createWeaponModuleTooltip(static_cast<WeaponModule*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]));
									if (temp->getSize().y < gEnv->game.ui.tooltipDescription->getSize().y)
										gEnv->game.ui.tooltipDescription->setSize(800, gEnv->game.ui.tooltipDescription->getSize().y);
									else gEnv->game.ui.tooltipDescription->setSize(800, temp->getSize().y);

									gEnv->game.ui.tooltipDescription->add(temp, "comparePanel");
									gEnv->game.ui.tooltipDescription->get<tgui::Panel>("comparePanel")->setPosition(400, 0);
								}
							}
						}
						break;
					}
					break;

				}
				break;
			case itemType::equipment:
				createEquipmentTooltip(static_cast<Equipment*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]));
				for (int i = 0; i < gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment.size(); i++)
				{
					if (gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[i] != NULL)
					{
						if (static_cast<Equipment*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]])->equipmentSlotType == gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[i]->equipmentSlotType)
						{
							createEquipmentTooltip(gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[i]);

							tgui::Widget::Ptr temp = gEnv->game.ui.tooltipDescription->cast<tgui::Widget>()->clone();
							temp->setVisible(true);

							createEquipmentTooltip(static_cast<Equipment*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]));
							if (temp->getSize().y < gEnv->game.ui.tooltipDescription->getSize().y)
								gEnv->game.ui.tooltipDescription->setSize(600, gEnv->game.ui.tooltipDescription->getSize().y);
							else gEnv->game.ui.tooltipDescription->setSize(600, temp->getSize().y);

							gEnv->game.ui.tooltipDescription->add(temp, "comparePanel");
							gEnv->game.ui.tooltipDescription->get<tgui::Panel>("comparePanel")->setPosition(300, 0);
						}
					}
				}
				break;
			case itemType::resource:
				createResourseTooltip(static_cast<ItemResource*>(gEnv->game.player.inventory[gEnv->game.player.localInventory[id]]));
				break;
			}
			gEnv->game.ui.tooltipDescription->setVisible(true);
		}
		else gEnv->game.ui.tooltipDescription->setVisible(false);
	}
	else gEnv->game.ui.tooltipDescription->setVisible(false);
}

void applyEquipmentTooltipPersonUI(int id)
{
	if (gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id] != NULL)
	{
		createEquipmentTooltip(gEnv->game.player.crew.characters[gEnv->game.ui.activeOpenPersonWindow]->equipment[id]);
		gEnv->game.ui.tooltipDescription->setVisible(true);
	}
	else gEnv->game.ui.tooltipDescription->setVisible(false);
}

void applyModuleTooltipShipUI(int id)
{
	if (gEnv->game.player.ship->modules[id] != NULL)
	{
		switch (gEnv->game.player.ship->modules[id]->moduleType)
		{
		case moduleType::system:
			createModuleTooltip(static_cast<Module*>(gEnv->game.player.ship->modules[id]));
			break;
		case moduleType::weapon:
			createWeaponModuleTooltip(static_cast<WeaponModule*>(gEnv->game.player.ship->modules[id]));
			break;
		}
		gEnv->game.ui.tooltipDescription->setVisible(true);
	}
	else gEnv->game.ui.tooltipDescription->setVisible(false);
}

void applySkillTooltipUI(PassiveSkill* p)
{
	if (p != NULL)
	{
		createSkillTooltip(p);
		gEnv->game.ui.tooltipDescription->setVisible(true);
	}
	else gEnv->game.ui.tooltipDescription->setVisible(false);
}

void applyFighterTooltipUI(int fighterId, int moduleId)
{
	if (gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId] != NULL)
	{
		switch (gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId]->moduleType)
		{
		case moduleType::system:
			createModuleTooltip(static_cast<Module*>(gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId]));
			break;
		case moduleType::weapon:
			createWeaponModuleTooltip(static_cast<WeaponModule*>(gEnv->game.player.fighterPlanes[fighterId]->modules[moduleId]));
			break;
		}
		gEnv->game.ui.tooltipDescription->setVisible(true);
	}
	else gEnv->game.ui.tooltipDescription->setVisible(false);
}
