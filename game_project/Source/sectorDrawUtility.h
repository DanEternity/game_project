#pragma once

#include "mapObjectsData.h"
#include "enviroment.h"

void buildDecoration(MapDecoration * obj);

// WARNING: change only decor position
void updateDecoration(MapDecoration * obj);

void buildMarker(MapMarker * obj);

// change only position
void updateMarker(MapMarker * obj);

void buildSprite(sf::Sprite ** obj, std::wstring modelName);

void updateSprite(sf::Sprite * obj, sf::Vector2f pos);

void buildBackground(sf::Sprite ** obj, std::wstring modelName);