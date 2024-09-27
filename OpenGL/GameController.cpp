#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black background
	glEnable(GL_CULL_FACE);

	camera = Camera(WindowController::GetInstance().GetResolution());
	camera.LookAt({ 200, 200, 200 }, { 0,0,0 }, { 0,1,0 });
	//glfwSetWindowSize(WindowController::GetInstance().GetWindow(), resolutions[0].width, resolutions[0].height);
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
	glm::mat4 vp;
	glm::mat4 world = glm::mat4(1);

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



		glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
		vp = camera.GetProjection() * camera.GetView();

		// Select rotation
		if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) // A was pressed
		{
			world = glm::rotate(world, 0.01f, { 0, 1, 0 });
		}

		if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) // D was pressed
		{
			world = glm::rotate(world, 0.01f, { 0, -1, 0 });
		}

		if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) // W was pressed
		{
			world = glm::rotate(world, 0.01f, { 1, 0, 0 });
		}

		if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) // S was pressed
		{
			world = glm::rotate(world, 0.01f, { -1, 0, 0 });
		}

		//world *= glm::scale(world, { 2, 2, 2 });

		vp *= world;
		vp = glm::scale(vp, {fmod(glfwGetTime(),2.0),fmod(glfwGetTime(),2.0),fmod(glfwGetTime(),2.0) });
		mesh.Render(vp);
		glfwSwapBuffers(win); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the ESC Key was pressed
		glfwWindowShouldClose(win) == 0); // Check if the window was closed

	mesh.Cleanup();
	shader.Cleanup();
}