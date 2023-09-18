#pragma once
#ifndef WINDOW_H
#define WINDOW_H

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
private:
	Window() = default;
};

#endif // WINDOW_H