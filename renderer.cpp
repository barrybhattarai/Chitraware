#include "renderer.h"
#include<iostream>

using namespace chitraware;

Renderer::Renderer() {
	ID = glCreateProgram();

}

void Renderer::link() {
	glLinkProgram(ID);
}