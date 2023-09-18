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
	std::cout << "\033[42m\033[30mINFO::Window\033[0m OpenGL version - " << glGetString(GL_VERSION) << std::endl;
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
	glfwSwapBuffers(window);
	glfwPollEvents();
}
