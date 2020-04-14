#include "sectorDrawUtility.h"

void buildDecoration(MapDecoration * obj)
{

	if (gEnv->modelDB.find(obj->model) == gEnv->modelDB.end())
	{
		// error 
		wprintf(L"Error! model <%s> not found \n", obj->model.c_str());
		return;
	}

	auto tex = gEnv->modelDB[obj->model];

	if (tex->status != modelStatus::loaded && tex->status != modelStatus::loadedAndUsed)
	{
		wprintf(L"Error! model <%s> not loaded \n", obj->model.c_str());
		return;
	}

	if (obj->sprite != NULL)
	{
		delete obj->sprite;
		obj->sprite = NULL;
	}

	obj->sprite = new sf::Sprite(tex->tex);
	auto size = obj->sprite->getTexture()->getSize();

	obj->sprite->setOrigin({float(size.x) / 2, float(size.y) / 2});

	obj->sprite->setRotation(obj->rotation);
	obj->sprite->setScale(obj->scale / gEnv->game.adventureData.settingMapScale);

	auto p = obj->pos;

	p.x /= gEnv->game.adventureData.settingMapScale;
	p.y /= gEnv->game.adventureData.settingMapScale;
	p.x -= (gEnv->game.player.cameraPosition.x / gEnv->game.adventureData.settingMapScale);
	p.y -= (gEnv->game.player.cameraPosition.y / gEnv->game.adventureData.settingMapScale);

	obj->sprite->setPosition(p);

}

void updateDecoration(MapDecoration * obj)
{

	auto p = obj->pos;

	p.x /= gEnv->game.adventureData.settingMapScale;
	p.y /= gEnv->game.adventureData.settingMapScale;
	p.x -= (gEnv->game.player.cameraPosition.x / gEnv->game.adventureData.settingMapScale);
	p.y -= (gEnv->game.player.cameraPosition.y / gEnv->game.adventureData.settingMapScale);

	obj->sprite->setPosition(p);

}

void buildMarker(MapMarker * obj)
{


	if (gEnv->modelDB.find(L"markerBase") == gEnv->modelDB.end())
	{
		// error 
		wprintf(L"Error! model MarkerBase not found \n");
		return;
	}

	auto tex = gEnv->modelDB[L"markerBase"];

	if (tex->status != modelStatus::loaded && tex->status != modelStatus::loadedAndUsed)
	{
		wprintf(L"Error! model MarkerBase not found \n");
		return;
	}

	if (obj->sprite != NULL)
	{
		delete obj->sprite;
		obj->sprite = NULL;
	}

	obj->sprite = new sf::Sprite(tex->tex);
	auto size = obj->sprite->getTexture()->getSize();

	obj->sprite->setOrigin({ float(size.x) / 2, float(size.y) / 2 });

	//obj->sprite->setRotation(obj->rotation);

	sf::Vector2f objScale(1, 1);

	obj->sprite->setScale(objScale / gEnv->game.adventureData.settingMapScale);

	auto p = obj->pos;

	p.x /= gEnv->game.adventureData.settingMapScale;
	p.y /= gEnv->game.adventureData.settingMapScale;
	p.x -= (gEnv->game.player.cameraPosition.x / gEnv->game.adventureData.settingMapScale);
	p.y -= (gEnv->game.player.cameraPosition.y / gEnv->game.adventureData.settingMapScale);

	obj->sprite->setPosition(p);

}

void updateMarker(MapMarker * obj)
{

	auto p = obj->pos;

	p.x /= gEnv->game.adventureData.settingMapScale;
	p.y /= gEnv->game.adventureData.settingMapScale;
	p.x -= (gEnv->game.player.cameraPosition.x / gEnv->game.adventureData.settingMapScale);
	p.y -= (gEnv->game.player.cameraPosition.y / gEnv->game.adventureData.settingMapScale);

	obj->sprite->setPosition(p);

}

void buildSprite(sf::Sprite ** obj, std::wstring modelName)
{

	if (gEnv->modelDB.find(modelName) == gEnv->modelDB.end())
	{
		// error 
		wprintf(L"Error! model %ws not found \n", modelName.c_str());
		return;
	}

	auto tex = gEnv->modelDB[modelName];

	if (tex->status != modelStatus::loaded && tex->status != modelStatus::loadedAndUsed)
	{
		wprintf(L"Error! model %ws not found \n", modelName.c_str());
		return;
	}

	if ((*obj) != NULL)
	{
		delete (*obj);
		(*obj) = NULL;
	}

	(*obj) = new sf::Sprite(tex->tex);
	auto obj2 = (*obj);

	auto size = obj2->getTexture()->getSize();

	obj2->setOrigin({ float(size.x) / 2, float(size.y) / 2 });

	//obj2->setRotation(obj2->rotation);

	sf::Vector2f objScale(1, 1);

	obj2->setScale(objScale / gEnv->game.adventureData.settingMapScale);

	auto p = sf::Vector2f(0,0);

	p.x /= gEnv->game.adventureData.settingMapScale;
	p.y /= gEnv->game.adventureData.settingMapScale;
	p.x -= (gEnv->game.player.cameraPosition.x / gEnv->game.adventureData.settingMapScale);
	p.y -= (gEnv->game.player.cameraPosition.y / gEnv->game.adventureData.settingMapScale);

	obj2->setPosition(p);

}

void updateSprite(sf::Sprite * obj, sf::Vector2f pos)
{
	auto p = pos;

	p.x /= gEnv->game.adventureData.settingMapScale;
	p.y /= gEnv->game.adventureData.settingMapScale;
	p.x -= (gEnv->game.player.cameraPosition.x / gEnv->game.adventureData.settingMapScale);
	p.y -= (gEnv->game.player.cameraPosition.y / gEnv->game.adventureData.settingMapScale);

	obj->setPosition(p);
}

void buildBackground(sf::Sprite ** obj, std::wstring modelName)
{
	if (gEnv->modelDB.find(modelName) == gEnv->modelDB.end())
	{
		// error 
		wprintf(L"Error! model %ws not found \n", modelName.c_str());
		return;
	}

	auto tex = gEnv->modelDB[modelName];

	if (tex->status != modelStatus::loaded && tex->status != modelStatus::loadedAndUsed)
	{
		wprintf(L"Error! model %ws not found \n", modelName.c_str());
		return;
	}

	if ((*obj) != NULL)
	{
		delete (*obj);
		(*obj) = NULL;
	}

	(*obj) = new sf::Sprite(tex->tex);
	auto obj2 = (*obj);

	obj2->setPosition(0, 0);

}
