#include "GameController.h"
#include "WindowController.h"
#ifdef USE_TOOL_WINDOW
	#include "ToolWindow.h"
#endif
#include "Font.h"
#include <WinUser.h>

void GameController::Initialize()
{
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f); // Black background
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	srand(time(0));

	camera = Camera(WindowController::GetInstance().GetResolution());
	camera.LookAt({ 5, 0, 10 }, { 0,0,0 }, { 0,1,0 });
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


	shader = Shader();
	shader.LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	
	Mesh* light = new Mesh();
	light->Create(&shaderColor, "../Assets/Models/Sphere.obj");
	light->SetPosition({ 0.0f, 0.0f, 4.0f });
	light->SetColor({ 1.0f, 1.0f, 1.0f });
	light->SetScale({ 0.1f, 0.1f, 0.1f });
	lights.push_back(light);

	Mesh* box = new Mesh();
	box->Create(&shaderDiffuse, "../Assets/Models/monkey.obj");
	box->SetCameraPosition(camera.GetPosition());
	box->SetScale({ 1.0f, 1.0f, 1.0f });
	box->SetPosition({ 0.0f, 0.0f, 0.0f });
	meshBoxes.push_back(box);

	Font* arialFont = new Font();
	arialFont->Create(&shaderFont, "../Assets/Fonts/arial.ttf", 100);

	POINT p;
	p.x = 0;
	p.y = 0;
	bool allowBoxes = false, boxAdded = false, colorPosition = false;
	int boxCount = 0;

	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do
	{
#ifdef USE_TOOL_WINDOW
		// Winform stuff
		System::Windows::Forms::Application::DoEvents(); // Handle C++/CLI form events

		meshBoxes.at(0)->SetSpecularStrength(OpenGL::ToolWindow::specularStrength);
		meshBoxes.at(0)->SetSpecularRed((float)OpenGL::ToolWindow::specularRedChannel / 100);
		meshBoxes.at(0)->SetSpecularGreen((float)OpenGL::ToolWindow::specularGreenChannel / 100);
		meshBoxes.at(0)->SetSpecularBlue((float)OpenGL::ToolWindow::specularBlueChannel / 100);
#endif



		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen and dept buffer
		for (auto light : lights)
		{
			light->Render(camera.GetProjection() * camera.GetView());
		}
		
		if (OpenGL::ToolWindow::radioMoveLightValue)
		{
			colorPosition = false;
			allowBoxes = false;
			for (auto box : meshBoxes)
			{
				box->Cleanup();
				delete box;
			}
			
			meshBoxes.clear();

			box = new Mesh();
			box->Create(&shaderDiffuse, "../Assets/Models/monkey.obj");
			box->SetCameraPosition(camera.GetPosition());
			box->SetScale({ 1.0f, 1.0f, 1.0f });
			box->SetPosition({ 0.0f, 0.0f, 0.0f });
			meshBoxes.push_back(box);

			OpenGL::ToolWindow::radioMoveLightValue = false;
		}
		else if (OpenGL::ToolWindow::radioCubesToSphereValue)
		{
			colorPosition = false;
			boxCount = 0;
			allowBoxes = true;
			for (auto box : meshBoxes)
			{
				box->Cleanup();
				delete box;
			}
			meshBoxes.clear();

			box = new Mesh();
			box->Create(&shaderDiffuse, "../Assets/Models/monkeyBall.obj");
			box->SetCameraPosition(camera.GetPosition());
			box->SetScale({ 1.0f, 1.0f, 1.0f });
			box->SetPosition({ 0.0f, 0.0f, 0.0f });
			meshBoxes.push_back(box);

			OpenGL::ToolWindow::radioCubesToSphereValue = false;
		}
		else if (OpenGL::ToolWindow::radioColorPositionValue)
		{
			colorPosition = true;
			allowBoxes = false;
			for (auto box : meshBoxes)
			{
				box->Cleanup();
				delete box;
			}

			meshBoxes.clear();

			box = new Mesh();
			box->Create(&shader, "../Assets/Models/monkey.obj");
			box->SetCameraPosition(camera.GetPosition());
			box->SetScale({ 1.0f, 1.0f, 1.0f });
			box->SetPosition({ 0.0f, 0.0f, 0.0f });
			meshBoxes.push_back(box);

			OpenGL::ToolWindow::radioColorPositionValue = false;
		}

		if (OpenGL::ToolWindow::resetLightPos)
		{
			light->SetPosition({ 0.0f, 0.0f, 4.0f });
			OpenGL::ToolWindow::resetLightPos = false;
		}
		else if (OpenGL::ToolWindow::resetMonkeyPos && !allowBoxes)
		{
			meshBoxes.at(0)->SetPosition({0.0f, 0.0f, 0.0f});
			OpenGL::ToolWindow::resetMonkeyPos = false;
		}

		GetCursorPos(&p);

		if (allowBoxes)
		{
			if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !boxAdded) // left mouse button was pressed
			{
				boxAdded = true;
				boxCount++;
				box = new Mesh();
				box->Create(&shaderDiffuse, "../Assets/Models/CubeBox.obj");
				box->SetCameraPosition(camera.GetPosition());
				box->SetScale({ 0.5f, 0.5f, 0.5f });
				box->SetPosition({ glm::linearRand(-3.0f, 3.0f), glm::linearRand(-3.0f, 3.0f), glm::linearRand(-3.0f, 3.0f) });
				meshBoxes.push_back(box);
			}
			else if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS && boxAdded)
			{
				boxAdded = false;
			}
		}
		else if (!colorPosition)
		{
			if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) // left mouse button was pressed
			{
				if (p.x < (1024 / 2))
				{
					glm::vec3 pos = light->GetPosition();
					pos.x -= 0.01;
					light->SetPosition(pos);
				}
				else
				{
					glm::vec3 pos = light->GetPosition();
					pos.x += 0.01;
					light->SetPosition(pos);
				}

				if (p.y < (768 / 2))
				{
					glm::vec3 pos = light->GetPosition();
					pos.y += 0.01;
					light->SetPosition(pos);
				}
				else
				{
					glm::vec3 pos = light->GetPosition();
					pos.y -= 0.01;
					light->SetPosition(pos);
				}
			}
		}
		else if (colorPosition)
		{
			if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) // left mouse button was pressed
			{
				if (p.x < (1024 / 2))
				{
					glm::vec3 pos = meshBoxes.at(0)->GetPosition();
					pos.x -= 0.01;
					meshBoxes.at(0)->SetPosition(pos);
				}
				else
				{
					glm::vec3 pos = meshBoxes.at(0)->GetPosition();
					pos.x += 0.01;
					meshBoxes.at(0)->SetPosition(pos);
				}

				if (p.y < (768 / 2))
				{
					glm::vec3 pos = meshBoxes.at(0)->GetPosition();
					pos.y += 0.01;
					meshBoxes.at(0)->SetPosition(pos);
				}
				else
				{
					glm::vec3 pos = meshBoxes.at(0)->GetPosition();
					pos.y -= 0.01;
					meshBoxes.at(0)->SetPosition(pos);
				}
			}
		}


		glm::vec3 rotation = { 0.005f, 0.0f, 0.0f };
		for (auto box : meshBoxes)
		{
			box->SetRotation(box->GetRotation() + rotation);
			box->Render(camera.GetProjection() * camera.GetView());
		}

		std::string output = "Mouse Pos ";
		std::string position = std::to_string(p.x) + " " + std::to_string(p.y);
		output += position;
		arialFont->RenderText(output, 10, 50, 0.5f, {1.0f, 1.0f, 0.0f});
		arialFont->RenderText("Cubes: " + std::to_string(boxCount), 10, 150, 0.5f, { 1.0f, 1.0f, 0.0f });


		glfwSwapBuffers(win); // Swap the front and back buffers
		glfwPollEvents();

	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && // Check if the ESC Key was pressed
		glfwWindowShouldClose(win) == 0); // Check if the window was closed

	for (auto light : lights)
	{
		light->Cleanup();
		delete light;
	}
	lights.clear();
	for (auto box : meshBoxes)
	{
		box->Cleanup();
		delete box;
	}
	meshBoxes.clear();

	shaderFont.Cleanup();
	shaderDiffuse.Cleanup();
	shaderColor.Cleanup();
	shader.Cleanup();
}