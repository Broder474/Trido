#include "Core.h"

namespace Core
{
	Core::Core(): res(&logger)
	{
		glfwInit();
		glewExperimental = GL_TRUE;

		GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
		glfwGetMonitorContentScale(primary_monitor, &sysdata.monitor_scaleX, &sysdata.monitor_scaleY);
		settings.monitory_scaleX = sysdata.monitor_scaleX;
		settings.monitory_scaleY = sysdata.monitor_scaleY;

		sysdata.video_mode = glfwGetVideoMode(primary_monitor);
		settings.video_mode = sysdata.video_mode;

		gl_window = glfwCreateWindow(settings.video_mode->width, settings.video_mode->height, "Trido", NULL, NULL);
		glfwMakeContextCurrent(gl_window);
		glewInit();
		glfwSwapInterval(1);

		glfwSetWindowUserPointer(gl_window, this);
		glfwSetKeyCallback(gl_window, Core::KeyCallback);
		glfwSetMouseButtonCallback(gl_window, Core::MouseCallback);

		res.Load();
		windows.push_back(std::make_shared<MainWindow>(gl_window, &res));
		logger.print(Log_type::INFO, "Core run");
	}
	void Core::KeyCallback(GLFWwindow* gl_window, int key, int scancode, int action, int mod)
	{
		Core* core = static_cast<Core*>(glfwGetWindowUserPointer(gl_window));
		if (core) {
			// first input topper window
			std::vector<std::shared_ptr<Window>>& windows = core->windows;
 			for (auto& window : windows)
			{
				window->OnKeyClick(key, scancode, action, mod);
				if (window->LockInput == Window::ALLOW_ALL)
					continue;
				// stop accept input from lower windows
				else break;
			}

		}
	}
	void Core::MouseCallback(GLFWwindow* gl_window, int button, int action, int mod)
	{
		Core* core = static_cast<Core*>(glfwGetWindowUserPointer(gl_window));
		if (core) {
			// first input topper window
			std::vector<std::shared_ptr<Window>>& windows = core->windows;
			for (auto& window : windows)
			{
				window->OnMouseClick(button, action, mod);
				if (window->LockInput == Window::ALLOW_ALL || window->LockInput == Window::ALLOW_MOUSE)
					continue;
				// stop accept input from lower windows
				else break;
			}
		}
	}
	void Core::CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
	{

	}
	void Core::Loop()
	{
		while (!glfwWindowShouldClose(gl_window))
			Pipeline();
		Exit();
	}
	void Core::Pipeline()
	{
		Render();
		glfwSwapBuffers(gl_window);
		glfwPollEvents();
	}
	void Core::Render()
	{
		// first render lower window
		for (auto& window : windows)
			window->Render();
	}
	void Core::Exit()
	{
		glfwTerminate();
	}
}