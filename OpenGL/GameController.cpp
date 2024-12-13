#include "GameController.h"
#include "WindowController.h"
#ifdef USE_TOOL_WINDOW
	#include "ToolWindow.h"
#endif
#include "Font.h"
#include "Mesh.h"
#include "GameTime.h"

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	srand(time(0));

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	camera = Camera(WindowController::GetInstance().GetResolution());
	camera.LookAt({ 5, 5, 5 }, { 0,0,0 }, { 0,1,0 });
	//glfwSetWindowSize(WindowController::GetInstance().GetWindow(), resolutions[0].width, resolutions[0].height);
}

void GameController::RunGame()
{
#ifdef USE_TOOL_WINDOW
	// Show the C++/CLI tool window
	OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	window->Show();
#endif

	shaderColor = Shader();
	shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");

	shaderDiffuse = Shader();
	shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");

	shaderFont = Shader();
	shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");

	shaderSkybox = Shader();
	shaderSkybox.LoadShaders("Skybox.vertexshader", "Skybox.fragmentshader");

	shaderPost = Shader();
	shaderPost.LoadShaders("Postprocessor.vertexshader", "Postprocessor.fragmentshader");

	postProcessor = PostProcessor();
	postProcessor.Create(&shaderPost);

	Mesh* light = new Mesh();
	light->Create(&shaderColor, "../Assets/Models/Sphere.obj");
	light->SetPosition({ 3.0f, 0.0f, 0.0f });
	light->SetColor({ 1.0f, 1.0f, 1.0f });
	light->SetScale({ 0.1f, 0.1f, 0.1f });
	lights.push_back(light);

	Mesh* mesh = nullptr;

	// Fighter
	//mesh = new Mesh();
	//mesh->Create(&shaderDiffuse, "../Assets/Models/Fighter.obj");
	//mesh->SetCameraPosition(camera.GetPosition());
	//mesh->SetPosition({0.0f, 0.0f, 0.0f});
	//mesh->SetScale({ 0.002f, 0.002f, 0.002f });
	//meshes.push_back(mesh);

	// Fighter ASE
	mesh = new Mesh();
	mesh->Create(&shaderDiffuse, "../Assets/Models/Fighter.ase");
	mesh->SetCameraPosition(camera.GetPosition());
	mesh->SetPosition({0.0f, 0.0f, 0.0f});
	mesh->SetScale({ 0.002f, 0.002f, 0.002f });
	meshes.push_back(mesh);

	// Cube
	//mesh = new Mesh();
	//mesh->Create(&shaderDiffuse, "../Assets/Models/Cube.obj", 1000);
	//mesh->SetCameraPosition(camera.GetPosition());
	//mesh->SetScale({ 0.1f, 0.1f, 0.1f });
	//mesh->SetPosition({0.0f, 0.0f, 0.0f});
	//meshes.push_back(mesh);

	/*box = new Mesh();
	box->Create(&shaderDiffuse, "../Assets/Models/monkey.obj");
	box->SetCameraPosition(camera.GetPosition());
	box->SetScale({ 1.0f, 1.0f, 1.0f });
	box->SetPosition({5.0f, 0.0f, 0.0f});
	meshBoxes.push_back(box);box = new Mesh();

	skybox = new Skybox();
	skybox->Create(&shaderSkybox, "../Assets/Models/Skybox.obj",
		{ "../Assets/Textures/Skybox/right.jpg",
		"../Assets/Textures/Skybox/left.jpg",
		"../Assets/Textures/Skybox/top.jpg",
		"../Assets/Textures/Skybox/bottom.jpg",
		"../Assets/Textures/Skybox/front.jpg",
		"../Assets/Textures/Skybox/back.jpg" });*/

	Font* arialFont = new Font();
	arialFont->Create(&shaderFont, "../Assets/Fonts/arial.ttf", 100);

	GameTime::GetInstance().Initialize();
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

		GameTime::GetInstance().Update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen and dept buffer

		/*camera.Rotate();
		glm::mat4 view = glm::mat4(glm::mat3(camera.GetView()));
		skybox->Render(camera.GetProjection() * view);*/

		postProcessor.Start();

		for (auto light : lights)
		{
			light->Render(camera.GetProjection() * camera.GetView());
		}
		
		// Note we are now using a pointer so we are not doing a shallow copy, we could also
		// use a reference if we were not on the Heap
		glm::vec3 rotationSpeed = { 0.0f, 0.005f, 0.0f };
		for (auto mesh : meshes)
		{
			mesh->SetRotation(mesh->GetRotation() + (rotationSpeed * (float)GameTime::GetInstance().DeltaTime()));
			mesh->Render(camera.GetProjection() * camera.GetView());
		}

		postProcessor.End();

		arialFont->RenderText(std::to_string(GameTime::GetInstance().Fps()), 100, 100, 0.5f, {1.0f, 1.0f, 0.0f});
		glfwSwapBuffers(win); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the ESC Key was pressed
		glfwWindowShouldClose(win) == 0); // Check if the window was closed

	postProcessor.Cleanup();

	for (auto light : lights)
	{
		light->Cleanup();
		delete light;
	}
	lights.clear();
	for (auto mesh : meshes)
	{
		mesh->Cleanup();
		delete mesh;
	}
	meshes.clear();

	shaderPost.Cleanup();
	shaderFont.Cleanup();
	shaderDiffuse.Cleanup();
	shaderColor.Cleanup();
	shaderSkybox.Cleanup();
}