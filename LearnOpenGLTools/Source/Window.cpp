#include <Window.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLFWwindow* window;

Window::~Window()
{
}

bool Window::Create(const WindowProps& props)
{
	glfwInit();
	// Setting OpenGL to #version 330 core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(props.Width, props.Height, props.Title, nullptr, nullptr);
	if (!window)
	{
		std::cout << "\033[41m\033[30mERROR::Window\033[0m Failed to create window!" << std::endl;
		return false;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "\033[41m\033[30mERROR::Window\033[0m Failed to load OpenGL functions!" << std::endl;
		return false;
	}
	// Printing the OpenGL version
	std::cout << "\033[42m\033[30mINFO::Window\033[0m OpenGL version - " << glGetString(GL_VERSION) << std::endl;
	// Setting vertical sync as enabled
	glfwSwapInterval(1);
	return true;
}

void Window::Terminate()
{
	glfwTerminate();
}

bool Window::IsRunning()
{
	return !glfwWindowShouldClose(window);
}

void Window::Update()
{
	// Swapping the buffer
	glfwSwapBuffers(window);
	// Polling the event
	glfwPollEvents();
}

bool Window::IsKeyPressed(const KeyCode& keyCode)
{
	switch (keyCode)
	{
	case KeyCode::Forward:
		return glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
	case KeyCode::Backward:
		return glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
	case KeyCode::Left:
		return glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
	case KeyCode::Right:
		return glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
	case KeyCode::Up:
		return glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
	case KeyCode::Down:
		return glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;
	case KeyCode::Escape:
		return glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
	default:
		return false;
	}
}

void Window::Close()
{
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}
