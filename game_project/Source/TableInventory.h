#pragma once

#include "InventoryItem.h"

class TableInventory
{
public:
	tgui::ScrollablePanel::Ptr scrollablePanel;
	std::vector<InventoryItem*> item;

	TableInventory()
	{
		scrollablePanel = tgui::ScrollablePanel::create();
		gEnv->globalGui.add(scrollablePanel, "inventoryPanel");
		scrollablePanel->setRenderer(gEnv->globalTheme.getRenderer("ScrollablePanel"));
		scrollablePanel->setPosition("40%", "60%");
		scrollablePanel->setSize(500, 200);
		for (int i = 0; i < 20; i++)
		{

		}
	}
};