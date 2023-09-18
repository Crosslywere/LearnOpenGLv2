#include <iostream>
#include <Window.h>

int main()
{
	if (Window::Create())
		while (Window::IsRunning())
			Window::Update();
	Window::Terminate();
}