#include <functional>
#include "Utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>  
#include "Logger.h"

namespace State
{
	class StateManager
	{
		public:
			StateManager();
			glm::mat4 projection;
	};
}