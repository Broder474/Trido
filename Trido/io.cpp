#include "IO.h"

namespace Input_Output
{
	IO::IO()
	{

	}
	void IO::UpdateCursorPos(double xpos, double ypos)
	{
		cursor_pos = { xpos / vid_size.x, 1 - ypos / vid_size.y };
	}
	void IO::init(GLFWwindow* window)
	{
		this->window = window;
		GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vid_mode = glfwGetVideoMode(primary_monitor);
		vid_size = { vid_mode->width, vid_mode->height };
		glfwGetMonitorContentScale(primary_monitor, &vid_scale.x, &vid_scale.y);
	}
	glm::vec2 IO::GetCursorPos() const { return cursor_pos; }
}