#include <Window.h>
#include "TexturedCube.h"
#include "Lighting.h"
#include "Cubemap.h"

int main(void)
{
	WindowProps props;
	props.Width = 1280;
	props.Height = 720;
	props.Title = "Cubemap";
	props.Resizable = false;
	if (Window::Create(props))
    {
		Window::Run(Cubemap());
    }
	Window::Terminate();
    return 0;
}