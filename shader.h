#pragma once
#include<GL/glew.h>
namespace chitraware {



	class Shader
	{
	private:
		GLuint ID;
		GLuint type;
		const GLchar *source;
	public:
		Shader(GLuint,  const GLchar* source);
		void bind();
		void attach(const GLuint program);


	};

}

