#pragma once
#include <GL/glew.h>
namespace chitraware {
	class VertexBuffer
	{
	private:
	public:
		GLuint ID ;
		
		VertexBuffer( GLfloat verts[], GLsizei );
		void bind();

	};



	
}