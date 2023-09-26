#include <Window.h>
#include "TexturedCube.h"
#include "Lighting.h"

int main(void)
{
	if (Window::Create())
	{
		Window::Run(MultiLight());
	}
	Window::Terminate();
	return 0;
}