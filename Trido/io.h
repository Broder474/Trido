#pragma once
#include <iostream>
#include <fstream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#include "logger.h"

namespace Input_Output
{
	class IO
	{
	public:
		IO();
		void init(GLFWwindow* window);
		void UpdateCursorPos(double xpos, double ypos);
		glm::vec2 GetCursorPos() const;
	private:
		GLFWwindow* window = nullptr;
		glm::vec2 cursor_pos{ 0, 0 };
		glm::vec2 vid_scale{ 0, 0 };
		glm::vec2 vid_size{ 0, 0 };
	};
}