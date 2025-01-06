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
		virtual void MouseEvent(int button, int action, int mod);
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

			GUI_Element(Resources* res, glm::vec2 point1, glm::vec2 point2, std::string shader_name);

			// check if point is in borders of gui object
			virtual bool IsInBounds(glm::vec2 point);
		protected:
			void CacheShader();
			std::string shader_name;
			Resources* res = nullptr;
			glm::vec2 point1{ 0, 0 };
			glm::vec2 point2{ 0, 0 };
			glm::mat4 model, projection;
			bool isVisible = true;
			bool isActive = true;
			Shader* cached_shader = nullptr;
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
		Color_Button(Resources* res, glm::vec2 point1, glm::vec2 point2, std::string shader_name);
		void Render() override;
		void MouseEvent(int button, int action, int mod) override;
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
		void MouseEvent(int button, int action, int mod) override;
		void OnKeyClick(int key, int scancode, int action, int mod) override;
		void Event() override;
	};
}