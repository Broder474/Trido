#pragma once

#include "UI.h"
#include <string>
#include <GL/freeglut.h>
#include <rapidxml.hpp>
#include <lua.hpp>
#include <functional>
#include <vector>

#include "IO.h"
#include "EventManager.h"
#include "CmdManager.h"

using namespace Input_Output;
using namespace State;
using namespace EventManager;
using namespace CmdManager;
using namespace UI;

namespace Core
{
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
		Resources res;
		IO io;
		std::vector<std::shared_ptr<Window>> windows;
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod);
		static void MouseCallback(GLFWwindow* window, int button, int action, int mod);
		static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
		static void WindowSizeCallback(GLFWwindow* window, int width, int height);
	private:
		std::string version = "0.0.1pa";
	};
}