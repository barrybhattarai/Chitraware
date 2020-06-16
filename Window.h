#pragma once
#define GLEW_STATIC
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>


namespace chitraware {
	//class of the window object in Chitrware.
	class Window {


	private:
		int width; //width of the window.
		int height;  // height of the window.
		GLFWmonitor* monitor = NULL; // monitor object of the current window.
		const GLFWvidmode* vidMode = NULL; // video mode of the current monitor.
		bool isFullScreen;  // whether the window is fullscreen.
		const char* title; // title of the window.
		static Window* instance;
	public:
		GLFWwindow* window;// the glfw window object.

		Window(int _width, int _height, const char* _title, bool _isFullScreen) {

			glfwInit(); // initializing glfw context to be used.
			width = _width;
			height = _height;
			isFullScreen = _isFullScreen;
			title = _title;
			instance = this;

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
			glfwMakeContextCurrent(window);
			glewInit();
			glfwSetKeyCallback(window, keyCallback);
			glfwSetFramebufferSizeCallback(window, frameBufferCallback);
			glClearColor(0,0,0,1);
			glEnable(GLFW_SAMPLES);
			glEnable(GL_DEPTH);
		}


		void setFullScreen(bool fullScreenStatus) {
			if (fullScreenStatus) {
				if (!isFullScreen) {
					//setting the monitor to make the window full screen.

					isFullScreen = true;

					if (!monitor) {
						monitor = glfwGetPrimaryMonitor();// getting the monitor where fullscreen is to be created/ Just the primary by default.
						vidMode = glfwGetVideoMode(monitor); // video mode of the monitor about to set the fullscreen to.

						//video mode for the fullscreen window mode width and height for the window object.
					}
					height = vidMode->height;
					width = vidMode->width;

					//setting the monitor for it to be fullscreen.
					glfwSetWindowMonitor(window, monitor, 0, 0, width, height, vidMode->refreshRate);

				}
			}
			else {
				if (!monitor) {
					monitor = glfwGetPrimaryMonitor();// getting the monitor where fullscreen is to be created/ Just the primary by default.
					vidMode = glfwGetVideoMode(monitor); // video mode of the monitor about to set the fullscreen to.

					//video mode for the fullscreen window mode width and height for the window object.

				}
				height = vidMode->height/2;
				width = vidMode->width/2;

				glfwSetWindowMonitor(window, NULL, 200, 200, width , height , vidMode->refreshRate);
				isFullScreen = false;

			}
		}

		void init() {
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
			glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
			glfwWindowHint(GLFW_SAMPLES, 4);
		}

		void destroy() {
			glfwTerminate();
		}

		static void keyCallback(GLFWwindow*, int keyCode, int, int action, int) {
			if (keyCode == GLFW_KEY_F && action == GLFW_PRESS)
				instance->setFullScreen(!instance->isFullScreen);
		}

		static void frameBufferCallback(GLFWwindow* window, int _width, int _height) {
			glViewport(0, 0, _width, _width);
		}

	};

	Window* Window::instance = NULL;
}