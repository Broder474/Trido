#include <functional>
#include "Resources.h"
#include <iostream>

// id means z-index in context of windows, higher id is upper
typedef unsigned int id;

namespace UI
{
	class Window
	{
	public:
		Window(GLFWwindow* window, Resources* resources);
		virtual void Render() {};
		virtual void OnMouseClick(int button, int action, int mod) {};
		virtual void OnKeyClick(int key, int scancode, int action, int mod) {};
		virtual void OnCursorPos(double xpos, double ypos) {};
		virtual void Event() {};
		// permit to receive input from lower windows
		enum InputRule { ALLOW_ALL, ALLOW_MOUSE, FORBID_ALL }LockInput = FORBID_ALL;

	protected:
		GLFWwindow* window = nullptr;
		Resources* res = nullptr;
		double mouseX, mouseY;

	};
	class MainWindow : public Window
	{
	public:
		MainWindow(GLFWwindow* window, Resources* resources);
		void Render() override;
		void OnMouseClick(int button, int action, int mod) override;
		void OnKeyClick(int key, int scancode, int action, int mod) override;
		void OnCursorPos(double xpos, double ypos) override;
		void Event() override;

		float vertices[20] = {
			// позиции       // текстурные координаты
			 0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // верхний правый угол
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
	class GUI_Element
	{
	public:
		// ivec set mouse button click borders
		glm::vec2 point1;
		glm::vec2 point2;

		// check if point is in borders of gui object
		virtual bool IsInBounds(glm::vec2);
		
		using CallBack = std::function<void()>;

		CallBack OnMouseHover;
		CallBack LeftMouseButtonPressed;
		CallBack RightMouseButtonPressed;

		GUI_Element(glm::vec2 point1, glm::vec2 point2);

		template<class Object, class Method>
		void SetOnMouseHoverCallback(Object* OnMouseHoverObj, Method OnMouseHoverMethod);
		template<class Object, class Method>
		void SetLeftMouseButtonPressed(Object* LeftMouseButtonPressedObj, Method LeftMouseButtonMethod);
		template<class Object, class Method>
		void SetRightMouseButtonPressed(Object* RightMouseButtonPressedObj, Method RighMouseButtonMethod);
	};
}