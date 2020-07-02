#include "itemUtils.h"

void giveIconToItem(Item * item)
{
	switch (item->itemType)
	{
	case itemType::module:
		switch (static_cast<Module*>(item)->slot)
		{
		case moduleSlot::ModuleSlotType::core:
			item->icon = &gEnv->modelDB[L"itemCore"]->tex;
			break;
		case moduleSlot::ModuleSlotType::engine:
			item->icon = &gEnv->modelDB[L"itemEngine"]->tex;
			break;
		case moduleSlot::ModuleSlotType::hyperdrive:
			item->icon = &gEnv->modelDB[L"itemHyperdrive"]->tex;
			break;
		case moduleSlot::ModuleSlotType::system:
			item->icon = &gEnv->modelDB[L"itemSystem"]->tex;
			break;
		default:
			item->icon = &gEnv->modelDB[L"itemDefault"]->tex;
		}
		break;
	default:
		item->icon = &gEnv->modelDB[L"itemDefault"]->tex;
		break;
	}
}
