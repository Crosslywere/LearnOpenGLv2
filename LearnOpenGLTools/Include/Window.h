#pragma once
#ifndef WINDOW_H
#define WINDOW_H

/**
 * @brief The set of keys used by the window
 */
enum class KeyCode
{
	Escape = 0,
	Forward,
	Backward,
	Left,
	Right,
	Up,
	Down,
};

/**
 * @brief A struct used to define the properties of a window
 */
struct WindowProps
{
	int Width = 800;
	int Height = 600;
	const char* Title = "Default";
};

/**
 * @brief A singleton class that is responsible for creating the window for rendering
 */
class Window
{
public:
	~Window();
	static bool Create(const WindowProps& props = WindowProps());
	static void Terminate();
	static bool IsRunning();
	static void Update();
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
private:
	Window() = default;
};

#endif // WINDOW_H