#include "vertexBuffer.h"
#include <iostream>


using namespace chitraware;



VertexBuffer::VertexBuffer( GLfloat verts[], GLsizei size){
glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size , verts, GL_STATIC_DRAW);
 
	
};

void VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);

}

