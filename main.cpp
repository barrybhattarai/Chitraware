#include "Window.h"
#include<iostream>
#include<GLFW/glfw3.h>

int main() {
	std::cout << "Starting to create window";
	Window appWindow = Window(500, 500, "My title", false);

	while (!glfwWindowShouldClose(appWindow.window)) {
		glfwSwapBuffers(appWindow.window);
		glfwPollEvents();
	}

	appWindow.destroy();
	return 0;

}