#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Logger.h"

class Settings
{
public:
	float monitory_scaleX = 0;
	float monitory_scaleY = 0;
	const GLFWvidmode* video_mode;
};
struct Resources
{
	Resources(Logger* logger);
	struct Texture
	{
		int width;
		int height;
		int channels;
		GLuint tex_id = 0;
	};
	void Load();
	bool LoadTextureFromFile(const char* filename, Texture* texture);
	std::vector<Texture>textures;
	Logger* logger = nullptr;
	unsigned int createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
	unsigned int compileShader(unsigned int type, const char* source);
};
class System
{
public:
	float monitor_scaleX = 0;
	float monitor_scaleY = 0;
	const GLFWvidmode* video_mode;
};