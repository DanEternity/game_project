#pragma once

#include "enviroment.h"
#include "tableInventory.h"
#include "personEquipmentUI.h"
#include "shipModulesUI.h"

namespace WidgetType
{
	enum widgetType
	{
		Button,
		Panel,
		ScrollablePanel,
		BitmapButton,
		ProgressBar,
		Label
	};
}

namespace TargetInventory
{
	enum targetInventory
	{
		tableInventory,
		gridPanel,
		shipPanel,
		personPanel
	};
}

/// <summary> Creates and return widget </summary>
/// <param name="type"> Type of returns widget </param>
/// <param name="render"> Type of render used to widget </param>
/// <param name="sizeX"> Width of widget </param>
/// <param name="sizeY"> Height of widget </param>
/// <param name="posX"> Position X of widget to his parent </param>
/// <param name="posY"> Position Y of widget to his parent </param>
/// <param name="enabled"> Is widget enabled after creation. True on default </param>
tgui::Widget::Ptr createWidget(WidgetType::widgetType type, std::string render, std::string sizeX, std::string sizeY, std::string posX, std::string posY, bool enabled = true);
tgui::Label::Ptr createWidgetLabel(std::string render, std::string posX, std::string posY, int textSize, std::wstring text, bool enabled = true);
void updateInventoryCell(int id);

void enableWidget(tgui::Widget::Ptr widget, bool enable);
void swapElements(TargetInventory::targetInventory target, int id);
void rebuildAll();

std::wstring createFloatString(float number);