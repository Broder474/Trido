#pragma once
#include <GL/freeglut.h>
namespace Utils
{
		union rgba {
			rgba(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
			rgba(GLfloat r, GLfloat g, GLfloat b);
			GLfloat array[4];
			struct {
				GLfloat r, g, b, a;
			};
	};
}