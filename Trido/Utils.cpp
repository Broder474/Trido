#include "Utils.h"

namespace Utils
{
	rgba::rgba(GLfloat r, GLfloat g, GLfloat b, GLfloat a) : r(r), g(g), b(b), a(a)
	{
		
	}
	rgba::rgba(GLfloat r, GLfloat g, GLfloat b) :r(r), g(g), b(b), a(1.0f)
	{

	}
	rgba::rgba() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {};
	rgba rgba::operator * (float gain)
	{
		return { r * gain, g * gain, b * gain };
	}
}