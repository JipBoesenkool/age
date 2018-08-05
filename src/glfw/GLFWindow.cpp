//
// Created by Jip Boesenkool on 09/12/2017.
//
#include "glfw/GLFWindow.h"

GLFWwindow* GLFWindow::mpWindow;

//Public Functions
GLFWindow::GLFWindow( )
		: IWindow()
{
	mWidth	= 1080;
	mHeight	= 1920;
	mTitle	= (char*)"NULL";
}

GLFWindow::GLFWindow( int width, int height, char* title )
		: IWindow()
{
	mWidth	= width;
	mHeight= height;
	mTitle	= title;

	//Create the window
	GLFWindow::CreateWindow(mWidth, mHeight, mTitle);

	//Setup GLFW callbacks
	SetupCallbacks();
}

void GLFWindow::SetupCallbacks()
{
	// Set the error callback
	glfwSetErrorCallback(GLFWindow::ErrorCallback);
	// Set the key callback
	glfwSetKeyCallback(GLFWindow::mpWindow, GLFWindow::KeyCallback);
	// Set the mouse callback
	glfwSetCursorPosCallback(GLFWindow::mpWindow, GLFWindow::MouseCallback);
	glfwSetScrollCallback(GLFWindow::mpWindow, GLFWindow::ScrollCallback);
	// Set the window resize callback
	glfwSetFramebufferSizeCallback(GLFWindow::mpWindow, GLFWindow::ResizeCallback);
}

void GLFWindow::ErrorCallback(int error, const char* description)
{
	// Print error
	fputs(description, stderr);
}

void GLFWindow::ResizeCallback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	glfwGetFramebufferSize(window, &width, &height); // In case your Mac has a retina display
#endif

	IWindow::Get()->Resize(width, height);
	// Instantiate the event. The event system tracks all events with smart
	// pointers, so you must instantiate the event using a smart pointer.
	std::shared_ptr<WindowResizeEvent> pNewEvent( new WindowResizeEvent(width, height) );
	// Trigger the event.
	IEventManager::Get()->TriggerEvent(pNewEvent);
}

void GLFWindow::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Instantiate the event. The event system tracks all events with smart
	// pointers, so you must instantiate the event using a smart pointer.
	std::shared_ptr<KeyEvent> pNewEvent( new KeyEvent(key, scancode, action, mods) );
	// Trigger the event.
	IEventManager::Get()->QueueEvent(pNewEvent);
}

void GLFWindow::MouseCallback( GLFWwindow *window, double xpos, double ypos )
{
	// Instantiate the event. The event system tracks all events with smart
	// pointers, so you must instantiate the event using a smart pointer.
	std::shared_ptr<MouseMoveEvent> pNewEvent( new MouseMoveEvent(xpos, ypos) );
	// Trigger the event.
	IEventManager::Get()->QueueEvent(pNewEvent);
}

void GLFWindow::ScrollCallback( GLFWwindow *window, double xoffset, double yoffset )
{
	// Instantiate the event. The event system tracks all events with smart
	// pointers, so you must instantiate the event using a smart pointer.
	std::shared_ptr<MouseScrollEvent> pNewEvent( new MouseScrollEvent(xoffset, yoffset) );
	// Trigger the event.
	IEventManager::Get()->QueueEvent(pNewEvent);
}

//Interface Functions
void GLFWindow::CreateWindow( int width, int height, char* title )
{
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	//TODO: should not be here, opengl specific
#ifdef __APPLE__ // Because Apple hates comforming to standards
	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif


	// Create the GLFW window
	GLFWindow::mpWindow = glfwCreateWindow(mWidth, mHeight, mTitle, NULL, NULL);

	// Check if the window could not be created
	if (!GLFWindow::mpWindow)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		fprintf(stderr, "Either GLFW is not installed or your graphics card does not support modern OpenGL.\n");
		glfwTerminate();
		return;
	}

	// Make the context of the window
	glfwMakeContextCurrent(GLFWindow::mpWindow);
	// Get the width and height of the framebuffer to properly resize the window
	glfwGetFramebufferSize(GLFWindow::mpWindow, &mWidth, &mHeight);

	// Call the resize callback to make sure things get drawn immediately
	Resize(mWidth, mHeight);
}

void GLFWindow::DestroyWindow()
{
	// Destroy the window
	glfwDestroyWindow(GLFWindow::mpWindow);

	// Terminate GLFW
	glfwTerminate();
}

void GLFWindow::SwapBuffers()
{
	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(GLFWindow::mpWindow);
}

void GLFWindow::Resize(int width, int height)
{
#ifdef __APPLE__
	glfwGetFramebufferSize(GLFWindow::mpWindow, &width, &height); // In case your Mac has a retina display
#endif
	mWidth = width;
	mHeight= height;
	// Set the viewport size. This is the only matrix that OpenGL maintains for us in modern OpenGL!
	//glViewport(0, 0, width, height);
}

bool GLFWindow::IsClosed()
{
	if( glfwWindowShouldClose(GLFWindow::mpWindow) )
	{
		return true;
	}
	return false;
}

void* GLFWindow::GetProcAddress()
{
	return (void *)glfwGetProcAddress;
}