#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H

// Include standard headers
#include <vector>
#include <string>
#include <fstream>

// Windows specific includes and defines
#ifdef _WIN32
#include <windows.h>
#define M_ASSERT(_cond, _msg) \
	if (!(_cond)) { OutputDebugStringA(_msg); std:abort(); glfwTerminate();}
#endif

// Open GL/Helper Headers
#include <GL/glew.h> // Include GLEW
#include <GLFW/glfw3.h>	// Include GLFW
#include <glm/glm.hpp> // Include GLM
#include <glm/gtc/matrix_transform.hpp> // View / Projection
#include <glm/gtc/random.hpp>

#include "Resolution.h"
#include "Singleton.h"

#endif // STANDARD_INCLUDES_H