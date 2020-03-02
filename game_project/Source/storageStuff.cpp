#include "storageStuff.h"
#include <string>

void changeFilterState(tgui::Widget::Ptr widget, const std::string & signalName)
{
	switch (widget->cast<tgui::ComboBox>()->getSelectedItemIndex())
	{
	case 1:
		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setEnabled(true);
		gEnv->game.adventureGUI.get<tgui::Panel>("inventoryPanel")->setVisible(true);
		break;
	case 2:

		break;
	case 3:
		break;
	}
}