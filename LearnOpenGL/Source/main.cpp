#include <iostream>
#include <Window.h>
#include <glad/glad.h>
#include <iostream>

int main()
{
	if (Window::Create())
	{
		glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
		while (Window::IsRunning())
		{
			glClear(GL_COLOR_BUFFER_BIT);

			Window::Update();
		}
	}
	Window::Terminate();
}