#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black background

	resolutions[0] = Resolution(1200, 800, 45);
	resolutions[1] = Resolution(800, 800, 45);
	resolutions[2] = Resolution(1400, 800, 45);

	camera[0].SetResolution(resolutions[0]);
	camera[1].SetWorldSpace(glm::vec3(2, 1, 1));
	camera[1].SetResolution(resolutions[0]);
	camera[2].SetWorldSpace(glm::vec3(6, 4, 4));
	camera[2].SetResolution(resolutions[0]);

	glfwSetWindowSize(WindowController::GetInstance().GetWindow(), resolutions[0].width, resolutions[0].height);
}

void GameController::RunGame()
{
	// Show the C++/CLI tool window
	OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	window->Show();

	shader = Shader();
	shader.LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	mesh = Mesh();
	mesh.Create(&shader);

	int curCamera = 0;
	int curResolution = 0;
	bool v_pressed = false; // to make sure the key is lifted before being reactivated
	bool c_pressed = false;

	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do
	{
		// Winform stuff
		System::Windows::Forms::Application::DoEvents(); // Handle C++/CLI form events

		GLint loc = 0;
		loc = glGetUniformLocation(shader.GetProgramID(), "RenderRedChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderRedChannel);
		loc = glGetUniformLocation(shader.GetProgramID(), "RenderGreenChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderGreenChannel);
		loc = glGetUniformLocation(shader.GetProgramID(), "RenderBlueChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderBlueChannel);

		if (glfwGetKey(win, GLFW_KEY_V) == GLFW_PRESS && !v_pressed) // W was pressed
		{
			v_pressed = true;
			curResolution = (curResolution == 2) ? 0 : curResolution + 1;
			camera[curCamera].SetResolution(resolutions[curResolution]);
			glfwSetWindowSize(WindowController::GetInstance().GetWindow(), resolutions[curResolution].width, resolutions[curResolution].height);
		}
		else if (glfwGetKey(win, GLFW_KEY_V) != GLFW_PRESS)
		{
			v_pressed = false;
		}

		if (glfwGetKey(win, GLFW_KEY_C) == GLFW_PRESS && !c_pressed) // C was pressed
		{
			c_pressed = true;
			curCamera = (curCamera == 2) ? 0 : curCamera + 1;
			camera[curCamera].SetResolution(resolutions[curResolution]);
		}
		else if (glfwGetKey(win, GLFW_KEY_C) != GLFW_PRESS)
		{
			c_pressed = false;
		}

		glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
		mesh.Render(camera[curCamera].GetProjection() * camera[curCamera].GetView());
		glfwSwapBuffers(win); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the ESC Key was pressed
		glfwWindowShouldClose(win) == 0); // Check if the window was closed

	mesh.Cleanup();
	shader.Cleanup();
}