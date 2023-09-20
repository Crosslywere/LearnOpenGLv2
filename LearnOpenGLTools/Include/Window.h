#pragma once
#ifndef WINDOW_H
#define WINDOW_H

/**
 * @brief A virtual Application class to be implemented by an application to be run on the window
 */
class Application
{
public:
	virtual void OnUpdate(float deltaTime) {}
	virtual void OnRender() {}
	virtual void OnRenderImGui() {}
};

/**
 * @brief The set of keys used by the window
 */
enum class KeyCode
{
	Key_Escape = 0,
	Key_W,
	Key_S,
	Key_A,
	Key_D,
	Key_Space,
	Key_LControl,
	Key_F,
};

/**
 * @brief A struct used to define the properties of a window
 */
struct WindowProps
{
	int Width = 800;
	int Height = 600;
	const char* Title = "Default";
	bool Resizable = true;
};

/**
 * @brief A singleton class that is responsible for creating the window for rendering
 */
class Window
{
public:
	/**
	 * @brief Should be called first before any OpenGL function as this preps a render context as
	 * well as OpenGL function pointers through "glad"
	 * 
	 * @param props A WindowProps struct that holds all the necessary information for creating the
	 * window
	 * 
	 * @return Returns true if the window is successfully created and the function pointers are
	 * successfully loaded. 
	 */
	static bool Create(const WindowProps& props = WindowProps());
	/**
	 * @brief Should be called at the end of the application to terminate the render context (the
	 * window)
	 */
	static void Terminate();
	/**
	 * @brief Checks if the window is meant to close
	 * 
	 * @return Returns true if the window isn't meant to close 
	 */
	static bool IsRunning();
	/**
	 * @brief Updates the window's frame buffer
	 */
	static void Render();
	/**
	 * @brief Update's window events
	 */
	static void Poll();
	/**
	 * @brief Checks if the key specified is pressed
	 * 
	 * @param keyCode A KeyCode enum class that represents each possible key
	 * 
	 * @return Returns true if the button specified is pressed and false otherwise
	 */
	static bool IsKeyPressed(const KeyCode& keyCode);
	/**
	 * @brief Sets the window to be closed
	 */
	static void Close();

	static void Run(Application& app);
private:
	Window() = default;
};

#endif // WINDOW_H