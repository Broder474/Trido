#include <functional>
#include "Resources.h"
#include "Utils.h"

// id means z-index in context of windows, higher id is upper
typedef unsigned int id;
using namespace Utils;

namespace UI
{
	class Window
	{
		// permit to receive input from lower windows
		// by default upper window will forbid input from lower window, change it to ALLOW_ALL if you need mouse and keyboard input or ALLOW_MOUSE if mouse only
	public:
		Window(GLFWwindow* window, Resources* resources);
		virtual void Render() {};
		virtual void MouseEvent(int button, int action, int mod);
		virtual void CursorPosEvent();
		virtual void OnKeyClick(int key, int scancode, int action, int mod) {};
		virtual void Event() {};
		void RenderGUI();

		enum InputRule { ALLOW_ALL, ALLOW_MOUSE, FORBID_ALL }LockInput = FORBID_ALL;

		class GUI_Element
		{
			using CallBack = std::function<void()>;
		public:
			using Texture = Resources::Texture;
			using Shader = Resources::Shader;
			// mouse button click borders
			virtual void Render();
			virtual void MouseEvent(int button, int action, int mod) {};
			virtual void CursorPosEvent() {};

			GUI_Element(Resources* res, glm::vec2 point1, glm::vec2 point2, std::string shader_name);

			// check if point is in borders of gui object
			virtual bool IsInBounds(glm::vec2 point);
		protected:
			void CacheShader();
			std::string shader_name;
			Resources* res = nullptr;
			glm::vec2 point1{ 0, 0 };
			glm::vec2 point2{ 0, 0 };
			glm::mat4 model;
			glm::mat4& projection;
			bool isVisible = true;
			bool isActive = true;
			Shader* cached_shader = nullptr;
		};

		std::vector<std::shared_ptr<GUI_Element>>gui_elements;
	protected:
		GLFWwindow* window = nullptr;
		Resources* res = nullptr;
	};

	class Color_Button : public Window::GUI_Element
	{		
	public:
		Color_Button(Resources* res, glm::vec2 point1, glm::vec2 point2, std::string shader_name, rgba rgba);
		void Render() override;
		void MouseEvent(int button, int action, int mod) override;
		void CursorPosEvent() override;
		void SetBorderTop(float size) { border_top = size; }
		void SetBorderLeft(float size) { border_left = size; }
	private:
		rgba color;
		rgba hovered_color;
		rgba pressed_color;
		bool isHovered = false, isPressed = false;
		float border_top = 0.09f, border_left = 0.05f;
	};

	class Image_Button : public Window::GUI_Element
	{
	public:
		Image_Button(Resources* res, glm::vec2 point1, glm::vec2 point2, std::string shader_name, std::string texture_name);
		void MouseEvent(int button, int action, int mod) override;
		void Render() override;
	private:
		std::string texture_name;
	};

	class Image : public Window::GUI_Element
	{
	public:
		Image(Resources* res, glm::vec2 point1, glm::vec2 point2, std::string shader_name, std::string texture_name);
		void Render() override;
		void MouseEvent(int button, int action, int mod) override;
	private:
		std::string texture_name;
		Texture* cached_texture = nullptr;
	};

	class MainWindow : public Window
	{
	public:
		MainWindow(GLFWwindow* window, Resources* resources);
		void Render() override;
		void OnKeyClick(int key, int scancode, int action, int mod) override;
		void Event() override;
	};
}