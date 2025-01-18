#include "Resources.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Resources::Resources(Logger& logger, IO* io) : logger(logger), io(io)
{
	stbi_set_flip_vertically_on_load(true);
	sm = new State::StateManager();
};

unsigned int Resources::compileShader(unsigned int type, const char* source) {
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	// Error check
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
 	if (!success) {
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		logger.print(Log_type::LOG_ERROR, infoLog);
	}
	return shader;
}

unsigned int Resources::CreateShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile) {
	// compiling shaders
	const char* vertexShaderSource = LoadShaderFromFile(vertexShaderFile);
	const char* fragmentShaderSource = LoadShaderFromFile(fragmentShaderFile);
	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	// creating shader program
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	// linking check
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		logger.print(Log_type::LOG_ERROR, infoLog);
	}

	// delete shaders after linking
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	delete[] vertexShaderSource;
	delete[] fragmentShaderSource;

	return program;
}
void Resources::Load()
{
	int textures_count = 1;
	for (int i = 0; i < textures_count; i++)
	{
		// handling xml data
	}
	Texture* tex1 = nullptr;
	if (LoadTextureFromFile("textures/tex1.png", tex1))
		textures.insert({ "tex1", tex1 });
	else
		logger.print(Log_type::INFO, std::to_string(GetLastError()));

	{
		unsigned int shaderProgram = CreateShaderProgram("shaders/vert1.vert", "shaders/frag1.frag");

		float vertices[20] = {
			// positions  // texture coordinates
			 -1.0f,  -1.0f, 0.0f,  0.0f, 0.0f,  // left down
			 -1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // left top
			1.0f, -1.0f, 0.0f,  1.0f, 0.0f, // right down
			1.0f,  1.0f, 0.0f,  1.0f, 1.0f  // right top
		};

		unsigned int indices[6] = {
			0, 1, 2,
			1, 2, 3
		};
		unsigned int VBO, VAO, EBO;

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

		shaders.insert({ "shader1", new Shader(shaderProgram, VAO, VBO) });
	}

	{
		unsigned int shaderProgram = CreateShaderProgram("shaders/vert2.vert", "shaders/frag2.frag");

		float vertices[20] = {
			// positions  // texture coordinates
			-1.0f,  -1.0f, 0.0f,  // left down
			-1.0f, 1.0f, 0.0f, // left top
			1.0f, -1.0f, 0.0f, // right down
			1.0f,  1.0f, 0.0f // right top
		};
		unsigned int indices[6] = {
			0, 1, 2,
			1, 2, 3
		};
		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);

		shaders.insert({ "shader2", new Shader(shaderProgram, VAO, VBO) });
	}
}
bool Resources::LoadTextureFromFile(const char* filename, Texture*& texture)
{
	// Load from file
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

	// Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	texture = new Texture();
	texture->tex_id = image_texture;
	texture->width = image_width;
	texture->height = image_height;
	texture->channels = 4;
	texture->texelWidth = 1. / image_width;
	texture->texelHeight = 1. / image_height;
}

const char* Resources::LoadShaderFromFile(const char* filename)
{
	std::ifstream stream(filename);
	if (!stream.is_open())
	{
		std::string error_string = "Shader \"" + std::string(filename) + "\" not found";
		logger.print(Log_type::LOG_ERROR, error_string);
	}
	std::string data = "";
	std::string temp = "";
	while (std::getline(stream, temp)) { data += temp + "\n"; };
	stream.close();
	char* result = new char[data.size() + 1];
	std::copy(data.begin(), data.end(), result);
	result[data.size()] = '\0';
	return result;
}