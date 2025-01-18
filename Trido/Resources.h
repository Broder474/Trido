#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>  
#include "Logger.h"
#include "IO.h"
#include "StateManager.h"

using namespace Input_Output;

class Resources
{
public:
	Resources(Logger& logger, IO* io);
	struct Texture
	{
		int width = 0;
		int height = 0;
		int channels = 0;
		float texelWidth = 0.f;
		float texelHeight = 0.f;
		GLuint tex_id = 0;
	};
	struct Shader
	{
		Shader(unsigned int shaderProgram, unsigned int VAO, unsigned int VBO) : shaderProgram(shaderProgram), VAO(VAO), VBO(VBO) {};
		unsigned int shaderProgram = 0;
		unsigned int VAO = 0, VBO = 0;
	};
	void Load();
	bool LoadTextureFromFile(const char* filename, Texture*& texture);
	unsigned int CreateShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile);
	unsigned int compileShader(unsigned int type, const char* source);
	std::map<std::string, Texture*>textures;
	std::map<std::string, Shader*>shaders;
	Logger& logger;
	IO* io;
	State::StateManager* sm;
private:
	const char* LoadShaderFromFile(const char* filename);
};