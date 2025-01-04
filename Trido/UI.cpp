#include "UI.h"
namespace UI
{
	using GUI_Element = Window::GUI_Element;

	// Window basic class
	Window::Window(GLFWwindow* window, Resources* resources): window(window), res(resources) {
		
	}

	// GUI element basic class
	GUI_Element::GUI_Element(glm::vec2 point1, glm::vec2 point2): point1(point1), point2(point2)
	{

	}
	bool GUI_Element::IsInBounds(glm::vec2)
	{
		// ���� ��������� ����� ���������� ��� �����, ����� �������� ������ ������� ����������, � ����� ������ ������
		return true;
	}

	Color_Button::Color_Button(glm::vec2 point1, glm::vec2 point2): GUI_Element(point1, point2)
	{

	}

	void Color_Button::MouseEvent(int button, int action, int mod)
	{
		
	}


	MainWindow::MainWindow(GLFWwindow* window, Resources* resources) : Window(window, resources)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// �������� ������
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// �������� ���������� ���������
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec2 aTexCoord;

        out vec2 TexCoord;

        void main() {
            gl_Position = vec4(aPos, 1.0);
            TexCoord = aTexCoord;
        }
    )";

		const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

        in vec2 TexCoord;

        uniform sampler2D texture1;

        void main() {
            FragColor = texture(texture1, TexCoord);
        }
    )";
		shaderProgram = res->createShaderProgram(vertexShaderSource, fragmentShaderSource);

		gui_elements.push_back(std::make_shared<Color_Button>(Color_Button({ 0, 0 }, { 1920, 1080 })));
	}
	void MainWindow::Render() 
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindTexture(GL_TEXTURE_2D, res->textures["tex1"].tex_id);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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