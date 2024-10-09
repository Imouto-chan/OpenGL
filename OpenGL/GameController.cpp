#include "GameController.h"
#include "WindowController.h"
#ifdef USE_TOOL_WINDOW
	#include "ToolWindow.h"
#endif

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black background
	glEnable(GL_DEPTH_TEST);

	camera = Camera(WindowController::GetInstance().GetResolution());
	camera.LookAt({ 2, 2, 2 }, { 0,0,0 }, { 0,1,0 });
	//glfwSetWindowSize(WindowController::GetInstance().GetWindow(), resolutions[0].width, resolutions[0].height);
}

void GameController::RunGame()
{
#ifdef USE_TOOL_WINDOW
	// Show the C++/CLI tool window
	OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	window->Show();
#endif

	shader = Shader();
	shader.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

	mesh = Mesh();
	mesh.Create(&shader);

	int curCamera = 0;
	int curResolution = 0;
	bool v_pressed = false; // to make sure the key is lifted before being reactivated
	bool c_pressed = false;

	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do
	{
#ifdef USE_TOOL_WINDOW
		// Winform stuff
		System::Windows::Forms::Application::DoEvents(); // Handle C++/CLI form events

		GLint loc = 0;
		loc = glGetUniformLocation(shader.GetProgramID(), "RenderRedChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderRedChannel);
		loc = glGetUniformLocation(shader.GetProgramID(), "RenderGreenChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderGreenChannel);
		loc = glGetUniformLocation(shader.GetProgramID(), "RenderBlueChannel");
		glUniform1i(loc, (int)OpenGL::ToolWindow::RenderBlueChannel);
#endif



		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen and dept buffer
		mesh.Render(camera.GetProjection() * camera.GetView());
		glfwSwapBuffers(win); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the ESC Key was pressed
		glfwWindowShouldClose(win) == 0); // Check if the window was closed

	mesh.Cleanup();
	shader.Cleanup();
}