#include <Window.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <iostream>

static GLFWwindow* window;
unsigned int winWidth, winHeight;

static void ErrorCallback(int error, const char* description)
{
	std::cout << "\033[41m\033[30mERROR::GLFW\033[0m " << description << std::endl;
}

static void FrameResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool Window::Create(const WindowProps& props)
{
	glfwSetErrorCallback(ErrorCallback);
	glfwInit();
	// Setting OpenGL to #version 330 core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	const char* glsl_version = "#version 330 core";
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
	glfwSetFramebufferSizeCallback(window, FrameResizeCallback);
	// Printing the OpenGL version
	std::cout << "\033[42m\033[30mINFO::Window\033[0m OpenGL version - " << glGetString(GL_VERSION) << std::endl;
	// Setting vertical sync as enabled
	glfwSwapInterval(1);
	// Setting up Dear ImGui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	// Setting the color style
	ImGui::StyleColorsDark();

	// Setting Platform/Renderer backend
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();

	return true;
}

void Window::Terminate()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}

bool Window::IsRunning()
{
	return !glfwWindowShouldClose(window);
}

void Window::Render()
{
	// Rendering the ImGui frame
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// Swapping the buffer
	glfwSwapBuffers(window);
	// Polling the event
	glfwPollEvents();
}

void Window::Poll()
{
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
