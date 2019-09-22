#pragma once

#include "enviroment.h"

#pragma region updateMenuOverlay(double deltaTime)
/// <summary> Performs menu update. Should be called regularly to display menu.
/// Initiates other update mechanics </summary>
/// <param name="deltaTime"> deltaTime is time in seconds from previous frame </param>
void updateMenuOverlay(double deltaTime);
#pragma endregion