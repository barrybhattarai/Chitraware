#include "Window.h"
#include<iostream>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/ext/matrix_transform.hpp>
#include "shader.h"
#include "renderer.h"
 

const GLchar* vShaderSource = R"glsl(
	#version 440 core
layout(location=0) in vec3 position;
uniform mat4 transform;
out vec4 color;
void main(){
gl_Position=  transform* vec4(position, 1);
color = vec4(1,1,1,1);
}
)glsl";


const GLchar* fShaderSource = R"glsl(
#version 440 core
out vec4 fragColor;
in vec4 color;
void main(){
fragColor = color;
}
)glsl";


using namespace chitraware;


int main() {
	std::cout << "Starting application" << std::endl;

	Window appWindow=  Window(960, 540, "My title", false);

	GLfloat vertices[] = {
		-0.5,0.5,1.0,
		-0.5,-0.5,1.0,
		0.5,-0.5,1.0,
		0.5,0.5,1.0,

		/*-0.5,0.5,-0.5,
		-0.5,-0.5,-0.5,
		0.5,-0.5,-0.5,
		0.5,0.5,-0.5*/

	};
	
	//element data//which vertices will be painted;
	GLuint elements[] = {
		0,1,2,
		0,2,3,
		/*4,6,5,
		4,7,6,
		0,5,1,
		0,4,5,
		6,3,2,
		6,7,3,
		7,4,0,
		7,4,3,
		5,6,2,
		5,2,1*/
	};
	//vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//shader compilation part 1. vertex shader
	Shader vShader(GL_VERTEX_SHADER, vShaderSource);
	
	// fragment shader
	Shader fShader(GL_FRAGMENT_SHADER, fShaderSource);

	
	//shader program
	Renderer program;
	fShader.attach(program.ID);
	vShader.attach(program.ID);
	program.link();


	//
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof GLfloat, NULL);
	glEnableVertexArrayAttrib(vao, 0);

	//elmement object variable
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof elements, elements, GL_STATIC_DRAW);


		glUseProgram(program.ID);

	//transform matrix
	glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		//transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
	transform = glm::rotate(transform, (GLfloat)1.0, glm::vec3(0, 0, 1.0));
		GLuint transformLoc = glGetUniformLocation(program.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));



	while (!glfwWindowShouldClose(appWindow.window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		glfwSwapBuffers(appWindow.window);
		glfwPollEvents();
	}



	appWindow.destroy();
	return 0;

}



