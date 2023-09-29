#include <Window.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <Framebuffer.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>
#include <iostream>

static GLFWwindow* window;

static WindowProps winProps;

static Framebuffer* winFramebuffer;

static VertexArray* winScreenVAO;

static VertexBuffer* winScreenVBO;

static unsigned int winScreenShaderID;

static bool winFocused = true;

static struct {
	bool pressed = false;
	bool repeated = false;
} appKeys[Key_Max]{};

static bool appButtons[Button_Max]{};

static struct {
	double xpos = 0.0f;
	double ypos = 0.0f;
} appCursorPos;

static void ErrorCallback(int error, const char* description)
{
	std::cout << "\033[41m\033[30mERROR::GLFW\033[0m " << description << std::endl;
}

static void FrameResizeCallback(GLFWwindow* window, int width, int height)
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize.x = winProps.Width = width;
	io.DisplaySize.y = winProps.Height = height;
	glViewport(0, 0, width, height);
	delete winFramebuffer;
	winFramebuffer = new Framebuffer(width, height);
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	unsigned int keyIndex;
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		keyIndex = Key_Escape;
		break;
	case GLFW_KEY_LEFT_CONTROL:
		keyIndex = Key_LControl;
		break;
	case GLFW_KEY_SPACE:
		keyIndex = Key_Space;
		break;
	case GLFW_KEY_A:
		keyIndex = Key_A;
		break;
	case GLFW_KEY_W:
		keyIndex = Key_W;
		break;
	case GLFW_KEY_S:
		keyIndex = Key_S;
		break;
	case GLFW_KEY_D:
		keyIndex = Key_D;
		break;
	case GLFW_KEY_F:
		keyIndex = Key_F;
		break;
	default:
		keyIndex = Key_Max;
	}
	if (keyIndex < Key_Max)
	{
		if (action == GLFW_PRESS)
			appKeys[keyIndex] = { true, false };
		else if (action == GLFW_REPEAT)
			appKeys[keyIndex] = { false, true };
		else if (action == GLFW_RELEASE)
			appKeys[keyIndex] = { false, false };
	}
}

static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	unsigned int buttonIndex;
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		buttonIndex = Button_Left;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		buttonIndex = Button_Right;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		buttonIndex = Button_Middle;
		break;
	default:
		buttonIndex = Button_Max;
	}
	if (buttonIndex < Button_Max)
		appButtons[buttonIndex] = (action == GLFW_PRESS);
}

static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	appCursorPos.xpos = xpos;
	appCursorPos.ypos = ypos;
}

static void WindowFocusCallback(GLFWwindow* window, int focused)
{
	winFocused = (bool)focused;
}

