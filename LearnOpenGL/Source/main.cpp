#include <Window.h>
#include "TexturedCube.h"

int main(void)
{
	if (Window::Create())
		Window::Run(TexturedCube());
	Window::Terminate();
	return 0;
}