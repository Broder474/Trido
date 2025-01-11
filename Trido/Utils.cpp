#include "Utils.h"

namespace Utils
{
	rgba::rgba(GLfloat r, GLfloat g, GLfloat b, GLfloat a) : r(r), g(g), b(b), a(a)
	{
		
	}
	rgba::rgba(GLfloat r, GLfloat g, GLfloat b) :r(r), g(g), b(b), a(1.0f)
	{

	}
}