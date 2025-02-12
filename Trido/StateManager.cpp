#include "StateManager.h"

namespace State
{
	StateManager::StateManager()
	{
		projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -0.1f, 0.1f);
	}
}