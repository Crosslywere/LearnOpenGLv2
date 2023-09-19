#include <iostream>
#include <Window.h>
#include <glad/glad.h>
#include <iostream>

void ProcessInputs()
{
	if (Window::IsKeyPressed(KeyCode::Forward))
	{
		Window::Close();
	}
}

int main()
{
	if (Window::Create())
	{
		float verts[9] = {
			0.0f, 0.5f, 0.0f,
			0.5f, -.5f, 0.0f,
			-.5f, -.5f, 0.0f,
		};
		unsigned int VAO, VBO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
		while (Window::IsRunning())
		{
			ProcessInputs();
			glClear(GL_COLOR_BUFFER_BIT);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			Window::Update();
		}
	}
	Window::Terminate();
}