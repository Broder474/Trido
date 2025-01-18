#include "UI.h"
namespace UI
{
	using GUI_Element = Window::GUI_Element;

	// Window basic class
	Window::Window(GLFWwindow* window, Resources* resources): window(window), res(resources) {
		
	}
	void Window::MouseEvent(int button, int action, int mod)
	{
		for (auto& gui_element : gui_elements)
			gui_element->MouseEvent(button, action, mod);
	}
	void Window::CursorPosEvent()
	{
		for (auto& gui_elements : gui_elements)
			gui_elements->CursorPosEvent();
	}
	void Window::RenderGUI()
	{

		for (auto& gui_element : gui_elements)
			gui_element->Render();
	}

	// GUI element basic class
	GUI_Element::GUI_Element(Resources* res, glm::vec2 point1, glm::vec2 point2, std::string shader_name): res(res), point1(point1), point2(point2), shader_name(shader_name), 
		projection(res->sm->projection)
	{
		glm::vec2 size = point2 - point1;
		glm::vec2 center = (point1 + point2) / 2.0f;
		
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(center, 0.0f));
		model = glm::scale(model, glm::vec3(size.x / 2.0f, size.y / 2.0f, 1.0f));
	}
	void GUI_Element::CacheShader() { cached_shader = res->shaders[shader_name]; }
	bool GUI_Element::IsInBounds(glm::vec2 point)
	{
		if (point.x >= point1.x && point.x < point2.x && point.y >= point1.y && point.y <= point2.y)
			return true;
		return false;
	}
	void GUI_Element::Render()
	{

	}

	Color_Button::Color_Button(Resources* res, glm::vec2 point1, glm::vec2 point2, std::string shader_name, rgba color): GUI_Element(res, point1, point2, shader_name), color(color)
	{
		hovered_color = color * 0.8f;
		pressed_color = color * 0.6f;
	}
	void Color_Button::Render()
	{
		if (!cached_shader)
			CacheShader();

		glUseProgram(cached_shader->shaderProgram); 

		glUniformMatrix4fv(glGetUniformLocation(cached_shader->shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// colors
		rgba& baseColor = isPressed ? pressed_color : isHovered ? hovered_color : this->color;
		rgba borderColor = { baseColor.r * 0.5f, baseColor.g * 0.5f, baseColor.b * 0.5f, baseColor.a };

		// draw border
		glm::vec3 scale = glm::vec3(1.0f + border_left, 1.0f + border_top, 1.0f); // Масштабируем равномерно
		glm::mat4 borderModel = glm::scale(model, scale);
		glUniformMatrix4fv(glGetUniformLocation(cached_shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(borderModel));
		glUniform4fv(glGetUniformLocation(cached_shader->shaderProgram, "color"), 1, borderColor.array);
		glBindVertexArray(cached_shader->VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// draw base color
		glUniformMatrix4fv(glGetUniformLocation(cached_shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniform4fv(glGetUniformLocation(cached_shader->shaderProgram, "color"), 1, baseColor.array);
		glBindVertexArray(cached_shader->VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	void Color_Button::MouseEvent(int button, int action, int mod)
	{
		if (!isActive || !IsInBounds(res->io->GetCursorPos()))
			return;
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			if (action == GLFW_PRESS)
			{
				isPressed = true;
			}
			else if (action == GLFW_RELEASE)
			{
				isPressed = false;
				MessageBoxA(0, "Release", 0, 0);
			}
		}
	}

	void Color_Button::CursorPosEvent()
	{
		if (isActive)
		{
			if (IsInBounds(res->io->GetCursorPos()))
				isHovered = true;
			else
				isHovered = isPressed = false;
		}
	}

	Image_Button::Image_Button(Resources* res, glm::vec2 point1, glm::vec2 point2, std::string shader_name, std::string texture_name) : GUI_Element(res, point1, point2, shader_name), 
		texture_name(texture_name)
	{

	}
	void Image_Button::Render()
	{

	}
	void Image_Button::MouseEvent(int button, int action, int mod)
	{

	}

	Image::Image(Resources* res, glm::vec2 point1, glm::vec2 point2, std::string shader_name, std::string texture_name) : GUI_Element(res, point1, point2, shader_name), texture_name(texture_name)
	{

	}
	void Image::Render() 
	{ 
		if (!cached_texture)
			cached_texture = res->textures[texture_name];
		if (!cached_shader)
			CacheShader();

		glUseProgram(cached_shader->shaderProgram);

		glUniformMatrix4fv(glGetUniformLocation(cached_shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(cached_shader->shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		// GLuint texelSizeLoc = glGetUniformLocation(cached_shader->shaderProgram, "texelSize");
		// glUniform2f(texelSizeLoc, cached_texture->texelWidth, cached_texture->texelHeight);
		glBindTexture(GL_TEXTURE_2D, cached_texture->tex_id);
		glBindVertexArray(cached_shader->VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
	}
	void Image::MouseEvent(int button, int action, int mod)
	{

	}

	MainWindow::MainWindow(GLFWwindow* window, Resources* resources) : Window(window, resources)
	{
		gui_elements.push_back(std::make_shared<Image>(Image(res, { 0.0f, 0.0f }, { 1920.0f, 1080.0f }, "shader1", "tex1")));
		//Color_Button* btn1 = new Color_Button(res, { 800.0f, 520.0f }, { 900.0f, 560.0f }, "shader2", rgba(.8f, 0.4f, 0.0f, 1.0f));
		//btn1->SetBorderTop(0.19f);
		//gui_elements.push_back(std::make_shared<Color_Button>(*btn1));
	}
	void MainWindow::Render() 
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		RenderGUI();
	}
	void MainWindow::OnKeyClick(int key, int scancode, int action, int mod)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
			glfwSetWindowShouldClose(window, true);
	}
	void MainWindow::Event()
	{

	}
}