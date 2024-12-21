#include "UI.h"
namespace UI
{
	Window::Window(GLFWwindow* window, Resources* resources): window(window), res(resources) {
		
	}
	GUI_Element::GUI_Element(glm::vec2 point1, glm::vec2 point2) {
	}
	bool GUI_Element::IsInBounds(glm::vec2)
	{
		// надо проверить какие координаты при клике, чтобы понимать откуда считать координаты, а потом писать логику
		return true;
	}
	template<class Object, class Method>
	void GUI_Element::SetOnMouseHoverCallback(Object* OnMouseHoverObj, Method OnMouseHoverMethod) {
		OnMouseHover = std::bind(OnMouseHoverMethod, OnMouseHoverObj);
	}
	template<class Object, class Method>
	void GUI_Element::SetLeftMouseButtonPressed(Object* LeftMouseButtonPressedObj, Method LeftMouseButtonPressedMethod) {
		LeftMouseButtonPressed = std::bind(LeftMouseButtonPressedMethod, LeftMouseButtonPressedObj);
	}
	template<class Object, class Method>
	void GUI_Element::SetRightMouseButtonPressed(Object* RightMouseButtonPressedObj, Method RightMouseButtonPressedMethod) {
		RightMouseButtonPressed = std::bind(RightMouseButtonPressedMethod, RightMouseButtonPressedObj);
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

		// Атрибуты вершин
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Атрибуты текстурных координат
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
	}
	void MainWindow::Render() 
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindTexture(GL_TEXTURE_2D, res->textures[0].tex_id);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	void MainWindow::OnKeyClick(int key, int scancode, int action, int mod)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
			glfwSetWindowShouldClose(window, true);
	}
	void MainWindow::OnMouseClick(int button, int action, int mod)
	{

	}
	void MainWindow::OnCursorPos(double xpos, double ypos)
	{

	}
	void MainWindow::Event()
	{

	}
}