bool Window::Create(const WindowProps& props)
{
	winProps.Width = props.Width;
	winProps.Height = props.Height;
	winProps.Title = props.Title;
	//winProps.Resizable = props.Resizable; // Ignoring the resizable variable
	glfwSetErrorCallback(ErrorCallback);
	glfwInit();
	// Setting OpenGL to #version 330 core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, props.Resizable);
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
	// Setting window callbacks
	glfwSetFramebufferSizeCallback(window, FrameResizeCallback);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetCursorPosCallback(window, CursorPosCallback);
	glfwSetWindowFocusCallback(window, WindowFocusCallback);
	// Other functions
	glfwSetWindowSizeLimits(window, props.MinWidth, props.MinHeight, GLFW_DONT_CARE, GLFW_DONT_CARE);
	// Printing the OpenGL version
	std::cout << "\033[42m\033[30mINFO::Window\033[0m OpenGL version - " << glGetString(GL_VERSION) << std::endl;
	// Setting vertical sync as enabled
	glfwSwapInterval(1);
	// Setting up Dear ImGui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard;

	// Setting the color style
	ImGui::StyleColorsDark();

	// Setting Platform/Renderer backend
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();

	float screenVerts[] = {
		-1.0f, -1.0f,   0.0f, 0.0f,
		 1.0f, -1.0f,   1.0f, 0.0f,
		 1.0f,  1.0f,   1.0f, 1.0f,

		 1.0f,  1.0f,   1.0f, 1.0f,
		-1.0f,  1.0f,   0.0f, 1.0f,
		-1.0f, -1.0f,   0.0f, 0.0f,
	};
	winScreenVAO = new VertexArray();
	winScreenVAO->Bind();
	winScreenVBO = new VertexBuffer(screenVerts, sizeof(screenVerts));
	winScreenVBO->Bind();
	VertexBufferLayout()
		.Push<float>(2)
		.Push<float>(2)
	.Enable();
	winFramebuffer = new Framebuffer(props.Width, props.Height);
	const char* screenVertSrc =
		R"(#version 330 core
		layout (location = 0) in vec2 aPos;
		layout (location = 1) in vec2 aTexCoords;
		out vec2 TexCoords;
		void main()
		{
			gl_Position = vec4(aPos, 0.0, 1.0);
		})";
	const char* screenFragSrc =
		R"(#version 330 core
		in vec2 TexCoords;
		uniform sampler2D uTexture;
		void main()
		{
			gl_FragColor = texture(uTexture, TexCoords);
		})";
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &screenVertSrc, nullptr);
	glCompileShader(vs);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &screenFragSrc, nullptr);
	glCompileShader(fs);
	winScreenShaderID = glCreateProgram();
	glAttachShader(winScreenShaderID, vs);
	glAttachShader(winScreenShaderID, fs);
	glLinkProgram(winScreenShaderID);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glUseProgram(winScreenShaderID);
	glUniform1i(glGetUniformLocation(winScreenShaderID, "uTexture"), 0);
	return true;
}

void Window::Terminate()
{
	delete winScreenVAO;
	delete winScreenVBO;
	delete winFramebuffer;
	glDeleteProgram(winScreenShaderID);
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

void Window::Run(Application& app)
{
	float past = 0.0f;
	while (IsRunning())
	{
		float now = (float)glfwGetTime();
		float delta = now - past;
		past = now;
		Poll();
		if (winFocused)
		{
			glEnable(GL_DEPTH_TEST);

			winFramebuffer->Bind();
			app.OnUpdate(delta);
			app.OnRender();
			ImGui::NewFrame();
			app.OnRenderImGui();
			Render();
			glDisable(GL_DEPTH_TEST);
			glUseProgram(winScreenShaderID);
			winFramebuffer->PrepDraw();
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			winScreenVAO->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 6);
			winScreenVAO->Unbind();
		}
	}
}

int Window::GetWidth()
{
	return winProps.Width;
}

int Window::GetHeight()
{
	return winProps.Height;
}

float Window::GetMouseXPos()
{
	return (float)appCursorPos.xpos;
}

float Window::GetMouseYPos()
{
	return (float)appCursorPos.ypos;
}

float Window::GetAspectRatio()
{
	return (float)winProps.Width / (float)winProps.Height;
}

bool Window::IsKeyPressed(const KeyCode& keyCode)
{
	if (keyCode >= Key_Max || keyCode < 0)
		return false;

	return appKeys[keyCode].pressed;
}

bool Window::IsKeyHeld(const KeyCode& keyCode)
{
	if (keyCode >= Key_Max || keyCode < 0)
		return false;

	return appKeys[keyCode].repeated;
}

void Window::Close()
{
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

bool Window::IsButtonPressed(const ButtonCode& buttonCode)
{
	if (buttonCode >= Button_Max || buttonCode < 0)
		return false;

	return appButtons[buttonCode];
}

void Window::SetMouseMode(const MouseMode& mode)
{
	ImGuiIO& io = ImGui::GetIO();
	switch (mode)
	{
	default:
	case MouseMode::Mouse_Disabled:
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
		break;
	case MouseMode::Mouse_Normal:
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard;
		break;
	}
}
