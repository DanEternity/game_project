#include "TableInventory.h"

TableInventory::TableInventory()
{
	scrollablePanel = tgui::ScrollablePanel::create();
	gEnv->globalGui.add(scrollablePanel, "inventoryPanel");
	scrollablePanel->setRenderer(gEnv->globalTheme.getRenderer("Panel"));
	scrollablePanel->setPosition("10%", "80%");
	scrollablePanel->setSize(550, 100);
	for (int i = 0; i < 30; i++)
	{
		InventoryItem * invitem = new InventoryItem(i, this, "null");
	}
}

InventoryItem::InventoryItem(int position, TableInventory* inv, std::string content)
{
	positionX = position % cellsize;
	positionY = position / cellsize;
	panel = tgui::Button::create();
	inv->scrollablePanel->add(panel);
	panel->setSize(45, 40);
	panel->setPosition(5 + positionX * 50, 10 + positionY * 50);
	panel->setRenderer(gEnv->globalTheme.getRenderer("Button"));
}