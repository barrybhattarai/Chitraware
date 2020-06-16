#pragma once


#include<GLFW/glfw3.h>




//class of the window object in Chitrware.
class Window {


private:
	int width; //width of the window.
	int height;  // height of the window.
	GLFWmonitor* monitor = NULL; // monitor object of the current window.
	const GLFWvidmode* vidMode = NULL; // video mode of the current monitor.
	bool isFullScreen;  // whether the window is fullscreen.
	const char* title; // title of the window.
	GLFWkeyfun keypressfun;
public:
	GLFWwindow* window;// the glfw window object.



public:
	Window(int _width, int _height, const char* _title, bool _isFullScreen) {

		glfwInit(); // initializing glfw context to be used.
		width = _width;
		height = _height;
		isFullScreen = _isFullScreen;
		title = _title;


		//when to create full screen is true.
		if (isFullScreen) {

			monitor = glfwGetPrimaryMonitor();// getting the monitor where fullscreen is to be created/ Just the primary by default.
			vidMode = glfwGetVideoMode(monitor); // video mode of the monitor about to set the fullscreen to.

			//video mode for the fullscreen window mode width and height for the window object.
			height = vidMode->height;
			width = vidMode->width;

		}

		init();
		window = glfwCreateWindow(width, height, title, monitor, NULL);// creating window object with the needed agruments. 
		
		
		glfwSetKeyCallback(window, keypressfun);
	}

private:
	void setFullScreen(bool fullScreenStatus) {
		if (fullScreenStatus) {
			if (!isFullScreen) {
				//setting the monitor to make the window full screen.

				isFullScreen = true;

				if (!monitor) {
					monitor = glfwGetPrimaryMonitor();// getting the monitor where fullscreen is to be created/ Just the primary by default.
					vidMode = glfwGetVideoMode(monitor); // video mode of the monitor about to set the fullscreen to.

					//video mode for the fullscreen window mode width and height for the window object.
					height = vidMode->height;
					width = vidMode->width;
				}
				//setting the monitor for it to be fullscreen.
				glfwSetWindowMonitor(window, monitor, 0, 0, vidMode->width, vidMode->height, vidMode->refreshRate);

			}
		}
		else {
			if (!monitor) {
				monitor = glfwGetPrimaryMonitor();// getting the monitor where fullscreen is to be created/ Just the primary by default.
				vidMode = glfwGetVideoMode(monitor); // video mode of the monitor about to set the fullscreen to.

				//video mode for the fullscreen window mode width and height for the window object.
				height = vidMode->height;
				width = vidMode->width;
			}

			glfwSetWindowMonitor(window, NULL, 200, 200, width / 2, height / 2, vidMode->refreshRate);
			isFullScreen = false;

		}

	}

	void init() {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
		glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);
		glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);


	}
	void onPressEvent (GLFWwindow* _window, int keyCode, int scanCode, int action, int mods) {
		if (action == GLFW_PRESS && keyCode == GLFW_KEY_F) {
			setFullScreen(!isFullScreen);
		}
	}
public:

	void destroy() {
		glfwTerminate();
	}

}


