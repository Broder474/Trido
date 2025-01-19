#pragma once
#include <iostream>
#include <fstream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>  
#include <GL/freeglut.h>
#include "logger.h"

namespace Input_Output
{
	class IO
	{
	public:
		IO();
		void init(GLFWwindow* window, glm::mat4* projection);
		void UpdateCursorPos(double xpos, double ypos);
		glm::vec2 GetCursorPos() const;
		glm::vec2 vid_size{ 0, 0 };
		float scale_ratio = 1.0f;
		GLFWwindow* window = nullptr;
		glm::vec2 cursor_pos{ 0, 0 };
		glm::vec2 vid_scale{ 0, 0 };
		bool isFullscreen = false;
		glm::mat4* projection = nullptr;
		float vp_offset_x = 0.f, vp_offset_y = 0.f;
		void ToggleFullscreen();
	private:
	};
}