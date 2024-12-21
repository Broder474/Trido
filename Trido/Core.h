#pragma once

#include "UI.h"
#include <string>
#include <GL/freeglut.h>
#include <rapidxml.hpp>
#include <lua.hpp>
#include <functional>
#include <vector>

#include "IO.h"
#include "StateManager.h"
#include "EventManager.h"
#include "CmdManager.h"

using namespace IO;
using namespace StateManager;
using namespace EventManager;
using namespace CmdManager;
using namespace UI;

namespace Core
{

	class Settings
	{
	public:
		float monitory_scaleX = 0;
		float monitory_scaleY = 0;
		const GLFWvidmode* video_mode;
	};
	class System
	{
	public:
		float monitor_scaleX = 0;
		float monitor_scaleY = 0;
		const GLFWvidmode* video_mode;
	};
	class Core
	{
	public:
		Core();
		void Loop();
		void Pipeline();
		void Render();
		void Exit();
		std::string getVersion() { return version; }

		Logger logger;
		GLFWwindow* gl_window = nullptr;
		Settings settings;
		Resources res;
		System sysdata;
		std::vector<std::shared_ptr<Window>> windows;
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod);
		static void MouseCallback(GLFWwindow* window, int button, int action, int mod);
		static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
		
	private:
		std::string version = "0.0.1pa";
	};
}