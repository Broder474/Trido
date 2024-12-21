#include "Resources.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Resources::Resources(Logger* logger) : logger(logger) 
{
	stbi_set_flip_vertically_on_load(true);
};

unsigned int Resources::compileShader(unsigned int type, const char* source) {
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	// Проверка на ошибки
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		logger->print(Log_type::LOG_ERROR, infoLog);
	}
	return shader;
}

// Функция для создания программы
unsigned int Resources::createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
	// Компиляция шейдеров
	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	// Создание шейдерной программы
	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	// Проверка на ошибки линковки
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		logger->print(Log_type::LOG_ERROR, infoLog);
	}

	// Удаляем шейдеры после линковки
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}
void Resources::Load()
{
	int textures_count = 1;
	textures.reserve(textures_count);
	for (int i = 0; i < textures_count; i++)
	{
		// handling xml data
	}
	Resources::Texture tex1;
	if (LoadTextureFromFile("textures/tex1.png", &tex1))
		textures.push_back(tex1);
}
bool Resources::LoadTextureFromFile(const char* filename, Texture* texture)
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

	texture->tex_id = image_texture;
	texture->width = image_width;
	texture->height = image_height;
	texture->channels = 4;
}