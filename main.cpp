#include "Window.h"
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/ext/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "shader.h"
#include "renderer.h"
#include "vertexBuffer.h"
 

const GLchar* vShaderSource = R"glsl(
	#version 440 core
layout (location=0) in vec3 position;
uniform  mat4 transform;
 out vec4 color;
void main(){
gl_Position=  transform * vec4(position, 1);
color = vec4(1,1,1,1);
}
)glsl";


const GLchar* fShaderSource = R"glsl(
#version 440 core
in vec4 color;
out vec4 fragColor;
void main(){
fragColor = color;
}
)glsl";


GLfloat vertdata[] = {
	-0.5,0.5,0,
	-0.5,-0.5,0,
	0.5,-0.5,0,
	0.5,0.5,0
};

GLfloat cube_colors[] = {
	// front colors
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 1.0,
	// back colors
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 1.0
};


using namespace chitraware;


int main() {
	std::cout << "Starting application" << std::endl;

	Window appWindow=  Window(960, 540, "My title", false);


	
	//element data//which vertices will be painted;
	GLuint elements[] = {
		0,1,2,
		0,2,3
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

	VertexBuffer vbo(vertdata, sizeof vertdata);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,NULL, NULL);
	glEnableVertexAttribArray(0);
	
	//elmement object variable
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof elements, elements, GL_STATIC_DRAW);


	glUseProgram(program.ID);

	//transform matrix
		glm::mat4 transform = glm::mat4(1.0f);
		glm::mat4 scale = glm::scale(glm::vec3(2.0, 2.0, 2.0));
		glm::mat4 rotate = glm::rotate((float)0.0, glm::vec3(0, 0, 1));
		glm::mat4 translate =  glm::translate(glm::vec3(0, 0, 0));
		glm::mat4 modelMatrix = translate * rotate * scale;

		glm::mat4 viewMatrix = glm::lookAt(
			glm::vec3(3, 3, -3), // Camera is at (4,3,3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

		glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), (float)appWindow.width / (float)appWindow.height, 0.1f, 100.0f);
		transform =   projectionMatrix* viewMatrix* modelMatrix;

		GLuint transformLoc = glGetUniformLocation(program.ID, "transform");

	//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));





	while (!glfwWindowShouldClose(appWindow.window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		rotate = glm::rotate((float)glfwGetTime(), glm::vec3(0, 0, 1));

		 modelMatrix = translate * rotate * scale;

		transform = projectionMatrix * viewMatrix * modelMatrix;
		//transform = glm::mat4(1.0f);
		
		//GLuint transformLoc = glGetUniformLocation(program.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		glfwSwapBuffers(appWindow.window);
		glfwPollEvents();
	}



	appWindow.destroy();
	return 0;

}



