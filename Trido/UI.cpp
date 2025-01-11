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
		{
			
		}
	}
	void Window::RenderGUI()
	{
		for (auto& gui_element : gui_elements)
			gui_element->Render();
	}

	// GUI element basic class
	GUI_Element::GUI_Element(Resources* res, glm::vec2 point1, glm::vec2 point2, std::string shader_name): res(res), point1(point1), point2(point2), shader_name(shader_name)
	{
		glm::vec2 size = point2 - point1;
		glm::vec2 center = (point1 + point2) * 0.5f;
		
		// create model matrix
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(center, 0.0f));
		// [-1;1] -> [-0.5;0.5]
		model = glm::scale(model, glm::vec3(size.x / 2, size.y / 2, 1.0f));
		// projection matrix
		// [-0.5;0.5] -> [0, 1]
 		projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, -0.1f, 0.1f);
	}
	void GUI_Element::CacheShader() { cached_shader = res->shaders[shader_name]; }
	bool GUI_Element::IsInBounds(glm::vec2 point)
	{
		// надо проверить какие координаты при клике, чтобы понимать откуда считать координаты, а потом писать логику
		return true;
	}
	void GUI_Element::Render()
	{

	}

	Color_Button::Color_Button(Resources* res, glm::vec2 point1, glm::vec2 point2, std::string shader_name, rgba color): GUI_Element(res, point1, point2, shader_name), color(color)
	{

	}
	void Color_Button::Render()
	{
		if (!cached_shader)
			CacheShader();

		glUseProgram(cached_shader->shaderProgram); 

		glUniformMatrix4fv(glGetUniformLocation(cached_shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(cached_shader->shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniform4fv(glGetUniformLocation(cached_shader->shaderProgram, "color"), 1, color.array);
		glBindVertexArray(cached_shader->VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	void Color_Button::MouseEvent(int button, int action, int mod)
	{
		if (isActive)
		{
			glm::vec2 curs_pos = res->io->GetCursorPos();
			if (button == GLFW_MOUSE_BUTTON_LEFT)
			{
				if (action == GLFW_PRESS)
				{
					MessageBoxA(0, "press", 0, 0);
				}
				else if (action == GLFW_RELEASE)
				{
					MessageBoxA(0, "release", 0, 0);
				}
			}

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
		gui_elements.push_back(std::make_shared<Image>(Image(res, { 0.0f, 0.9f }, { 0.1f, 1.0f }, "shader1", "tex1")));
		gui_elements.push_back(std::make_shared<Color_Button>(Color_Button(res, { 0.45f, 0.45f }, { 0.55f, 0.55f }, "shader2", rgba(.0f, 1, 0, 1.0f))));
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
	void MainWindow::MouseEvent(int button, int action, int mod)
	{
		
	}
	void MainWindow::Event()
	{

	}
}