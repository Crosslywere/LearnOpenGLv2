#include <Window.h>
#include "TexturedCube.h"
#include "Lighting.h"
#include "FrameBuffer.h"

int main(void)
{
	if (Window::Create())
	{
		Window::Run(MultiLight());
	}
	Window::Terminate();
	return 0;
}