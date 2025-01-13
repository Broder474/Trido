#include "Core.h"

namespace Core
{
	Core::Core(): res(logger, &io)
	{
		glfwInit();
		glewExperimental = GL_TRUE;

		GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
		glfwGetMonitorContentScale(primary_monitor, &settings.monitory_scaleX, &settings.monitory_scaleY);

		settings.video_mode = glfwGetVideoMode(primary_monitor);

		gl_window = glfwCreateWindow(settings.video_mode->width, settings.video_mode->height, "Trido", NULL, NULL);
		io.init(gl_window);
		glfwMakeContextCurrent(gl_window);
		//glfwSetWindowMonitor(gl_window, primary_monitor, 0, 0, settings.video_mode->width, settings.video_mode->height, settings.video_mode->refreshRate);
		glewInit();
		glfwSwapInterval(1);

		glfwSetWindowUserPointer(gl_window, this);
		glfwSetKeyCallback(gl_window, Core::KeyCallback);
		glfwSetMouseButtonCallback(gl_window, Core::MouseCallback);
		glfwSetCursorPosCallback(gl_window, Core::CursorPosCallback);

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
				window->MouseEvent(button, action, mod);
				if (window->LockInput == Window::ALLOW_ALL || window->LockInput == Window::ALLOW_MOUSE)
					continue;
				// stop accept input from lower windows
				else break;
			}
		}
	}
	void Core::CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
	{
		Core* core = static_cast<Core*>(glfwGetWindowUserPointer(window));
		core->io.UpdateCursorPos(xpos, ypos);
		if (core) {
			// first input topper window
			std::vector<std::shared_ptr<Window>>& windows = core->windows;
			for (auto& window : windows)
			{
				window->CursorPosEvent();
				if (window->LockInput == Window::ALLOW_ALL || window->LockInput == Window::ALLOW_MOUSE)
					continue;
				// stop accept input from lower windows
				else break;
			}
		}
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