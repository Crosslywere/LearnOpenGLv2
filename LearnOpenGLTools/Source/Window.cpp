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
	window = glfwCreateWindow(props.Width, props.Height, props.Title, nullptr, nullptr);
	if (!window)
	{
		std::cout << "\033[31mERROR\033[0mFailed to create window!" << std::endl;
		return false;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "\033[41m\033[30mERROR\033[0m Failed to load OpenGL functions!" << std::endl;
		return false;
	}
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
	glfwPollEvents();
	glfwSwapBuffers(window);
}
