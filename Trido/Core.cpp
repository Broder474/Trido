#include "Core.h"

namespace Core
{
	Core::Core(): res(logger, &io)
	{
		glfwInit();
		glewExperimental = GL_TRUE;

		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		gl_window = glfwCreateWindow(mode->width, mode->height, "Trido", nullptr, nullptr);
		glfwMakeContextCurrent(gl_window);
		glewInit();
		glfwSwapInterval(1);
		res.Load();
		io.init(gl_window, &res.sm->projection);

		glfwSetWindowUserPointer(gl_window, this);
		glfwSetKeyCallback(gl_window, Core::KeyCallback);
		glfwSetMouseButtonCallback(gl_window, Core::MouseCallback);
		glfwSetCursorPosCallback(gl_window, Core::CursorPosCallback);
		glfwSetWindowSizeCallback(gl_window, Core::WindowSizeCallback);

		windows.push_back(std::make_shared<MainWindow>(gl_window, &res));
		logger.print(Log_type::INFO, "Core run");
	}
	void Core::KeyCallback(GLFWwindow* gl_window, int key, int scancode, int action, int mod)
	{
		Core* core = static_cast<Core*>(glfwGetWindowUserPointer(gl_window));
		// global keybinds
		// fullscreen toogle
		if (key == GLFW_KEY_F12 && action == GLFW_RELEASE)
		{
			core->io.ToggleFullscreen();
			return;
		}

		// general key input
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
	void Core::WindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		Core* core = static_cast<Core*>(glfwGetWindowUserPointer(window));

		float scale_ratio = std::min((float)width / 1920, (float)height / 1080);
		if (scale_ratio == 1)
			glViewport(0, 0, width, height);
		else 
		{
			int viewport_width = static_cast<int>(1920 * scale_ratio);
			int viewport_height = static_cast<int>(1080 * scale_ratio);
			int viewport_x = (width - viewport_width) / 2;
			int viewport_y = (height - viewport_height) / 2;
			glViewport(viewport_x, viewport_y, viewport_width, viewport_height);
		}
		printf("Framebuffer resized: %d x %d\n", width, height);

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