#include "shader.h"


using namespace chitraware;

Shader::Shader(GLuint _type, const GLchar* _source) {
	//vertex array object
	type = _type;
	ID = glCreateShader(type);
	source = _source;
	glShaderSource(ID, 1, &source, nullptr);
	glCompileShader(ID);
}

void Shader::bind() {
	
};


void Shader::attach(const GLuint program) {
	glAttachShader(program, ID);
}













