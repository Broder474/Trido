#include "IO.h"

namespace Input_Output
{
	IO::IO()
	{

	}
	void IO::UpdateCursorPos(double xpos, double ypos)
	{
		cursor_pos = { xpos / scale_ratio, 1080 - ypos / scale_ratio };
		printf("x: %f y: %f\n", cursor_pos.x, cursor_pos.y);
	}
	void IO::init(GLFWwindow* window, glm::mat4* projection)
	{
		this->window = window;
		this->projection = projection;
		GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vid_mode = glfwGetVideoMode(primary_monitor);
		glfwGetMonitorContentScale(primary_monitor, &vid_scale.x, &vid_scale.y);
		vid_size = { vid_mode->width, vid_mode->height };
		vid_size /= vid_scale.x;
		float scale_ratio_width = (float)vid_mode->width / 1920;
		float scale_ratio_height = (float)vid_mode->height / 1080;
		// надо сюда еще добавить масштабирование если экран больше, но мне впадлу
		scale_ratio = std::min(scale_ratio_width, scale_ratio_height);
	}
	glm::vec2 IO::GetCursorPos() const { return cursor_pos; }
	void IO::ToggleFullscreen()
	{
		isFullscreen = !isFullscreen;
		if (isFullscreen)
			glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, (int)vid_size.x, (int)vid_size.y, GLFW_DONT_CARE);
		else
			glfwSetWindowMonitor(window, nullptr, 0, 0, (int)vid_size.x, (int)vid_size.y, GLFW_DONT_CARE);
		glViewport(0, 0, (int)vid_size.x, (int)vid_size.y);
		printf("Framebuffer resized: %f x %f\n", vid_size.x, vid_size.y);
	}
}