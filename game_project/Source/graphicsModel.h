#pragma once

#include "baseObject.h"
#include <SFML\Graphics.hpp>
#include <string>

namespace modelStatus {

	enum ModelStatus
	{
		// model not initialized and cant be used or loaded
		notAssigned,
		// model initialized but not loaded
		notLoaded,
		// model loaded and ready to use
		loaded,
		// model used by object
		loadedAndUsed,
	};

} // namespace modelStatus
class ModelDescriptor : public BaseObject
{
public:
	
	// texture of model
	sf::Texture tex;
	// Descriptor status
	modelStatus::ModelStatus status = modelStatus::notAssigned;
	std::string pathToFile = "";
	std::string name = "";
	bool priorityLoad = false;

};