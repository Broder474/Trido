#include <functional>
#include "Resources.h"
#include <iostream>

// id means z-index in context of windows, higher id is upper
typedef unsigned int id;

namespace UI
{
	class Window
	{
		// permit to receive input from lower windows
		// by default upper window will forbid input from lower window, change it to ALLOW_ALL if you need mouse and keyboard input or ALLOW_MOUSE if mouse only
	public:
		Window(GLFWwindow* window, Resources* resources);
		virtual void Render() {};
		virtual void MouseEvent(int button, int action, int mod) {};
		virtual void OnKeyClick(int key, int scancode, int action, int mod) {};
		virtual void Event() {};

		enum InputRule { ALLOW_ALL, ALLOW_MOUSE, FORBID_ALL }LockInput = FORBID_ALL;

		class GUI_Element
		{
			using CallBack = std::function<void()>;
		public:
			// mouse button click borders
			glm::vec2 point1{ 0, 0 };
			glm::vec2 point2{ 0, 0 };
			virtual void MouseEvent(int button, int action, int mod) {};

			GUI_Element(glm::vec2 point1, glm::vec2 point2);

			// check if point is in borders of gui object
			virtual bool IsInBounds(glm::vec2);
		};

		std::vector<std::shared_ptr<GUI_Element>>gui_elements;
	protected:
		GLFWwindow* window = nullptr;
		Resources* res = nullptr;
		float mouseX = 0.0f, mouseY = 0.0f;
	};

	class Color_Button : public Window::GUI_Element
	{		
	public:
		Color_Button(glm::vec2 point1, glm::vec2 point2);
		void MouseEvent(int button, int action, int mod) override;
	};

	class MainWindow : public Window
	{
	public:
		MainWindow(GLFWwindow* window, Resources* resources);
		void Render() override;
		void MouseEvent(int button, int action, int mod) override;
		void OnKeyClick(int key, int scancode, int action, int mod) override;
		void Event() override;

		float vertices[20] = {
			// позиции       // текстурные координаты
			 0.5f,  1.f, 0.0f,  1.0f, 1.0f, // верхний правый угол
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // нижний правый угол
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // нижний левый угол
			-0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // верхний левый угол
		};

		unsigned int indices[6] = {
			0, 1, 3, // первый треугольник
			1, 2, 3  // второй треугольник
		};
		unsigned int shaderProgram;
		unsigned int VBO, VAO, EBO;
	};
}