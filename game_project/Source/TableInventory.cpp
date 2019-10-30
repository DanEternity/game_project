#include "TableInventory.h"

void TableInventory::addItem(std::string obj)
{
	int findNext;
	for (findNext = 0; findNext < item.size(); findNext++)
	{
		if (*item[findNext]->content == "")
		{
			break;
		}
	}
	*item[findNext]->content = obj;
	tgui::Button::Ptr wid;
	wid = item[findNext]->panelButton;
	wid->setText(obj);
}

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
		item.push_back(invitem);
	}
}

InventoryItem::InventoryItem(int position, TableInventory* inv, std::string content)
{
	positionX = position % cellsize;
	positionY = position / cellsize;
	number = position;
	panelButton = tgui::Button::create();
	inv->scrollablePanel->add(panelButton);
	panelButton->setSize(45, 40);
	panelButton->setPosition(5 + positionX * 50, 10 + positionY * 50);
	panelButton->setRenderer(gEnv->globalTheme.getRenderer("Button"));
	panelButton->setText("");
	panelButton->connect("MouseReleased", InventoryItemClicked, &(*inv), &(*this));
	this->content = new std::string(panelButton->getText());
}

void InventoryItemClicked(TableInventory * inv, InventoryItem *item, tgui::Widget::Ptr widget, const std::string & signalName)
{
	if (!inv->itemTransfering)
	{
		if (*item->content != "")
		{
			inv->itemWhichTransfer = *item->content;
			widget->cast<tgui::Button>()->setText("");
			*item->content = "";
			inv->itemTransfering = true;
		}
	}
	else
	{
		if (*item->content == "")
		{
			widget->cast<tgui::Button>()->setText(inv->itemWhichTransfer);
			*item->content = inv->itemWhichTransfer;
			inv->itemWhichTransfer = "";
			inv->itemTransfering = false;
		}
	}
}
